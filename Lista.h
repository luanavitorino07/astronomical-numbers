#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;

Lista *criar_Lista(const char *texto);
Lista *soma(const Lista *a, const Lista *b);

//retorna 1 ou 0
int maior(const Lista *a, const Lista *b);
int menor(const Lista *a, const Lista *b);
int igual(const Lista *a, const Lista *b);


/* Imprime o número no formato decimal */
void imprimir_Lista(const Lista *Lista);

/* Libera a memória utilizada pelo número */
void liberar_Lista(Lista *Lista);

#endif
