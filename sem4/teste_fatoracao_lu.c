/*
Testa a implementação da fatoração LU.

Author: Ermogenes Palacio
Date: 2015-11-02;
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

void teste_fatoracao_3x3(){
    double **A, **P, **L, **U;

    double **P_correto, **L_correto, **U_correto;

    bool correto;

    printf("\n-------------------\n");
    printf("Teste 1: matriz 3x3");
    printf("\n-------------------\n\n");

    double a[3][3] = {{1,3,5},{2,4,7},{1,1,0}};
    double l_correto[3][3] = {{1,0,0},{0.5,1,0},{0.5,-1,1}};
    double u_correto[3][3] = {{2,4,7},{0,1,1.5},{0,0,-2}};
    double p_correto[3][3] = {{0,1,0},{1,0,0},{0,0,1}};

    A = matriz_valores_quadrada(3, &a[0][0]);
    P = matriz_quadrada_nula(3);
    L = matriz_quadrada_nula(3);
    U = matriz_quadrada_nula(3);
    L_correto = matriz_valores_quadrada(3, &l_correto[0][0]);
    U_correto = matriz_valores_quadrada(3, &u_correto[0][0]);
    P_correto = matriz_valores_quadrada(3, &p_correto[0][0]);

    fatoracao_lu(A, 3, L, U, P);

    imprime_matriz(A, 3, 3, "A");
    imprime_matriz(P, 3, 3, "P");
    imprime_matriz(L, 3, 3, "L");
    imprime_matriz(U, 3, 3, "U");

    correto = confere_fatoracao_lu(A, 3, L, U, P, L_correto, U_correto, P_correto);

    if (correto){
        printf("\nFatoracao LU realizada com sucesso.\n");
    }else{
        printf("\nFatoracao LU nao passou nos testes.\n");
    }

    free(A); A = NULL;
    free(P); P = NULL;
    free(L); L = NULL;
    free(U); U = NULL;
    free(P_correto); P_correto = NULL;
    free(L_correto); L_correto = NULL;
    free(U_correto); U_correto = NULL;
}

void teste_fatoracao_4x4(){
    double **A, **P, **L, **U;

    double **P_correto, **L_correto, **U_correto;

    bool correto;

    printf("\n-------------------\n");
    printf("Teste 2: matriz 4x4");
    printf("\n-------------------\n\n");

    double a[4][4] = {{11,9,24,2},{1,5,2,6},{3,17,18,1},{2,5,7,1}};
    double l_correto_2[4][4] = {{1.00000,0.00000,0.00000,0.00000},
                              {0.27273,1.00000,0.00000,0.00000},
                              {0.09091,0.28750,1.00000,0.00000},
                              {0.18182,0.23125,0.00360,1.00000}};
    double u_correto_2[4][4] = {{11.00000,9.00000,24.00000,2.00000},
                              {0.00000,14.54545,11.45455,0.45455},
                              {0.00000,0.00000,-3.47500,5.68750},
                              {0.00000,0.00000,0.00000,0.51079}};
    double p_correto_2[4][4] = {{1,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,1}};

    A = matriz_valores_quadrada(4, &a[0][0]);
    P = matriz_quadrada_nula(4);
    L = matriz_quadrada_nula(4);
    U = matriz_quadrada_nula(4);
    L_correto = matriz_valores_quadrada(4, &l_correto_2[0][0]);
    U_correto = matriz_valores_quadrada(4, &u_correto_2[0][0]);
    P_correto = matriz_valores_quadrada(4, &p_correto_2[0][0]);

    fatoracao_lu(A, 4, L, U, P);

    imprime_matriz(A, 4, 4, "A");
    imprime_matriz(P, 4, 4, "P");
    imprime_matriz(L, 4, 4, "L");
    imprime_matriz(U, 4, 4, "U");

    correto = confere_fatoracao_lu(A, 4, L, U, P, L_correto, U_correto, P_correto);

    if (correto){
        printf("\nFatoracao LU realizada com sucesso.\n");
    }else{
        printf("\nFatoracao LU nao passou nos testes.\n");
    }

    free(A); A = NULL;
    free(P); P = NULL;
    free(L); L = NULL;
    free(U); U = NULL;
    free(P_correto); P_correto = NULL;
    free(L_correto); L_correto = NULL;
    free(U_correto); U_correto = NULL;
}

void teste_resolucao_3x3(){
//    double a[3][3] = {{1,4,52},{22,110,-3},{22,2,14}};
//    double b[3][1] = {{57},{134},{38}};

    double a[3][3] = {{1,3,5},{2,4,7},{1,1,0}};
    //double b[3][1] = {{222},{333},{444}};
    double b[3][1] = {{0},{0},{0}};
    //double b[3][1] = {{1},{1},{1}};

    double **A, **B, **X, **P;

    A = matriz_valores_quadrada(3, &a[0][0]);
    B = matriz_valores(3, 1, &b[0][0]);
    X = matriz_nula(3, 1);
    P = matriz_quadrada_nula(3);

    printf("\n-------------------\n");
    printf("\nSolucao linear para o sistema: \n");
    printf("\n-------------------\n");

    printf("x1\t\tx2\t\tx3\t\t\tb\n");
    int i;
    for(i = 0; i < 3; i++){
        printf("%f\t%f\t%f\t=\t%f\n", A[i][0], A[i][1], A[i][2], B[i][0]);
    }
    printf("\n-------------------\n\n");

    solucao_linear(A, 3, B, P, X);

    imprime_matriz(A, 3, 3, "A = Incognitas");
    imprime_matriz(B, 3, 1, "B = Termos independentes");
    imprime_matriz(X, 3, 1, "X = Resultado");
    imprime_matriz(P, 3, 3, "P = Pivo");

    free(A); A = NULL;
    free(B); B = NULL;
    free(X); X = NULL;
    free(P); P = NULL;

}

void teste_resolucao_4x4(){
    double a[4][4] = {{4,2,-1,1},{8,4,2,-2},{1,4,2,-2},{2,1,-2,6}};
    double b[4][1] = {{6},{10},{3},{8}};

    double **A, **B, **X, **P;

    A = matriz_valores_quadrada(4, &a[0][0]);
    B = matriz_valores(4, 1, &b[0][0]);
    X = matriz_nula(4, 1);
    P = matriz_quadrada_nula(4);

    printf("\n-------------------\n");
    printf("\nSolucao linear para o sistema: \n");
    printf("\n-------------------\n");

    printf("x1\t\tx2\t\tx3\t\tx4\t\t\tb\n");
    int i;
    for(i = 0; i < 4; i++){
        printf("%f\t%f\t%f\t%f\t=\t%f\n", A[i][0], A[i][1], A[i][2], A[i][3], B[i][0]);
    }
    printf("\n-------------------\n\n");

    solucao_linear(A, 4, B, P, X);

    imprime_matriz(A, 4, 4, "A = Incognitas");
    imprime_matriz(B, 4, 1, "B = Termos independentes");
    imprime_matriz(X, 4, 1, "X = Resultado");
    imprime_matriz(P, 4, 4, "P = Pivo");

    free(A); A = NULL;
    free(B); B = NULL;
    free(X); X = NULL;
    free(P); P = NULL;

}

int main(void){

    teste_fatoracao_3x3();
    teste_fatoracao_4x4();

    teste_resolucao_3x3();
    teste_resolucao_4x4();

    return 0;
}
