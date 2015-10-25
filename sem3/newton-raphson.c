/*
Implementa��o do m�todo de Newton-Raphson
para a aproxima��o de ra�zes de fun��es reais.

Author: Ermogenes Palacio
Date: 2015-10-22
*/

#include <stdio.h>   // fun��es de IO
#include <stdbool.h> // tipo booleano
#include <math.h>    // fun��es matem�ticas

const int    MAX_ITER = 200; // n�mero m�ximo de itera��es
const double ERROR_FLAG = 999999; // flag que indica que n�o convergiu
const double PADRAO_EPSILON = 1e-14; // m�ximo denominador desejado
const double PADRAO_TOLERANCIA = 1e-6; // maior erro aceit�vel

/* f(x) */
double f(double x){
    return pow(x, 3);
}

/* f'(x) */
double f_linha(double x){
    return 3 * pow(x, 2);
}

/* C�lculo das ra�zes */
double newtonRaphson(double x, double epsilon_f, double epsilon_x){
    /*
    double x: valor inicial
    double epsilon_f: menor denominador aceit�vel
    double epsilon_x: maior erro aceit�vel
    */

    int i; // contador de itera��es

    double x0 = x; // aproxima��o atual de x
    double y; // f(x)
    double y_linha; // f'(x)
    double x1; // pr�xima aproxima��o de x
    double erro_x; // erro atual
    double y_linha_abs; // magnitude do denominador atual

    bool convergiu = false; // flag para controle de converg�ncia

    printf("## M�todo de Newton-Raphson:\n\n");
    printf("Fun��o: `x^3`\n\n");
    printf("### ITERA��ES:\n\n");
    printf("`x = %.2f`\t`e_f = %.1e`\t`e_y = %.1e`\n\n", x, epsilon_f, epsilon_x);

    printf("`i`|`x`|`f(x)`|`f'(x)`|Erro\n");
    printf("---|---|---|---|---\n");

    // iterando at� o m�ximo permitido
    for(i = 1; i <= MAX_ITER; i++){

        // calcula y e y' no ponto atual
        y = f(x0);
        y_linha = f_linha(x0);

        // calcula magnitude do denominador
        y_linha_abs = fabs(y_linha);

        printf("`%d`|`%.4f`|`%.8f`|`%.4f`|`%.1e`\n", i, x0, y, y_linha, y_linha_abs);

        // atingiu o menor denominador aceit�vel ent�o n�o converge
        if(y_linha_abs < epsilon_f){
            break;
        }

        // calcula a pr�xima aproxima��o de x
        x1 = x0 - y / y_linha;

        // calcula o erro da aproxima��o
        erro_x = fabs(x1 - x0);

        // se erro menor que a toler�ncia, convergiu
        if(erro_x < epsilon_x){
            convergiu = true;
            break;
        }

        // assume a pr�xima aproxima��o como a atual
        x0 = x1;
    }

    // usa c�digo de erro para caso de n�o converg�ncia
    if(!convergiu){
        x1 = ERROR_FLAG;
    }

    // retorna o valor encontrado
    return x1;
}

int main()
{
    double result = newtonRaphson(1, PADRAO_EPSILON, PADRAO_TOLERANCIA);

    if(result == ERROR_FLAG){
        printf("Nao convergiu.");
    }
    else{
        printf("\nAproxima��o encontrada: `%.5f`", result);
    }
    return 0;
}
