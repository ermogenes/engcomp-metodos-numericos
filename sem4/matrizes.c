/*
Funções para trabalho com matrizes.

Author: Ermogenes Palacio
Date: 2015-11-02
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const double TOLERANCE = 0.0001;

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
            printf("%.2f\t", M[i][j]);
        }
        printf("\n");
    }
};

bool iguais(double x, double y){
    return (fabs(x - y) <= TOLERANCE);
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
    for(i = 0; i < dim; i++){
        Y[i][0] = B[i][0];
        for (j = 0; j < i; j++){
            Y[i][0] -= L[i][j] * Y[j][0];
        }
        Y[i][0] /= L[i][i];
    }
};

void substituicao_descendente(double **U, double **Y, int dim, double **X){
    int i, j;
    for(i = dim - 1; i >= 0; i--){
        X[i][0] = Y[i][0];
        for(j = i + 1; j < dim; j++){
            X[i][0] -= U[i][j] * X[j][0];
        }
        X[i][0] /= U[i][i];
    }
};

void solucao_linear(double **A, int dim, double **B, double **P, double **X){
    double **L, **U;
    double **Y;
    double **PB;

    L = matriz_quadrada_nula(dim);
    U = matriz_quadrada_nula(dim);
    Y = matriz_nula(dim, 1);
    PB = matriz_nula(dim, 1);

    fatoracao_lu(A, dim, L, U, P);

    PB = produto(P, B, dim, dim, dim, 1);

    substituicao_ascendente(L, PB, dim, Y);
    substituicao_descendente(U, Y, dim, X);
}

bool matrizes_iguais(double **M1, double **M2, int l, int c){
    int i, j;
    for(i = 0; i < l; i++)
        for(j = 0; j < c; j++)
            if (!iguais(M1[i][j], M2[i][j]))
                return false;
    return true;
}

bool confere_fatoracao_lu(double **L, double **U, double **P, double **L_ok, double **U_ok, double **P_ok, int dim){
    return (
        matrizes_iguais(L, L_ok, dim, dim) &&
        matrizes_iguais(U, U_ok, dim, dim) &&
        matrizes_iguais(P, P_ok, dim, dim)
    );
}

bool confere_solucao_linear(double **X, double **X_ok, int dim){
    return matrizes_iguais(X, X_ok, dim, 1);
}

void constroi_matriz_interpolacao(double **X, int dim, double **A){
    int i, j;
    for(i = 0; i < dim; i++){
        A[i][0] = 1;
        A[i][1] = X[i][0];
        for(j = 2; j < dim; j++)
            A[i][j] = pow(A[i][1], j);
    }
}

void polinomio_interpolador(double **X, double **Fx, int dim, double **Pol){
    double **A, **Pivo;

    A = matriz_quadrada_nula(dim);
    Pivo = matriz_nula(dim, dim);

    constroi_matriz_interpolacao(X, dim, A);

	solucao_linear(A, dim, Fx, Pivo, Pol);
}

void imprime_polinomio(double **P, int grau, char *identificador){
    int i;
    printf("\n--- %s ---\n", identificador);
    for(i = grau - 1; i >= 0; i--)
        printf("%+.2f * x^%d ", P[i][0], i);
    printf("\n");
}

bool confere_interpolacao_polinomial(double **P, double **P_ok, int dim){
    return matrizes_iguais(P, P_ok, dim, 1);
}
