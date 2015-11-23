"""
Integração numérica pelo método de Simpson.

Referências:
https://en.wikipedia.org/wiki/Simpson%27s_rule
http://rosettacode.org/wiki/Numerical_integration
"""


def integracao_simpson(f, a, b, n):
    """Calcula uma aproximação numérica para a integral definida
    de da função f dada, entre a e b, com n subintervalos (pares),
    pela regra de Simpson"""

    if n % 2:
        raise ValueError("n deve ser par (n=%d)" % n)

    h = (b - a) / n
    s = f(a) + f(b)

    for i in range(1, n, 2):
        s += 4 * f(a + i * h)
    for i in range(2, n-1, 2):
        s += 2 * f(a + i * h)

    return s * h / 3


def teste_integracao(f, a, b, n, nome_funcao, resultado_exato):

    saida = []
    saida.append("\n--- %s ---" % nome_funcao)

    try:
        integral = integracao_simpson(f, a, b, n)
        saida.append("Integral definida de %d a %d, em %d passos" % (a, b, n))
        saida.append("Estimada em %f" % integral)
        saida.append("O resultado exato é %f" % resultado_exato)

    except ValueError as e:
        saida.append(str(e))
        return '\n'.join(saida)

    finally:
        return '\n'.join(saida)


# Testando

print("Integração numérica pelo método de Simpson")

testes = [
    [lambda x:x**3, 0, 1, 1000, "x ao cubo (x^3)", 0.25],
    [lambda x:1/x, 1, 100, 1000, "inverso de x (1/x)", 4.605170],
    [lambda x:x, 0, 5000, 5000000, "identidade (x)", 12500000],
    [lambda x:x, 0, 6000, 6000000, "identidade (x)", 18000000],
]

for t in testes:
    print(teste_integracao(*t))