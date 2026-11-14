#include "lista.h"
#include <stdlib.h>
#include <string.h>

/* Estruturas internas compartilhadas pelas funcoes deste arquivo. */
typedef struct no {
    int bloco;
    struct no *prox;
} No;

struct lista {
    No *inicio;
    int sinal;   /* +1 ou -1; zero sempre com sinal +1 */
    int tamanho; /* quantidade de blocos */
};

/* PESSOA 1 — Estrutura e gerenciamento de memoria */
/* Implementar: criarLista, inserirInicio, inserirFim, liberarLista */

/* PESSOA 2 — Leitura, conversao, normalizacao e impressao */
/* Implementar: lerToken, converterNumero, normalizarNumero, imprimirNumero */

/* PESSOA 3 — Comparacao e subtracao */
/* Implementar: compararModulos, compararNumeros, subtrairModulos */

/* PESSOA 4 — Soma */
/* Implementar: somarModulos, somarNumeros */
