"""
Encontra raízes de funções reais utilizando o Método da bisseção:

Ref: (https://pt.wikipedia.org/wiki/M%C3%A9todo_da_bisse%C3%A7%C3%A3o)
"""

__author__ = 'Ermogenes Palacio'

from datetime import datetime
from decimal import *
import math


##### Constantes

TOL = Decimal('0.00001')  # tolerância de erro desejada
MAX_ITER = 100  # número máximo de iterações


##### Funções principais


def raiz_aprox_intervalo_por_bissecao(f, a, b, t = TOL, max_iteracoes = MAX_ITER):
    """
    Calcula raízes de uma dada função em um dado intervalo pelo método da bisseção.

    :param f: função que será analizada
    :param a: intervalo inferior de análise da função
    :param b: intervalo superior de análise da função
    :param t: margem de tolerância
    :param max_iteracoes: número máximo de iterações
    :return: raíz aproximada da função, e lista de strings com tabela Markdown, para exibição
    """

    # Avalia a validade dos limites inferior e superior do intervalo.
    if not a < b:
        raise Exception("Intervalo inválido.")

    # String de saída (uma tabela Markdown)
    tabela_saida = []
    tabela_saida.append('*Tolerância*: `{:.0e}`, *número máximo de iterações*: `{}`'.format(t, max_iteracoes))
    tabela_saida.append(
        '\ni|limite inferior (a)|limite superior (b)|ponto médio (c)|f(c)|erro absoluto\n---|---|---|---|---|---'
    )

    # Loop de aproximação
    for i in range(1, max_iteracoes):

        # Calcula o ponto médio do intervalo
        c = (a + b) / 2

        # Calcula o valor da função no ponto médio
        f_c = f(c)

        # Calcula o erro absoluto
        erro = (b - a) / 2

        # Atualiza a tabela para saída
        tabela_saida.append('{}|{}|{}|{}|{}|{:.0e}'.format(i, a, b, c, f_c, erro))

        # Avalia se a raíz foi encontrada
        #   se f(c) = 0, c é raíz
        #   se o erro é menor que a tolerância dada, a aproximação é suficiente
        if f_c == 0 or erro < t:
            # Fim do algoritmo, a raíz aproximada é retornada
            return c, tabela_saida

        # Como não encontrou a raíz, calcula o próximo intervalo
        # Precisamos de f(a)
        f_a = f(a)

        # Divide o intervalo, método similar ao da busca binária
        #   Pelo Teorema de Bolzano, se f(a)f(c) > 0, existe raíz em [a,c]
        if f_a * f_c > 0:
            # Novo intervalo, na metade superior
            a = c
        else:
            # Novo intervalo, na metade inferior
            b = c

    # Loop terminou sem encontrar resultado
    raise Exception("Valor da função não encontrado.")


def encontra_raizes(f, descricao, a, b, t = TOL, max_iteracoes = MAX_ITER):
    """
    Helper para a função `raiz_aprox_intervalo_por_bissecao`.

    Exibe uma saída formatada (Markdown).
    """
    import timeit

    print(descricao, '\n====')
    print('Avaliando a função `f: [{},{}] -> |R, y = {}`, pelo método da bisseção:\n'.format(a, b, descricao))

    if not a < b:
        print('Intervalo inválido.')
        return None

    # Avalia se o intervalo dado possui raízes, pelo Teorema de Bolzano
    if f(a) * f(b) < 0:

        # Calcula a raíz aproximada, contando o tempo de execução
        inicio = timeit.default_timer()
        try:
            raiz, saida = raiz_aprox_intervalo_por_bissecao(f, a, b, t = TOL, max_iteracoes = MAX_ITER)
        except Exception as excecao:
            raiz = 'NÃO ENCONTRADA'
            saida = excecao
        finally:
            tempo_decorrido = timeit.default_timer() - inicio

        # Exibe resultado formatado
        for linha in saida: print(linha)
        print('Tempo de execução: {} (segundos)'.format(tempo_decorrido))
        print('### **Raíz aproximada encontrada**: {}'.format(raiz))
        print('#### **Truncado**:', Decimal(raiz).quantize(Decimal(TOL), rounding = ROUND_FLOOR),'\t**Arredondado**:', Decimal(raiz).quantize(Decimal(TOL), rounding = ROUND_05UP))
        with localcontext() as ctx:
            ctx.rounding = ROUND_DOWN
        with localcontext() as ctx:
            ctx.rounding = ROUND_FLOOR

    else:
        print('Não é possível garantir que há raízes no intervalo.')


##### Exemplos de funções que podem ser utilizadas pela aplicação


def x_cubo_menos_x_menos_dois(x):
    """
    Ref: https://pt.wikipedia.org/wiki/M%C3%A9todo_da_bisse%C3%A7%C3%A3o#Exemplo
    """
    return


##### Programa principal

if True :#__name__ == 'main':

    # cabeçalho
    print('# Aproximação de raízes de funções pelo método da bisseção')
    print('Criado para estudos da disciplina Métodos Numéricos, semana 2, videoaula 5.')

    # corpo
    encontra_raizes(lambda x: x ** 3 - x - 2, 'x³ - x - 2', 1, 2)
    encontra_raizes(lambda x: x ** 3 - 9 * x ** 2 + 23 * x - 15, 'x³ - 9x² + 23x - 15', 2, 4)
    encontra_raizes(lambda x: x ** 3 - 9 * x ** 2 + 23 * x - 15, 'x³ - 9x² + 23x - 15', 1.5, 3.3)
    encontra_raizes(lambda x: math.sin(x), 'sen x', 1, 4)
    encontra_raizes(lambda x: math.log(x), 'ln x', 0.5, 5)
    encontra_raizes(lambda x: x ** 2, 'x²', -1, 1)
    encontra_raizes(lambda x: x ** 3, 'x³', -1, math.pi)
    encontra_raizes(lambda x: math.sqrt(x)-1, '(\u221Ax) - 1', 0, 3)

    # rodapé

    print('''
Créditos
---

**Exercícios**: [Univesp](http://engenharia.cursos.univesp.br/)

**Implementação**: Ermogenes Palacio - Twitter: [@ermogenes](http://www.twitter.com/ermogenes)

Gerado em {:%d/%m/%Y, às %Hh%Mmin%Ss}.
'''.format(datetime.now())
    )