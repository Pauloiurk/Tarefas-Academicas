# Contagem de Números Pares em uma Árvore BST

Atividade Prática Avaliativa desenvolvida em **C**, com o objetivo de praticar o uso de **Árvores Binárias de Busca (BST)** e **recursividade**.

## Objetivo

Implementar uma função recursiva responsável por percorrer uma árvore BST e contar quantos nós possuem valores pares.

A árvore é construída utilizando os seguintes valores:

```text
50, 25, 70, 14, 35, 60, 81
```

## Estrutura da Árvore

A inserção dos valores resulta na seguinte árvore:

```text
        50
       /  \
     25    70
    / \    / \
   14  35 60  81
```

## Implementação

A função `contarPares()` realiza a contagem utilizando recursividade.

Primeiro é verificado o caso base, onde um nó `NULL` retorna `0`. Em seguida, é verificado se o valor do nó atual é par utilizando o operador módulo `%`. Por fim, são realizadas chamadas recursivas para as subárvores esquerda e direita.

```c
int contarPares(No* raiz) {
    if (raiz == NULL)
        return 0;

    int ehPar = (raiz->valor % 2 == 0);

    return ehPar + contarPares(raiz->esq) + contarPares(raiz->dir);
}
```

## Resultado

Para os valores inseridos:

```text
[50, 25, 70, 14, 35, 60, 81]
```

Os números pares encontrados são:

```text
50, 70, 14, 60
```

Portanto, o resultado obtido pelo programa é:

```text
Total de numeros pares calculados: 4
```

## Critérios Atendidos

- Tratamento do caso base com `raiz == NULL`;
- Identificação de números pares utilizando `% 2 == 0`;
- Percurso recursivo da subárvore esquerda;
- Percurso recursivo da subárvore direita;
- Totalização dos nós que possuem valores pares.

## Tecnologias Utilizadas

- Linguagem C
- GCC
- Visual Studio Code
- Git
- GitHub

## Autor

**Paulo Justus Iurk Neto**  
Ciência da Computação