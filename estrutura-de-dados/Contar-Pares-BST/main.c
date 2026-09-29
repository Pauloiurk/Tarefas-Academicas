#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* esq;
    struct No* dir;
} No;

No* criarNo(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);

    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);

    return raiz;
}

// =========================================================================
// SUA TAREFA: IMPLEMENTAR ESTA FUNÇÃO RECURSIVA SIMPLES (4 LINHAS)
// Dica: se o galho é NULL, retorna 0.
// Verifique se o no atual é par: (raiz->valor % 2 == 0)
// Some 1 (se for par) com os pares da esquerda e da direita.
// =========================================================================
int contarPares(No* raiz) {
    if (raiz == NULL)
        return 0;

    int ehPar = (raiz->valor % 2 == 0);

    return ehPar + contarPares(raiz->esq) + contarPares(raiz->dir);
}

int main(void) {
    No* raiz = NULL;

    // Inserindo: 50, 25, 70, 14, 35, 60, 81
    int valores[] = {50, 25, 70, 14, 35, 60, 81};

    for (int i = 0; i < 7; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    int totalPares = contarPares(raiz);

    printf("=== ATIVIDADE AVALIATIVA N2: CONTADOR DE PARES ===\n");
    printf("Valores inseridos: [50, 25, 70, 14, 35, 60, 81]\n");
    printf("Total de numeros pares calculados: %d\n", totalPares);
    printf("Resultado esperado: 4 (50, 70, 14, 60)\n");

    return 0;
}