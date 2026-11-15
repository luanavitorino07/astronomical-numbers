
#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int bloco;
    struct no *prox;
} No;

struct lista {
    No *inicio;
    No *fim;
    int sinal;
    int tamanho;
};

static Lista *criar_lista_vazia(void) {
    Lista *lista = malloc(sizeof *lista);
    if (lista == NULL) return NULL;

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->sinal = 1;
    lista->tamanho = 0;

    return lista;
}

static int inserir_fim(Lista *lista, int bloco) {
    if (lista == NULL || bloco < 0 || bloco >= 10000) return 0;

    No *novo = malloc(sizeof *novo);
    if (novo == NULL) return 0;

    novo->bloco = bloco;
    novo->prox = NULL;

    if (lista->fim == NULL) {
        lista->inicio = novo;
    } else {
        lista->fim->prox = novo;
    }

    lista->fim = novo;
    lista->tamanho++;

    return 1;
}

void liberar_Lista(Lista *lista) {
    if (lista == NULL) return;

    No *atual = lista->inicio;

    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(lista);
}

Lista *criar_Lista(const char *texto) {
    if (texto == NULL || texto[0] == '\0') return NULL;

    size_t inicio = (texto[0] == '-') ? 1 : 0;
    size_t fim = strlen(texto);

    if (inicio == fim) return NULL;

    for (size_t i = inicio; i < fim; i++) {
        if (texto[i] < '0' || texto[i] > '9') return NULL;
    }

    Lista *lista = criar_lista_vazia();
    if (lista == NULL) return NULL;

    lista->sinal = (inicio == 1) ? -1 : 1;

    while (inicio < fim && texto[inicio] == '0') {
        inicio++;
    }

    if (inicio == fim) {
        if (!inserir_fim(lista, 0)) {
            liberar_Lista(lista);
            return NULL;
        }

        lista->sinal = 1;
        return lista;
    }

    while (fim > inicio) {
        int bloco = 0;
        int multiplicador = 1;
        size_t pos = fim;

        for (int digitos = 0; pos > inicio && digitos < 4; digitos++) {
            pos--;
            bloco += (texto[pos] - '0') * multiplicador;
            multiplicador *= 10;
        }

        if (!inserir_fim(lista, bloco)) {
            liberar_Lista(lista);
            return NULL;
        }

        fim = pos;
    }

    return lista;
}

static int comparar_modulos(const Lista *a, const Lista *b) {
    if (a->tamanho > b->tamanho) return 1;
    if (a->tamanho < b->tamanho) return -1;

    const No *noA = a->inicio;
    const No *noB = b->inicio;
    int res = 0;

    while (noA != NULL && noB != NULL) {
        if (noA->bloco > noB->bloco) {
            res = 1;
        } else if (noA->bloco < noB->bloco) {
            res = -1;
        }

        noA = noA->prox;
        noB = noB->prox;
    }

    return res;
}

int maior(const Lista *a, const Lista *b) {
    if (a == NULL || b == NULL) return -1;

    if (a->sinal > b->sinal) return 1;
    if (a->sinal < b->sinal) return 0;

    int res = comparar_modulos(a, b);

    if (a->sinal == -1) res = -res;

    return res == 1;
}

int menor(const Lista *a, const Lista *b) {
    if (a == NULL || b == NULL) return -1;

    if (a->sinal > b->sinal) return 0;
    if (a->sinal < b->sinal) return 1;

    int res = comparar_modulos(a, b);

    if (a->sinal == -1) res = -res;

    return res == -1;
}

int igual(const Lista *a, const Lista *b) {
    if (a == NULL || b == NULL) return -1;

    if (a->sinal != b->sinal) return 0;

    return comparar_modulos(a, b) == 0;
}

void imprimir_Lista(const Lista *lista) {
    if (lista == NULL || lista->inicio == NULL) return;

    size_t quantidade = (size_t)lista->tamanho;

    if (quantidade > (size_t)-1 / sizeof(No *)) return;

    const No **nos = malloc(quantidade * sizeof *nos);
    if (nos == NULL) return;

    const No *atual = lista->inicio;

    for (size_t i = 0; i < quantidade; i++) {
        nos[i] = atual;
        atual = atual->prox;
    }

    if (lista->sinal == -1) {
        putchar('-');
    }

    printf("%d", nos[quantidade - 1]->bloco);

    for (size_t i = quantidade - 1; i > 0; i--) {
        printf("%04d", nos[i - 1]->bloco);
    }

    free(nos);
}

static Lista *diferenca_modulos(const Lista *a, const Lista *b) {
    Lista *res = criar_lista_vazia();
    if (res == NULL) return NULL;

    const No *noA = a->inicio;
    const No *noB = b->inicio;

    int emprestimo = 0;
    No *ultimo_nao_zero = NULL;
    int tamanho_util = 0;

    while (noA != NULL) {
        int blocoB = 0;

        if (noB != NULL) {
            blocoB = noB->bloco;
            noB = noB->prox;
        }

        int total = noA->bloco - blocoB - emprestimo;
        emprestimo = 0;

        if (total < 0) {
            total += 10000;
            emprestimo = 1;
        }

        if (!inserir_fim(res, total)) {
            liberar_Lista(res);
            return NULL;
        }

        if (total != 0) {
            ultimo_nao_zero = res->fim;
            tamanho_util = res->tamanho;
        }

        noA = noA->prox;
    }

    if (ultimo_nao_zero == NULL) {
        No *primeiro = res->inicio;
        No *atual = primeiro->prox;

        primeiro->prox = NULL;

        while (atual != NULL) {
            No *proximo = atual->prox;
            free(atual);
            atual = proximo;
        }

        res->fim = primeiro;
        res->tamanho = 1;
    } else {
        No *atual = ultimo_nao_zero->prox;
        ultimo_nao_zero->prox = NULL;

        while (atual != NULL) {
            No *proximo = atual->prox;
            free(atual);
            atual = proximo;
        }

        res->fim = ultimo_nao_zero;
        res->tamanho = tamanho_util;
    }

    return res;
}

Lista *soma(const Lista *a, const Lista *b) {
    if (a == NULL || b == NULL) return NULL;

    Lista *res = NULL;

    if (a->sinal == b->sinal) {
        res = criar_lista_vazia();
        if (res == NULL) return NULL;

        res->sinal = a->sinal;

        const No *noA = a->inicio;
        const No *noB = b->inicio;

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

        if (vai_um != 0 && !inserir_fim(res, vai_um)) {
            liberar_Lista(res);
            return NULL;
        }
    } else {
        int comparacao = comparar_modulos(a, b);

        if (comparacao == 0) {
            res = criar_lista_vazia();
            if (res == NULL) return NULL;

            if (!inserir_fim(res, 0)) {
                liberar_Lista(res);
                return NULL;
            }

            return res;
        }

        if (comparacao > 0) {
            res = diferenca_modulos(a, b);

            if (res != NULL) {
                res->sinal = a->sinal;
            }
        } else {
            res = diferenca_modulos(b, a);

            if (res != NULL) {
                res->sinal = b->sinal;
            }
        }
    }

    if (res != NULL && res->tamanho == 1 &&
        res->inicio->bloco == 0) {
        res->sinal = 1;
    }

    return res;
}
