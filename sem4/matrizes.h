#ifndef MATRIZES_H_INCLUDED
#define MATRIZES_H_INCLUDED

#include <stdbool.h>

double** matriz_nula(int l, int c);
double** matriz_quadrada_nula(int dim);
double** matriz_identidade(int dim);
double** matriz_valores(int l, int c, double *m);
double** matriz_valores_quadrada(int dim, double *m);

void imprime_matriz(double **M, int l, int c, char *identificador);
void imprime_polinomio(double **M, int l, char *identificador);

void fatoracao_lu(double **A, int dim, double **L, double **U, double **P);
bool confere_fatoracao_lu(double **L, double **U, double **P, double **L_ok, double **U_ok, double **P_ok, int dim);

void solucao_linear(double **A, int dim, double **B, double **P, double **X);
bool confere_solucao_linear(double **X, double **X_ok, int dim);

void polinomio_interpolador(double **X, double **Fx, int dim, double **Pol);
bool confere_interpolacao_polinomial(double **P, double **P_ok, int dim);

#endif // MATRIZES_H_INCLUDED
