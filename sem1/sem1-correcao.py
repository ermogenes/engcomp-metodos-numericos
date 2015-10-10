"""
Script que exibe alguns resultados esperados nos exercícios de Métodos Numéricos, da Semana 1, Univesp.

Os resultados são gerados em Markdown (https://daringfireball.net/projects/markdown/).
"""

__author__ = 'Ermogenes Palacio'

from decimal import Decimal, ROUND_FLOOR
from datetime import date, datetime

############ cabeçalho

print('## Gabarito pessoal')
print('### Métodos Numéricos - Semana 1')
print('Resultados esperados de alguns exercícios da semana 1, para conferência.')

letras = list('abcde')

############ 1

n = [2, 10, 79, 107, 583]
saida = zip(letras, n)

print(
'''
### Exercício 1
Conversão decimal-binário

|Decimal|Binário
---|---|---'''
)

for l, x in saida:
    print('{}|`{}`|`{:b}`'.format(l, x, x))

########### 2

b = [0b1, 0b101, 0b100, 0b1011, 0b111001]
saida = zip(letras, b)

print(
'''
### Exercício 2
Conversão binário-decimal

|Binário|Decimal
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
            [xn.quantize(Decimal('1.0000')) for xn in x],
            [xn.quantize(Decimal('1.0000'), rounding=ROUND_FLOOR) for xn in x]
        )

print(
'''
### Exercício 5
Base `10`, mantissa `4`, expoente `[-3,3]`

Representar por arredondamento e por truncamento

|Real|Arredondado|Truncado
---|---|---|---'''
)

for l, x, xr, xt in saida:
    print('{}|`{}`|`{}`|`{}`'.format(l, x, xr, xt))


############# rodapé

print('''
### Créditos

**Exercícios**: [Univesp](http://engenharia.cursos.univesp.br/)

**Respostas**: Ermogenes Palacio - Twitter: [@ermogenes](http://www.twitter.com/ermogenes)

Gerado em {}.
'''.format(datetime.now().strftime("%d/%m/%Y, às %Hh%Mmin%Ss")))
