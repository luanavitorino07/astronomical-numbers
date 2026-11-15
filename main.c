
/*
    Emerson Camilo Pizarro Laquise  - 17983986
    Luana Assunção Vitorino         - 17906825
    Pedro de Freitas Sena           - 17864854
    Sarah Mendes Gurgel             - 14778859
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

static char *ler_linha(void) {
    size_t cap = 64;
    size_t tamanho = 0;

    char *texto = malloc(cap);
    if (!texto) return NULL;

    while (1) {
        if (cap - tamanho < 2) {
            cap *= 2;

            char *temp = realloc(texto, cap);
            if (!temp) {
                free(texto);
                return NULL;
            }

            texto = temp;
        }

        if (fgets(texto + tamanho, (int)(cap - tamanho), stdin) == NULL) {
            if (tamanho == 0) {
                free(texto);
                return NULL;
            }
            break;
        }

        tamanho += strlen(texto + tamanho);

        if (tamanho > 0 && texto[tamanho - 1] == '\n') {
            texto[--tamanho] = '\0';
            break;
        }

        if (feof(stdin)) break;
    }

    if (tamanho > 0 && texto[tamanho - 1] == '\r') {
        texto[--tamanho] = '\0';
    }

    return texto;
}

int main(void) {

    int n;
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++){

        char *linha = ler_linha();
        if (!linha) return 1;

        char *op = strtok(linha, " \t");
        char *numA = strtok(NULL, " \t");
        char *numB = strtok(NULL, " \t");

        if (!op || !numA || !numB) return 1;

        Lista *a = criar_Lista(numA);
        Lista *b = criar_Lista(numB);

        if (!a || !b){
            liberar_Lista(a);
            liberar_Lista(b);
            free(linha);
            return 1;
        }

        if(strcmp(op, "soma") == 0){
            Lista *res = soma(a, b);
            if (res){
                printf("Resultado:: ");
                imprimir_Lista(res);
                liberar_Lista(res);
            }
        }
        else if (strcmp(op, "maior") == 0){
            printf("Resultado:: %s\n", maior(a, b) ? "True" : "False");
        }
        else if (strcmp(op, "menor") == 0){
            printf("Resultado:: %s\n", menor(a, b) ? "True" : "False");
        }
        else if (strcmp(op, "igual") == 0){
            printf("Resultado:: %s\n", igual(a, b) ? "True" : "False");
        }

        liberar_Lista(a);
        liberar_Lista(b);
        free(linha);
    }

    return 0;
}
