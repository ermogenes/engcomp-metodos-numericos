/*
Testa a implementação da fatoração LU.

Author: Ermogenes Palacio
Date: 2015-11-02;
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

int main(void){

    double **A, **P, **L, **U;
    double **P_correto, **L_correto, **U_correto;

    bool correto;

    printf("\n-------------------\n\n");
    printf("Teste 1: matriz 3x3");
    printf("\n-------------------\n\n");

    double a[3][3] = {{1,3,5},{2,4,7},{1,1,0}};
    double l_correto[3][3] = {{1,0,0},{0.5,1,0},{0.5,-1,1}};
    double u_correto[3][3] = {{2,4,7},{0,1,1.5},{0,0,-2}};
    double p_correto[3][3] = {{0,1,0},{1,0,0},{0,0,1}};

    A = matriz_valores(3, &a[0][0]);
    P = matriz_nula(3);
    L = matriz_nula(3);
    U = matriz_nula(3);
    L_correto = matriz_valores(3, &l_correto[0][0]);
    U_correto = matriz_valores(3, &u_correto[0][0]);
    P_correto = matriz_valores(3, &p_correto[0][0]);

    fatoracao_lu(A, 3, L, U, P);

    imprime_matriz(A, 3, "A");
    imprime_matriz(P, 3, "P");
    imprime_matriz(L, 3, "L");
    imprime_matriz(U, 3, "U");

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

    printf("\n-------------------\n\n");
    printf("Teste 2: matriz 4x4");
    printf("\n-------------------\n\n");

    double a_2[4][4] = {{11,9,24,2},{1,5,2,6},{3,17,18,1},{2,5,7,1}};
    double l_correto_2[4][4] = {{1.00000,0.00000,0.00000,0.00000},
                              {0.27273,1.00000,0.00000,0.00000},
                              {0.09091,0.28750,1.00000,0.00000},
                              {0.18182,0.23125,0.00360,1.00000}};
    double u_correto_2[4][4] = {{11.00000,9.00000,24.00000,2.00000},
                              {0.00000,14.54545,11.45455,0.45455},
                              {0.00000,0.00000,-3.47500,5.68750},
                              {0.00000,0.00000,0.00000,0.51079}};
    double p_correto_2[4][4] = {{1,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,1}};

    A = matriz_valores(4, &a_2[0][0]);
    P = matriz_nula(4);
    L = matriz_nula(4);
    U = matriz_nula(4);
    L_correto = matriz_valores(4, &l_correto_2[0][0]);
    U_correto = matriz_valores(4, &u_correto_2[0][0]);
    P_correto = matriz_valores(4, &p_correto_2[0][0]);

    fatoracao_lu(A, 4, L, U, P);

    imprime_matriz(A, 4, "A");
    imprime_matriz(P, 4, "P");
    imprime_matriz(L, 4, "L");
    imprime_matriz(U, 4, "U");

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

    return 0;
}
