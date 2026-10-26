
#include <stdio.h>
#include <stdlib.h>

/*
 * LABORATORIO PRATICO INDIVIDUAL
 * Remocao Cirurgica e Desalocacao em BST
 *
 * Disciplina: Estrutura de Dados
 * Linguagem: C
 *
 * Objetivo:
 * Implementar os tres casos de remocao em uma
 * Arvore Binaria de Busca (BST) e realizar a
 * desalocacao completa da memoria em pos-ordem.
 */

/* Estrutura de um no da arvore */
typedef struct No {
    int chave;
    struct No *esquerda;
    struct No *direita;
} No;

/* Cria um novo no na memoria Heap */
No* criarNo(int chave) {
    No* novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }

    novo->chave = chave;
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

/* Insere um valor respeitando a propriedade BST */
No* inserir(No* raiz, int chave) {
    if (raiz == NULL) {
        return criarNo(chave);
    }

    if (chave < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, chave);
    }
    else if (chave > raiz->chave) {
        raiz->direita = inserir(raiz->direita, chave);
    }

    return raiz;
}

/* Exibe os valores em ordem crescente */
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        emOrdem(raiz->direita);
    }
}

/* Localiza o menor no de uma subarvore */
No* menorNo(No* raiz) {
    No* atual = raiz;

    while (atual != NULL && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }

    return atual;
}

/*
 * QUESTAO 1 - RASTREIO TEORICO
 *
 * CASO 1 - REMOCAO DO NO 20:
 *
 * O no 20 e uma folha, pois nao possui filhos.
 * Ao remove-lo, a funcao free() libera sua memoria.
 * Em seguida, retorna NULL para atualizar o ponteiro
 * esquerda do no 30, evitando acesso a memoria invalida.
 *
 * CASO 2 - REMOCAO DO NO 30:
 *
 * Considerando que o no 20 ja foi removido,
 * o no 30 possui apenas o filho direito 40.
 *
 * A funcao guarda o endereco do no 40,
 * libera a memoria do no 30 e retorna o
 * ponteiro para o filho 40.
 *
 * A chamada recursiva atualiza o ponteiro
 * esquerda do no 50, fazendo-o apontar
 * diretamente para o no 40.
 *
 * CASO 3 - REMOCAO DA RAIZ 50:
 *
 * Considerando a arvore original, o no 50
 * possui dois filhos.
 *
 * O sucessor em-ordem e o no 60, pois ele
 * e o menor elemento da subarvore direita.
 *
 * A chave 60 e copiada para a raiz.
 * Depois, o no 60 original e removido
 * recursivamente e sua memoria liberada.
 *
 * Dessa forma, a BST continua ordenada
 * e nao existem duas copias da chave 60.
 */

/*
 * QUESTAO 2 - FUNCAO REMOVER
 *
 * Implementacao recursiva dos tres casos
 * de exclusao de nos em uma BST.
 */
No* remover(No* raiz, int chave) {
    if (raiz == NULL) {
        return NULL;
    }

    /* Busca o valor na arvore */
    if (chave < raiz->chave) {
        raiz->esquerda = remover(raiz->esquerda, chave);
    }
    else if (chave > raiz->chave) {
        raiz->direita = remover(raiz->direita, chave);
    }
    else {

        /* CASO 1: No folha */
        if (raiz->esquerda == NULL &&
            raiz->direita == NULL) {

            free(raiz);
            return NULL;
        }

        /* CASO 2: Apenas filho direito */
        if (raiz->esquerda == NULL) {
            No* filho = raiz->direita;

            free(raiz);
            return filho;
        }

        /* CASO 2: Apenas filho esquerdo */
        if (raiz->direita == NULL) {
            No* filho = raiz->esquerda;

            free(raiz);
            return filho;
        }

        /* CASO 3: No com dois filhos */
        {
            No* sucessor = menorNo(raiz->direita);

            /* Copia a chave do sucessor */
            raiz->chave = sucessor->chave;

            /* Remove o sucessor original */
            raiz->direita = remover(
                raiz->direita,
                sucessor->chave
            );
        }
    }

    return raiz;
}

/*
 * QUESTAO 3 - DESTRUICAO COMPLETA DA ARVORE
 *
 * A desalocacao utiliza o percurso em pos-ordem:
 *
 * 1. Destruir a subarvore esquerda.
 * 2. Destruir a subarvore direita.
 * 3. Liberar a memoria do no atual.
 *
 * JUSTIFICATIVA TECNICA:
 *
 * A raiz possui ponteiros para seus filhos.
 * Por isso, os filhos precisam ser visitados
 * antes que a memoria da raiz seja liberada.
 *
 * Se free(raiz) fosse executado primeiro,
 * acessar raiz->esquerda ou raiz->direita
 * posteriormente causaria acesso a memoria
 * ja liberada, resultando em comportamento
 * indefinido.
 *
 * A pos-ordem garante que todos os descendentes
 * sejam desalocados antes do no pai.
 */
void destruirArvore(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    destruirArvore(raiz->esquerda);
    destruirArvore(raiz->direita);

    free(raiz);
}

/*
 * FUNCAO AUXILIAR
 * Monta a arvore de referencia da atividade.
 *
 *             50
 *           /    \
 *         30      70
 *        /  \    /  \
 *       20  40  60  80
 */
No* montarArvore(void) {
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int i;
    No* raiz = NULL;

    for (i = 0; i < 7; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    return raiz;
}

/*
 * FUNCAO PRINCIPAL
 * Executa os testes solicitados na atividade.
 */
int main(void) {
    No* raiz = NULL;

    printf("====================================\n");
    printf(" LABORATORIO PRATICO - BST EM C\n");
    printf("====================================\n\n");

    /* Montagem da arvore original */
    raiz = montarArvore();

    printf("Arvore original (em-ordem):\n");
    emOrdem(raiz);
    printf("\n\n");

    /*
     * TESTE 1 - REMOCAO DE NO FOLHA
     */
    printf("CASO 1 - Removendo o no 20\n");

    raiz = remover(raiz, 20);

    printf("Arvore apos remocao:\n");
    emOrdem(raiz);
    printf("\n\n");

    /*
     * TESTE 2 - REMOCAO COM UM FILHO
     */
    printf("CASO 2 - Removendo o no 30\n");

    raiz = remover(raiz, 30);

    printf("Arvore apos remocao:\n");
    emOrdem(raiz);
    printf("\n\n");

    /*
     * Destruir a arvore atual para iniciar
     * o terceiro teste com a arvore original.
     */
    destruirArvore(raiz);
    raiz = NULL;

    /*
     * TESTE 3 - REMOCAO COM DOIS FILHOS
     */
    raiz = montarArvore();

    printf("CASO 3 - Removendo a raiz 50\n");

    raiz = remover(raiz, 50);

    printf("Arvore apos remocao:\n");
    emOrdem(raiz);
    printf("\n\n");

    /*
     * QUESTAO 3 - DESALOCACAO FINAL
     */
    printf("Destruindo a arvore...\n");

    destruirArvore(raiz);
    raiz = NULL;

    printf("Memoria da arvore liberada.\n");
    printf("Programa finalizado com sucesso.\n");

    return 0;
}
