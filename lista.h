#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>

/* Tipo opaco: a estrutura e os nos sao definidos em lista.c. */
typedef struct lista Lista;

/* Pessoa 1: estrutura e memoria */
Lista *criarLista(void);
int inserirInicio(Lista *lista, int bloco);
int inserirFim(Lista *lista, int bloco);
void liberarLista(Lista *lista);

/* Pessoa 2: conversao e impressao */
char *lerToken(FILE *entrada);
Lista *converterNumero(const char *texto);
void normalizarNumero(Lista *numero);
void imprimirNumero(const Lista *numero);

/* Pessoa 3: comparacao e subtracao */
int compararModulos(const Lista *a, const Lista *b);
int compararNumeros(const Lista *a, const Lista *b);
/* Precondicao: |a| >= |b|. Retorna modulo nao negativo. */
Lista *subtrairModulos(const Lista *a, const Lista *b);

/* Pessoa 4: soma */
Lista *somarModulos(const Lista *a, const Lista *b);
Lista *somarNumeros(const Lista *a, const Lista *b);

#endif
