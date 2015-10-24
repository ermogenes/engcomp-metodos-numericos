/*
Implementação do método de Newton-Raphson
para a aproximação de raízes de funções reais.

Author: Ermogenes Palacio
Date: 2015-10-22
*/

#include <stdio.h>   // funções de IO
#include <stdbool.h> // tipo booleano
#include <math.h>    // funções matemáticas

const int    MAX_ITER = 200; // número máximo de iterações
const double ERROR_FLAG = 999999; // flag que indica que não convergiu
const double PADRAO_EPSILON = 1e-14; // máximo denominador desejado
const double PADRAO_TOLERANCIA = 1e-6; // maior erro aceitável

/* f(x) */
double f(double x){
	return pow(x, 3);
}

/* f'(x) */
double f_linha(double x){
	return 3 * pow(x, 2);
}

/* Cálculo das raízes */
double newtonRaphson(double x, double epsilon_f, double epsilon_x){
    /*
    double x: valor inicial
    double epsilon_f: menor denominador aceitável
    double epsilon_x: maior erro aceitável
    */

    int i; // contador de iterações

    double x0 = x; // aproximação atual de x
    double y; // f(x)
    double y_linha; // f'(x)
    double x1; // próxima aproximação de x
    double erro_x; // erro atual
    double y_linha_abs; // magnitude do denominador atual

    bool convergiu = false; // flag para controle de convergência

    printf("## Método de Newton-Raphson:\n\n");
    printf("Função: `x^3`\n\n");
    printf("### ITERAÇÕES:\n\n");
    printf("`x = %.2f`\t`e_f = %.1e`\t`e_y = %.1e`\n\n", x, epsilon_f, epsilon_x);

    printf("`i`|`x`|`f(x)`|`f'(x)`|Erro\n");
    printf("---|---|---|---|---\n");

    // iterando até o máximo permitido
    for(i = 1; i <= MAX_ITER; i++){

        // calcula y e y' no ponto atual
        y = f(x0);
        y_linha = f_linha(x0);

        // calcula magnitude do denominador
        y_linha_abs = fabs(y_linha);

        printf("`%d`|`%.4f`|`%.8f`|`%.4f`|`%.1e`\n", i, x0, y, y_linha, y_linha_abs);

        // atingiu o menor denominador aceitável então não converge
        if(y_linha_abs < epsilon_f){
            break;
        }

        // calcula a próxima aproximação de x
        x1 = x0 - y / y_linha;

        // calcula o erro da aproximação
        erro_x = fabs(x1 - x0);

        // se erro menor que a tolerância, convergiu
        if(erro_x < epsilon_x){
            convergiu = true;
            break;
        }

        // assume a próxima aproximação como a atual
        x0 = x1;
	}

    // usa código de erro para caso de não convergência
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
        printf("\nAproximação encontrada: `%.5f`", result);
    }
    return 0;
}
