"""
Script que exibe alguns resultados esperados nos exercícios de Métodos Numéricos, da Semana 1, Univesp.

Os resultados são gerados em Markdown (https://daringfireball.net/projects/markdown/).
"""

__author__ = 'Ermogenes Palacio'

from decimal import Decimal, Context, ROUND_FLOOR
from datetime import date, datetime

############ cabeçalho

print('## Gabarito pessoal')
print('### Métodos Numéricos - Semana 1')
print('Resultados esperados de alguns exercícios da semana 1, para conferência.')

############ definições

letras = list('abcde')

def truncar_precisao_4(numero):
    return Context(prec=4, rounding=ROUND_FLOOR).create_decimal(numero)

def arredondar_precisao_4(numero):
    return numero.quantize(Context(prec=4, rounding=ROUND_FLOOR).create_decimal(numero))

def erro_absoluto(real, truncado):
    return real - truncado

def erro_relativo(real, truncado):
    return (real - truncado) / real

############ 1

x = [2, 10, 79, 107, 583]
saida = zip(letras, x)

print(
'''
### Exercício 1
Conversão decimal-binário

i|Decimal|Binário
---|---|---'''
)

for l, n in saida:
    print('{}|`{}`|`{:b}`'.format(l, n, n))

########### 2

b = [0b1, 0b101, 0b100, 0b1011, 0b111001]
saida = zip(letras, b)

print(
'''
### Exercício 2
Conversão binário-decimal

i|Binário|Decimal
---|---|---'''
)

for l, b in saida:
    print('{}|`{:b}`|`{}`'.format(l, b, b))

########### 5

x = [
    Decimal('0.834456'),
    Decimal('2.634305'),
    Decimal('0.103457'),
    Decimal('14.780340'),
    Decimal('25.546774'),
    ]

saida = zip(
            letras,
            x,
            [truncar_precisao_4(xn) for xn in x],
            [arredondar_precisao_4(xn) for xn in x]
        )

print(
'''
### Exercício 5
Base `10`, mantissa `4`, expoente `[-3,3]`

Representar por arredondamento e por truncamento

i|Real|Truncado|Arredondado
---|---|---|---'''
)

for l, n, nt, nr in saida:
    print('{}|`{}`|`{}`|`{}`'.format(l, n, nt, nr))

########### 6

expr = [
    'x1 + x2',
    'x2 x3',
    'x1 + x4 / x2',
    'x5 - x4',
    'x1 + x2 + x3',
    ]

real = [
    x[0] + x[1],
    x[1] * x[2],
    x[0] + x[3] / x[1],
    x[4] - x[3],
    x[0] + x[1] + x[2],
]

tr4 = truncar_precisao_4

truncado = [
    tr4(tr4(x[0]) + tr4(x[1])),
    tr4(tr4(x[1]) * tr4(x[2])),
    tr4(tr4(x[0]) + tr4(tr4(x[3]) / tr4(x[1]))),
    tr4(tr4(x[4]) - tr4(x[3])),
    tr4(tr4(x[0]) + tr4(x[1]) + tr4(x[2])),
]

tab_erro = list(zip(
    real,
    truncado
    ))

e_abs = [erro_absoluto(r, t) for r, t in tab_erro]
e_rel = [erro_relativo(r, t) for r, t in tab_erro]

saida = zip(
            letras,
            expr,
            real,
            truncado,
            e_abs,
            e_rel,
        )

print(
'''
### Exercício 6
Erro absoluto e relativo

i|Expressão|Resultado real|Truncado|Erro absoluto|Erro relativo
---|---|---|---|---|---'''
)

for l, e, r, t, ea, er in saida:
    print('{}|`{}`|`{}`|`{}`|`{}`|`{:.2e}`'.format(l, e, r, t, ea, er))

############# rodapé

print('''
### Créditos

**Exercícios**: [Univesp](http://engenharia.cursos.univesp.br/)

**Respostas**: Ermogenes Palacio - Twitter: [@ermogenes](http://www.twitter.com/ermogenes)

Gerado em {:%d/%m/%Y, às %Hh%Mmin%Ss}.
'''.format(datetime.now())
)
