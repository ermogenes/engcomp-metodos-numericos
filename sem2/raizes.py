"""
Encontra raízes aproximadas de funções reais.

Ref:
(https://pt.wikipedia.org/wiki/M%C3%A9todo_da_bisse%C3%A7%C3%A3o)
(https://pt.wikipedia.org/wiki/M%C3%A9todo_da_posi%C3%A7%C3%A3o_falsa)
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


def raiz_aprox_intervalo_por_posicao_falsa(f, a, b, t = TOL, max_iteracoes = MAX_ITER):
    """
    Calcula raízes de uma dada função em um dado intervalo pelo método da posição falsa.

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
        '\ni|limite inferior (a)|limite superior (b)|ponto falso (c)|f(c)|erro absoluto\n---|---|---|---|---|---'
    )

    # Loop de aproximação
    for i in range(1, max_iteracoes):

        # Precisamos de f(a) e f(b)
        f_a = f(a)
        f_b = f(b)

        # Calcula novo ponto para dividir o intervalo
        c = b - f_b * (b - a) / (f_b - f_a)

        # Calcula o valor da função no ponto encontrado
        f_c = f(c)

        # Calcula o erro
        erro = abs(c - b)

        # Atualiza a tabela para saída
        tabela_saida.append('{}|{}|{}|{}|{}|{:.0e}'.format(i, a, b, c, f_c, erro))

        # Avalia se a raíz foi encontrada
        #   se f(c) = 0, c é raíz
        #   se o erro é menor que a tolerância dada, a aproximação é suficiente
        if f_c == 0 or erro < t:
            # Fim do algoritmo, a raíz aproximada é retornada
            return c, tabela_saida

        # Como não encontrou a raíz, calcula o próximo intervalo

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
    Helper para as funções:
    * `raiz_aprox_intervalo_por_bissecao`
    * `raiz_aprox_intervalo_por_posicao_falsa`

    Exibe saída formatada (Markdown).
    """
    import timeit

    # Título
    print(descricao, '\n====')

    # Método da bisseção

    print('##### Avaliando a função `f: [{},{}] -> |R, y = {}`, pelo **método da bisseção**:\n'.format(a, b, descricao))

    if not a < b:
        print('Intervalo inválido.')
        return None

    # Avalia se o intervalo dado possui raízes, pelo Teorema de Bolzano
    if f(a) * f(b) < 0:

        # Calcula a raíz aproximada, contando o tempo de execução
        inicio = timeit.default_timer()
        try:
            raiz_bissecao, saida = raiz_aprox_intervalo_por_bissecao(f, a, b, t = TOL, max_iteracoes = MAX_ITER)
        except Exception as excecao:
            raiz_bissecao = None
            raiz_bissecao_truncado = None
            raiz_bissecao_arredondado = None
            saida.append(str(excecao))
        finally:
            tempo_decorrido_bissecao = timeit.default_timer() - inicio

        # Exibe resultado formatado
        for linha in saida: print(linha)
        print('Tempo de execução: {} (segundos)'.format(tempo_decorrido_bissecao))

        # Efetua os arredondamentos para quadro comparativo
        if raiz_bissecao:
            raiz_bissecao_truncado = Decimal(raiz_bissecao).quantize(Decimal(TOL), rounding = ROUND_FLOOR)
            raiz_bissecao_arredondado = Decimal(raiz_bissecao).quantize(Decimal(TOL), rounding = ROUND_05UP)

    else:
        print('Não é possível garantir que há raízes no intervalo.')
        tempo_decorrido_bissecao = None
        raiz_bissecao = None
        raiz_bissecao_truncado = None
        raiz_bissecao_arredondado = None

    # Método da posição falsa

    print('\n---')
    print('##### Avaliando a função `f: [{},{}] -> |R, y = {}`, pelo **método da posição falsa**:\n'.format(a, b, descricao))

    if not a < b:
        print('Intervalo inválido.')
        return None

    # Avalia se o intervalo dado possui raízes, pelo Teorema de Bolzano
    if f(a) * f(b) < 0:

        # Calcula a raíz aproximada, contando o tempo de execução
        inicio = timeit.default_timer()
        try:
            raiz_posicao_falsa, saida = raiz_aprox_intervalo_por_posicao_falsa(f, a, b, t = TOL, max_iteracoes = MAX_ITER)
        except Exception as excecao:
            raiz_posicao_falsa = None
            raiz_posicao_falsa_truncado = None
            raiz_posicao_falsa_arredondado = None
            saida.append(str(excecao))
        finally:
            tempo_decorrido_posicao_falsa = timeit.default_timer() - inicio

        # Exibe resultado formatado
        for linha in saida: print(linha)
        print('Tempo de execução: {} (segundos)'.format(tempo_decorrido_posicao_falsa))

        # Efetua os arredondamentos para quadro comparativo
        if raiz_posicao_falsa:
            raiz_posicao_falsa_truncado = Decimal(raiz_posicao_falsa).quantize(Decimal(TOL), rounding = ROUND_FLOOR)
            raiz_posicao_falsa_arredondado = Decimal(raiz_posicao_falsa).quantize(Decimal(TOL), rounding = ROUND_05UP)

    else:
        print('Não é possível garantir que há raízes no intervalo.')
        tempo_decorrido_posicao_falsa = None
        raiz_posicao_falsa = None
        raiz_posicao_falsa_truncado = None
        raiz_posicao_falsa_arredondado = None

    # Comparativo entre métodos

    print('\n---')
    print('##### Comparativo entre métodos:')
    print('\nMétodo|Raíz aproximada|Truncado|Arredondado|Tempo|Comparativo')
    print('---|---|---|---|---|---:')

    # Formatação dos valores para o quadro

    tempo_bissecao = None
    comparativo_bissecao = None
    tempo_posicao_falsa = None
    comparativo_posicao_falsa = None

    if raiz_bissecao:
        tempo_bissecao = '{:.6f}s'.format(tempo_decorrido_bissecao)
        comparativo_bissecao = '1x'
        if raiz_posicao_falsa:
            tempo_posicao_falsa = '{:.6f}s'.format(tempo_decorrido_posicao_falsa)
            comparativo_posicao_falsa = '~{:.1f}x'.format(tempo_decorrido_posicao_falsa/tempo_decorrido_bissecao)
    else:
        tempo_bissecao = None
        comparativo_bissecao = None
        if raiz_posicao_falsa:
            tempo_posicao_falsa = '{:.6f}s'.format(tempo_decorrido_posicao_falsa)
            comparativo_posicao_falsa = '1x'.format(tempo_decorrido_posicao_falsa)

    raiz_bissecao = '--' if raiz_bissecao is None else raiz_bissecao
    raiz_bissecao_truncado = '--' if raiz_bissecao_truncado is None else raiz_bissecao_truncado
    raiz_bissecao_arredondado = '--' if raiz_bissecao_arredondado is None else raiz_bissecao_arredondado
    tempo_bissecao = '--' if tempo_bissecao is None else tempo_bissecao
    comparativo_bissecao = '--' if comparativo_bissecao is None else comparativo_bissecao

    raiz_posicao_falsa = '--' if raiz_posicao_falsa is None else raiz_posicao_falsa
    raiz_posicao_falsa_truncado = '--' if raiz_posicao_falsa_truncado is None else raiz_posicao_falsa_truncado
    raiz_posicao_falsa_arredondado = '--' if raiz_posicao_falsa_arredondado is None else raiz_posicao_falsa_arredondado
    tempo_posicao_falsa = '--' if tempo_posicao_falsa is None else tempo_posicao_falsa
    comparativo_posicao_falsa = '--' if comparativo_posicao_falsa is None else comparativo_posicao_falsa

    # Exibe linhas do quadro comparativo

    print('Bisseção|{}|{}|{}|{}|{}'.format(
        raiz_bissecao, raiz_bissecao_truncado, raiz_bissecao_arredondado,
        tempo_bissecao, comparativo_bissecao
    ))
    print('Posição falsa|{}|{}|{}|{}|{}'.format(
        raiz_posicao_falsa, raiz_posicao_falsa_truncado, raiz_posicao_falsa_arredondado,
        tempo_posicao_falsa, comparativo_posicao_falsa
    ))


##### Programa principal

if __name__ == '__main__':

    # cabeçalho
    print('# Aproximação de raízes de funções')
    print('Criado para estudos da disciplina Métodos Numéricos, semana 2.')

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