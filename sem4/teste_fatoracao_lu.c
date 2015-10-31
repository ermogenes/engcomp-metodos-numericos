/*
Testa a implementação da fatoração LU.

Author: Ermogenes Palacio
Date: 2015-10-31
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

int main(void){

    double a[3][3] = {{1,3,5},{2,4,7},{1,1,0}};
    double l_correto[3][3] = {{1,0,0},{0.5,1,0},{0.5,-1,1}};
    double u_correto[3][3] = {{2,4,7},{0,1,1.5},{0,0,-2}};
    double p_correto[3][3] = {{0,1,0},{1,0,0},{0,0,1}};

    double **A, **P, **L, **U;
    double **P_correto, **L_correto, **U_correto;

    bool correto;

    A = matriz_valores(3, &a[0][0]);
    P = matriz_nula(3);
    L = matriz_nula(3);
    U = matriz_nula(3);
    L_correto = matriz_valores(3, &l_correto[0][0]);
    U_correto = matriz_valores(3, &u_correto[0][0]);
    P_correto = matriz_valores(3, &p_correto[0][0]);

    /*
    imprime_matriz(A, 3, "A");
    imprime_matriz(P, 3, "P");
    imprime_matriz(P_correto, 3, "P_correto");
    imprime_matriz(L, 3, "L");
    imprime_matriz(L_correto, 3, "L_correto");
    imprime_matriz(U, 3, "U");
    imprime_matriz(U_correto, 3, "U_correto");
    */

    fatoracao_lu(A, 3, L, U, P);

    correto = confere_fatoracao_lu(A, 3, L, U, P, L_correto, U_correto, P_correto);

    if (correto){
        printf("Fatoracao LU realizada com sucesso.");
    }else{
        printf("Fatoracao LU nao passou nos testes.");
    }

    free(A); A = NULL;
    free(P); P = NULL;
    free(L); L = NULL;
    free(U); U = NULL;

    return 0;
}

/*
double A_2[][4] = {{11,9,24,2},{1,5,2,6},{3,17,18,1},{2,5,7,1}};
double dim_2 = 4;
*/
