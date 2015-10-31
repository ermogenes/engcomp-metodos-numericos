#ifndef MATRIZES_H_INCLUDED
#define MATRIZES_H_INCLUDED

#include <stdbool.h>

double** matriz(int dim);
double** matriz_nula(int dim);
double** matriz_valores(int dim, double *m);
void imprime_matriz(double **M, int dim, char *identificador);

void fatoracao_lu(double **A, int dim, double **L, double **U, double **P);
bool confere_fatoracao_lu(double **A, int dim, double **L, double **U, double **P, double **L_ok, double **U_ok, double **P_ok);

#endif // MATRIZES_H_INCLUDED
