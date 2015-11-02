/*
Funções para trabalho com matrizes.

Author: Ermogenes Palacio
Date: 2015-11-02
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double** matriz(int dim){
    int i;
    double **M = malloc(sizeof(double *) * dim);
    for(i = 0; i < dim; i++){
        M[i] = malloc(sizeof(double) * dim);
    }
    return M;
}

void preenche_valor(double **M, int dim, double valor){
    int i, j;
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            M[i][j] = valor;
        }
    }
}

void preenche_identidade(double **M, int dim){
    int i, j;
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            M[i][j] = (i == j);
        }
    }
}

void carrega_valores(double **M, int dim, double *m){
    int i, j;
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            M[i][j] = ((double (*)[dim])m)[i][j];
        }
    }
}

double** matriz_nula(int dim){
    double **M = matriz(dim);
    preenche_valor(M, dim, 0);
    return M;
}

double** matriz_identidade(int dim){
    double **I = matriz(dim);
    preenche_identidade(I, dim);
    return I;
}

double** matriz_valores(int dim, double *m){
    double **M = matriz(dim);
    carrega_valores(M, dim, m);
    return M;
}

void imprime_matriz(double **M, int dim, char *identificador){
    int i, j;
    printf("\n--- %s ---\n", identificador);
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
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

double** produto(double** M1, double** M2, int dim){
    int i, j, k;
    double **produto = matriz(dim);
    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++)
            for(k = 0; k < dim; k++)
                produto[i][j] += M1[i][k] * M2[k][j];
    return produto;
}

void fatoracao_lu(double **A, int dim, double **L, double **U, double **P){
    preenche_valor(L, dim, 0);
    preenche_valor(U, dim, 0);

    matriz_pivo(A, P, dim);

    double **PA = produto(P, A, dim);

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
