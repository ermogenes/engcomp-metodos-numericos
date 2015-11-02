/*
Funções para trabalho com matrizes.

Author: Ermogenes Palacio
Date: 2015-11-02
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double** matriz(int l, int c){
    int i;
    double **M = malloc(sizeof(double *) * l);
    for(i = 0; i < l; i++){
        M[i] = malloc(sizeof(double) * c);
    }
    return M;
}

double** matriz_quadrada(int dim){
    return matriz(dim, dim);
}

void preenche_valor(double **M, int l, int c, double valor){
    int i, j;
    for(i = 0; i < l; i++){
        for(j = 0; j < c; j++){
            M[i][j] = valor;
        }
    }
}

void preenche_valor_quadrada(double **M, int dim, double valor){
    return preenche_valor(M, dim, dim, valor);
}

void preenche_identidade(double **M, int dim){
    int i, j;
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            M[i][j] = (i == j);
        }
    }
}

void carrega_valores(double **M, int l, int c, double *m){
    int i, j;
    for(i = 0; i < l; i++){
        for(j = 0; j < c; j++){
            M[i][j] = ((double (*)[c])m)[i][j];
        }
    }
}

double** matriz_nula(int l, int c){
    double **M = matriz(l, c);
    preenche_valor(M, l, c, 0);
    return M;
}

double** matriz_quadrada_nula(int dim){
    return matriz_nula(dim, dim);
}

double** matriz_identidade(int dim){
    double **I = matriz_quadrada(dim);
    preenche_identidade(I, dim);
    return I;
}

double** matriz_valores(int l, int c, double *m){
    double **M = matriz(l, c);
    carrega_valores(M, l, c, m);
    return M;
}

double** matriz_valores_quadrada(int dim, double *m){
    return matriz_valores(dim, dim, m);
}

void imprime_matriz(double **M, int l, int c, char *identificador){
    int i, j;
    printf("\n--- %s ---\n", identificador);
    for(i = 0; i < l; i++){
        for(j = 0; j < c; j++){
            printf("%f\t", M[i][j]);
        }
        printf("\n");
    }
};

double arred(double n, int multiplicador){
    return round(n * multiplicador) / multiplicador;
}

bool matrizes_iguais(double **M1, double **M2, int dim){
    int i, j;
    double m1ij, m2ij;
    int multiplicador = 1000;
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            m1ij = arred(M1[i][j], multiplicador);
            m2ij = arred(M2[i][j], multiplicador);
            if (m1ij != m2ij){
                return false;
            }
        }
    }
    return true;
}

bool confere_fatoracao_lu(double **A, int dim, double **L, double **U, double **P, double **L_ok, double **U_ok, double **P_ok){
    return (
        matrizes_iguais(L, L_ok, dim) &&
        matrizes_iguais(U, U_ok, dim) &&
        matrizes_iguais(P, P_ok, dim)
    );
}

void troca(double *x, double *y){
    double aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

void matriz_pivo(double **M1, double **M2, int dim){
    preenche_identidade(M2, dim);
    int i, j, k;
    for(i = 0; i < dim; i++){
        int max_j = i;
        for(j = i; j < dim; j++){
            if (fabs(M1[j][i]) > fabs(M1[max_j][i])){
                    max_j = j;
            }
        }
        if (max_j != i){
            for(k = 0; k < dim; k++){
                troca(&M2[i][k], &M2[max_j][k]);
            }
        }
    }
}

double** produto(double** M1, double** M2, int l1, int c1, int l2, int c2){
    int i, j, k;
    double **produto = matriz_nula(l1, c2);
    for(i = 0; i < l1; i++)
        for(j = 0; j < c2; j++)
            for(k = 0; k < c1; k++)
                produto[i][j] += M1[i][k] * M2[k][j];
    return produto;
}

double** produto_quadradas(double** M1, double** M2, int dim){
    return produto(M1, M2, dim, dim, dim, dim);
}

void fatoracao_lu(double **A, int dim, double **L, double **U, double **P){
    double **PA;

    preenche_valor_quadrada(L, dim, 0);
    preenche_valor_quadrada(U, dim, 0);

    matriz_pivo(A, P, dim);

    PA = produto_quadradas(P, A, dim);

    preenche_identidade(L, dim);

    int i, j, k;
    for(j = 0; j < dim; j++){
        L[j][j] = 1;
        for(i = 0; i <= j; i++){
            double soma = 0;
            for(k = 0; k < i; k++){
                    soma += U[k][j] * L[i][k];
            }
            U[i][j] = PA[i][j] - soma;
        }
        for(i = j; i < dim; i++){
            double soma = 0;
            for(k = 0; k < j; k++){
                    soma += U[k][j] * L[i][k];
            }
            L[i][j] = (PA[i][j] - soma) / U[j][j];
        }
    }

    free(PA); PA = NULL;
}

void substituicao_ascendente(double **L, double **B, int dim, double **Y){
    int i, j;

    Y[0][0] = B[0][0] / L[0][0];
    for(i = 1; i < dim; i++){
        double soma = 0;
        for (j = 0; j < i; j++){
            soma += L[i][j] * Y[j][0];
        }
        Y[i][0] = (1 / L[i][i]) * (B[i][0] - soma);
    }
//    imprime_matriz(Y, dim, 1, "Y substituido");
};

void substituicao_descendente(double **U, double **Y, int dim, double **X){
    int i, j, ultimo;
    ultimo = dim - 1;
    X[ultimo][0] = U[ultimo][ultimo];

    for(i = ultimo - 1; i >= 0; i--){
        double soma = 0;
        for(j = 1; j < dim; j++){
            soma += U[i][j] * X[j][0];
        }
        X[i][0] = (1 / U[i][i]) * (Y[i][0] - soma);
    }
//    imprime_matriz(X, dim, 1, "X substituido");
};

void solucao_linear(double **A, int dim, double **B, double **P, double **X){
    double **L, **U;
    double **Y;

    L = matriz_quadrada_nula(dim);
    U = matriz_quadrada_nula(dim);
    Y = matriz_nula(dim, 1);

    fatoracao_lu(A, dim, L, U, P);

    double **PB = matriz_nula(dim, 1);
//    double **PX = matriz_nula(dim, 1);

    PB = produto(P, B, dim, dim, dim, 1);
//    imprime_matriz(PB, dim, 1, "B pivotada");

    substituicao_ascendente(L, PB, dim, Y);

//    imprime_matriz(Y, dim, 1, "Y");

    substituicao_descendente(U, Y, dim, X);

//    imprime_matriz(X, dim, 1, "X nao pivotada");

//    PX = produto_quadradas(P, X, dim);
//    imprime_matriz(PX, dim, 1, "X pivotada");

//    #TODO Ver a melhor maneira de retornar a matriz resultado que está pivotada
}
