/*
Funções para trabalho com matrizes.

Author: Ermogenes Palacio
Date: 2015-10-31
*/

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

double** matriz_valores(int dim, double *m){
    double **M = matriz(dim);
    carrega_valores(M, dim, m);
    return M;
}

void imprime_matriz(double **M, int dim, char *identificador){
    int i, j;
    printf("%s\n", identificador);
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            printf("%f\t", M[i][j]);
        }
        printf("\n");
    }
};

bool matrizes_iguais(double **M1, double **M2, int dim){
    int i, j;
    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            if (M1[i][j]!=M2[i][j]){
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

void fatoracao_lu(double **A, int dim, double **L, double **U, double **P){
    while (0);
}
