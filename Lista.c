#include "Lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct no {
    int bloco;
    struct no *prox;
} No;

struct lista {
    No *inicio;
    int sinal;   // 1 ou -1
    int tamanho; // quantidade de blocos 
};


//FALTANDO:
//criar lista, inserir fim, liberar lista 



//COMPARAÇÕES
/*
retorna
 1 = maior
-1 = menor
 0 = igual
*/
static int comparar_modulos(const Lista *a, const Lista *b){
    if (a->tamanho > b->tamanho) return 1;
    if (a->tamanho < b->tamanho) return -1;

    No *noA = a->inicio;
    No *noB = b->inicio;

    int res = 0;

    while(noA != NULL && noB != NULL) {
        if (noA->bloco > noB->bloco) res = 1;
        else if(noA->bloco < noB->bloco) res = -1;

        noA = noA->prox;
        noB = noB->prox;
    }

    return res;
}


int maior(const Lista *a, const Lista *b){
    if (!a || !b) return -1;

    if (a->sinal > b->sinal) return 1;
    if (a->sinal < b->sinal) return 0;

    int res = comparar_modulos(a, b);
    if (a->sinal == -1) res = -res;

    return res == 1;
}

int menor(const Lista *a, const Lista *b){
    if (!a || !b) return -1;

    if (a->sinal > b->sinal) return 0;
    if (a->sinal < b->sinal) return 1;

    int res = comparar_modulos(a, b);
    if (a->sinal == -1) res = -res;

    return res == -1;
}

int igual(const Lista *a, const Lista *b){
    if (!a || !b) return -1;

    if (a->sinal != b->sinal) return 0;

    return comparar_modulos(a, b) == 0;
}





//IMPRIMIR
static void imprimir_bloco(No *no){
    if (!no) return;

    imprimir_bloco(no->prox);
    printf("%d", no->bloco);

    if (no->prox == NULL) {
        printf("%d", no->bloco);
    } else {
        imprimir_bloco(no->prox);
        printf("%04d", no->bloco);
    }
}

void imprimir_Lista(const Lista *Lista) {
    if (!Lista) return;

    if (Lista->sinal == -1) printf("-");
    if (!Lista->inicio){
        printf("0\n");
        return;
    }

    imprimir_bloco(Lista->inicio);
    printf("\n");
}


//SOMA
static Lista *diferenca_modulos(const Lista *a, const Lista *b){
    Lista *res = malloc(sizeof(Lista));
    if (!res) return NULL;

    res->inicio = NULL;
    res->sinal = 1;
    res->tamanho = 0;

    No *noA = a->inicio;
    No *noB = b->inicio;

    int emprestimo = 0;

    while (noA != NULL){
        int blocoA = noA->bloco;
        int blocoB = 0;

        if (noB != NULL){
            blocoB = noB->bloco;
            noB = noB->prox;   
        }

        int total = blocoA - blocoB - emprestimo;
        emprestimo = 0;

        if (total < 0){
            total += 10000;
            emprestimo = 1;
        }

        if (!inserir_fim(res, total)) {
            liberar_Lista(res);
            return NULL;
        }

        noA = noA->prox;
    }

    while (res->tamanho > 1) {
        No *atual = res->inicio;
        No *anterior = NULL;

        while (atual->prox != NULL) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual->bloco != 0) break;

        free(atual);
        anterior->prox = NULL;
        res->tamanho--;
    }

    return res;
}


Lista *soma(const Lista *a, const Lista *b) {
    if (a == NULL || b == NULL) return NULL;

    Lista *res = NULL;

    //se tiverem sinais iguais
    if (a->sinal == b->sinal) {
        res = malloc(sizeof(Lista));
        if (!res) return NULL;

        res->inicio = NULL;
        res->sinal = a->sinal;
        res->tamanho = 0;

        No *noA = a->inicio;
        No *noB = b->inicio;

        int vai_um = 0;

        while (noA != NULL || noB != NULL) {
            int blocoA = 0;
            int blocoB = 0;

            if (noA != NULL) {
                blocoA = noA->bloco;
                noA = noA->prox;
            }

            if (noB != NULL) {
                blocoB = noB->bloco;
                noB = noB->prox;
            }

            int total = blocoA + blocoB + vai_um;

            if (!inserir_fim(res, total % 10000)) {
                liberar_Lista(res);
                return NULL;
            }

            vai_um = total / 10000;
        }

        if (vai_um != 0) {
            if (!inserir_fim(res, vai_um)) {
                liberar_Lista(res);
                return NULL;
            }
        }
    }
    else {                //se tiver sinais diferentes 
        int comparacao = comparar_modulos(a, b);

        if (comparacao == 0) {
            res = malloc(sizeof(Lista));
            if (!res) return NULL;

            res->inicio = NULL;
            res->sinal = 1;
            res->tamanho = 0;

            if (!inserir_fim(res, 0)) {
                liberar_Lista(res);
                return NULL;
            }

            return res;
        }

        if (comparacao > 0) {
            res = diferenca_modulos(a, b);
            if (res != NULL) res->sinal = a->sinal;

        } else {
            res = diferenca_modulos(b, a);
            if (res != NULL) res->sinal = b->sinal;
        }
    }

    if (res != NULL &&
        res->tamanho == 1 &&
        res->inicio->bloco == 0) {
        res->sinal = 1;
    }

    return res;
}


