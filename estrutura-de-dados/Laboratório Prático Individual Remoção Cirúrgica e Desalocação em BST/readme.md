# Laboratório Prático — Remoção e Desalocação em BST

## Descrição

Atividade individual da disciplina de Estrutura de Dados, desenvolvida em linguagem C, com o objetivo de implementar a remoção de nós em uma Árvore Binária de Busca (BST) e realizar a desalocação de memória.

## Questão 1 — Três casos de remoção

**Caso 1 — Nó folha (20):** o nó é liberado utilizando `free()` e a função retorna `NULL`, atualizando o ponteiro esquerdo do nó 30.

**Caso 2 — Nó com um filho (30):** após a remoção do nó 20, o nó 30 possui apenas o filho direito 40. A função libera o nó 30 e retorna o endereço do nó 40, permitindo atualizar o ponteiro esquerdo do nó 50.

**Caso 3 — Nó com dois filhos (50):** o sucessor em-ordem é o nó 60, menor elemento da subárvore direita. Sua chave é copiada para a raiz e o nó 60 original é removido para evitar duplicidade.

## Questão 2 — Implementação

A função `remover()` utiliza recursividade para localizar o nó desejado e tratar os três casos de exclusão, preservando a propriedade de ordenação da BST.

Os nós removidos são desalocados utilizando `free()`.

## Questão 3 — Desalocação em pós-ordem

A função `destruirArvore()` percorre a subárvore esquerda, depois a direita e, por último, libera o nó atual.

Essa ordem é necessária porque liberar o pai antes de acessar os filhos causaria acesso à memória já desalocada, resultando em comportamento indefinido.

## Compilação e execução

Compilar utilizando GCC:

```bash
gcc -std=c99 -Wall -Wextra main.c -o main.exe
```

Executar no PowerShell:

```powershell
.\main.exe
```

## Resultados dos testes

| Teste | Percurso em-ordem |
|---|---|
| Árvore original | 20 30 40 50 60 70 80 |
| Remoção do nó 20 | 30 40 50 60 70 80 |
| Remoção do nó 30 | 40 50 60 70 80 |
| Remoção da raiz 50 | 20 30 40 60 70 80 |

O teste da remoção da raiz 50 utiliza uma nova árvore original.

## Tecnologias

- Linguagem C
- GCC
- Visual Studio Code
- Git e GitHub