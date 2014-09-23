
TL;DR
=====

O objetivo do EP é implementar um novo Shape no pbrt para renderizar
L-systems. Para isso, teremos que basicamente criar uma nova implementação da
interface Shape (core/shape.h), e torná-la acessível no interpretador da
entrada (função MakeShape em core.api.cpp).

L-systems
=========

São estruturas geométricas geradas a partir de gramáticas. Tipicamente servem
para gerar árvores e outras formas orgânicas e fractais. Vamos refrescar a
memória, uma gramática tem:

- Um alfabeto - são os símbolos com que ela trabalha
- Um conjunto de símbolos terminais - parte do alfabeto que "não expande"
- Um conjunto de regras - especificam como os símbolos expandem, exemplos:

  A -> BB ('A' expande em dois 'B's)

  A -> A+A ('A' expande recursivamente)
- Um símbolo inicial - as expansões começam daqui

Exemplo de gramática:

  - alfabeto = { A, B, C }
  - símbolos terminais = { C }
  - regras = { A -> BB, B -> CAC }
  - símbolo inicial = A

Expandindo ela, temos:
  1. A
  2. BB
  3. CACCAC
  4. CBBCCBBC
  5. CCACCACCCCACCACC
  6. etc

Para fazer L-Systems, usamos alguns símbolos com significados especiais, bem
parecido com aqueles programas "LOGO" no qual damos comandos a uma tartaruga
para desenhar formas geométricas.

* F: translate forward
* -: rotate left
* +: rotate right
* [: push transformation
* ]: pop transformation

Assim, se F traslada 10 unidade, + gira 90 graus, a sequência F+F+F+F faz um
quadrado.

Em 3D, tem mais símbolos para poder ter mais rotações. Veja nos slides da
quinta aula as convenções usadas. Também será preciso determinar o
"deslocamento unitário" e o "ângulo unitário" usado na gramática, a não ser
que usemos símbolos parametrizados (tem algo sobre isso nos slides também).

Classe Shape
============

No capítulo 3 do livro, é explicada a interface da classe. Você também pode
olhar direto no código, mas o capítulo explica melhor quais funções temos que
implementar e quais não. Particularmente, a seção 3.1.2 mostra como um Shape
pode ser composto por outros Shapes (que é o que queremos no EP).

O construtor da classe poderá receber uma string com a sequência que determina
a forma e os sub-shapes usados.

Interpretador
=============

Nessa parte do código, temos que acrescentar um if para tratar nosso Shape e
implementar uma função que converte os parâmetros recebidos do arquivo de cena
em uma gramática, para depois expandir ela o número de vezes que for
especificado e passar a string resultante para o construtor do nosso Shape.

