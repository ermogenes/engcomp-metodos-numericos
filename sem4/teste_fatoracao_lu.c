/*
Testa a implementação da fatoração LU.

Author: Ermogenes Palacio
Date: 2015-11-02;
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

void imprime_teste_fatoracao_lu(double **A, double **L_ok, double **U_ok, double **P_ok, int dim){
    bool correto;

    double **L, **U, **P;

    L = matriz_quadrada_nula(dim);
    U = matriz_quadrada_nula(dim);
    P = matriz_quadrada_nula(dim);

    printf("\n-------------------\n");
    printf("\nFatoracao LU: \n");
    imprime_matriz(A, dim, dim, "A = matriz");

    fatoracao_lu(A, dim, L, U, P);

    imprime_matriz(L, dim, dim, "L encontrado");
    imprime_matriz(L_ok, dim, dim, "L correto");
    imprime_matriz(U, dim, dim, "U encontrado");
    imprime_matriz(U_ok, dim, dim, "U correto");
    imprime_matriz(P, dim, dim, "P encontrado");
    imprime_matriz(P_ok, dim, dim, "P correto");

    correto = confere_fatoracao_lu(L, U, P, L_ok, U_ok, P_ok, dim);

    if (correto){
        printf("\nFatoracao LU executada com sucesso.\n");
    }else{
        printf("\nFatoracao LU nao passou nos testes.\n");
    }

    printf("\n-------------------\n");

    free(L); L = NULL;
    free(U); U = NULL;
    free(P); P = NULL;
}

void teste_fatoracao_3x3(){
    int dim = 3;
    double a[3][3] = {{1,3,5},{2,4,7},{1,1,0}};
    double l[3][3] = {{1,0,0},{0.5,1,0},{0.5,-1,1}};
    double u[3][3] = {{2,4,7},{0,1,1.5},{0,0,-2}};
    double p[3][3] = {{0,1,0},{1,0,0},{0,0,1}};

    double **A, **P, **L, **U;
    double **P_correto, **L_correto, **U_correto;

    A = matriz_valores_quadrada(dim, &a[0][0]);
    P = matriz_quadrada_nula(dim);
    L = matriz_quadrada_nula(dim);
    U = matriz_quadrada_nula(dim);
    L_correto = matriz_valores_quadrada(dim, &l[0][0]);
    U_correto = matriz_valores_quadrada(dim, &u[0][0]);
    P_correto = matriz_valores_quadrada(dim, &p[0][0]);

    fatoracao_lu(A, dim, L, U, P);

    imprime_teste_fatoracao_lu(A, L_correto, U_correto, P_correto, dim);

    free(A); A = NULL;
    free(P); P = NULL;
    free(L); L = NULL;
    free(U); U = NULL;
    free(P_correto); P_correto = NULL;
    free(L_correto); L_correto = NULL;
    free(U_correto); U_correto = NULL;
}

void teste_fatoracao_4x4(){
    int dim = 4;
    double a[4][4] = {{11,9,24,2},{1,5,2,6},{3,17,18,1},{2,5,7,1}};
    double l[4][4] = {{1.00000,0.00000,0.00000,0.00000},
                              {0.27273,1.00000,0.00000,0.00000},
                              {0.09091,0.28750,1.00000,0.00000},
                              {0.18182,0.23125,0.00360,1.00000}};
    double u[4][4] = {{11.00000,9.00000,24.00000,2.00000},
                              {0.00000,14.54545,11.45455,0.45455},
                              {0.00000,0.00000,-3.47500,5.68750},
                              {0.00000,0.00000,0.00000,0.51079}};
    double p[4][4] = {{1,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,1}};

    double **A, **P, **L, **U;
    double **P_correto, **L_correto, **U_correto;

    A = matriz_valores_quadrada(dim, &a[0][0]);
    P = matriz_quadrada_nula(dim);
    L = matriz_quadrada_nula(dim);
    U = matriz_quadrada_nula(dim);
    L_correto = matriz_valores_quadrada(dim, &l[0][0]);
    U_correto = matriz_valores_quadrada(dim, &u[0][0]);
    P_correto = matriz_valores_quadrada(dim, &p[0][0]);

    fatoracao_lu(A, dim, L, U, P);

    imprime_teste_fatoracao_lu(A, L_correto, U_correto, P_correto, dim);

    free(A); A = NULL;
    free(P); P = NULL;
    free(L); L = NULL;
    free(U); U = NULL;
    free(P_correto); P_correto = NULL;
    free(L_correto); L_correto = NULL;
    free(U_correto); U_correto = NULL;
}

void imprime_teste_solucao_linear(double **A, double **B, double **X_ok, int dim){
    bool correto;

    double **X, **P;

    X = matriz_nula(dim, 1);
    P = matriz_quadrada_nula(dim);

    printf("\n-------------------\n");
    printf("\nSolucao linear para o sistema: \n");
    imprime_matriz(A, dim, dim, "A = coeficientes das incognitas");
    imprime_matriz(B, dim, 1, "B = termos independentes");

    solucao_linear(A, dim, B, P, X);

    imprime_matriz(X, dim, 1, "X = resultado encontrado");
    imprime_matriz(X_ok, dim, 1, "X correto = resultado esperado");

    correto = confere_solucao_linear(X, X_ok, dim);

    if (correto){
        printf("\nSistema resolvido com sucesso.\n");
    }else{
        printf("\nSistema nao passou nos testes.\n");
    }

    printf("\n-------------------\n");

    free(P); P = NULL;
    free(X); X = NULL;
}

void teste_solucao_linear_2x2(){
    int dim = 2;
    double a[2][2] = {{1,1},{4,-1}};
    double b[2][1] = {{7},{3}};
    double x[2][1] = {{2},{5}};

    double **A, **B;
    double **X_correto;

    A = matriz_valores_quadrada(dim, &a[0][0]);
    B = matriz_valores(dim, 1, &b[0][0]);
    X_correto = matriz_valores(dim, 1, &x[0][0]);

    imprime_teste_solucao_linear(A, B, X_correto, dim);

    free(A); A = NULL;
    free(B); B = NULL;
    free(X_correto); X_correto = NULL;
}

void teste_solucao_linear_3x3(){
    int dim = 3;
    double a[3][3] = {{1,3,5},{2,4,7},{1,1,0}};
    double b[3][1] = {{0},{0},{0}};
    double x[3][1] = {{0},{0},{0}};

    double **A, **B;
    double **X_correto;

    A = matriz_valores_quadrada(dim, &a[0][0]);
    B = matriz_valores(dim, 1, &b[0][0]);
    X_correto = matriz_valores(dim, 1, &x[0][0]);

    imprime_teste_solucao_linear(A, B, X_correto, dim);

    free(A); A = NULL;
    free(B); B = NULL;
    free(X_correto); X_correto = NULL;
}

void teste_solucao_linear_4x4(){
    int dim = 4;
    double a[4][4] = {{2,-6,4,-2},{1,-3,4,3},{4,3,-2,3},{1,-4,3,3}};
    double b[4][1] = {{8},{6},{3},{9}};
    double x[4][1] = {{1},{-2},{-1},{1}};

    double **A, **B;
    double **X_correto;

    A = matriz_valores_quadrada(dim, &a[0][0]);
    B = matriz_valores(dim, 1, &b[0][0]);
    X_correto = matriz_valores(dim, 1, &x[0][0]);

    imprime_teste_solucao_linear(A, B, X_correto, dim);

    free(A); A = NULL;
    free(B); B = NULL;
    free(X_correto); X_correto = NULL;
}

int main(void){

    teste_fatoracao_3x3();
    teste_fatoracao_4x4();

    teste_solucao_linear_2x2();
    teste_solucao_linear_3x3();
    teste_solucao_linear_4x4();

    return 0;
}
