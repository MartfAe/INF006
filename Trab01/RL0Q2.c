#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINHA 500
#define MAX_ELEMENTOS 100

typedef struct Ponto {
    double x;
    double y;
    double distanciaOrigem;
} Ponto;

double calcularDistanciaOrigem(double x, double y) {
    return sqrt(x * x + y * y);
}

int main() {
    FILE *arquivo_entrada = fopen("L0Q2.in", "r");
    FILE *arquivo_saida = fopen("L0Q2.out", "w");

    if (arquivo_entrada == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        return EXIT_FAILURE;
    }
    if (arquivo_saida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        fclose(arquivo_entrada);
        return EXIT_FAILURE;
    }

    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, arquivo_entrada) != NULL) {
        char strings[MAX_ELEMENTOS][MAX_LINHA];
        int inteiros[MAX_ELEMENTOS];
        double floats[MAX_ELEMENTOS];
        Ponto pontos[MAX_ELEMENTOS];
        
        int numStrings = 0, numInteiros = 0, numFloats = 0, numPontos = 0;

        char *token = strtok(linha, " ");
        while (token != NULL) {
            if (sscanf(token, "(%lf,%lf)", &pontos[numPontos].x, &pontos[numPontos].y) == 2) {
                pontos[numPontos].distanciaOrigem = calcularDistanciaOrigem(pontos[numPontos].x, pontos[numPontos].y);
                numPontos++;
            } else if (sscanf(token, "%lf", &floats[numFloats]) == 1 && strchr(token, '.') != NULL) {
                numFloats++;
            } else if (sscanf(token, "%d", &inteiros[numInteiros]) == 1) {
                numInteiros++;
            } else {
                strcpy(strings[numStrings], token);
                numStrings++;
            }
            token = strtok(NULL, " ");
        }

        fprintf(arquivo_saida, "str:");
        for (int i = 0; i < numStrings; i++) {
            fprintf(arquivo_saida, "%s ", strings[i]);
        }
        fprintf(arquivo_saida, "int:");
        for (int i = 0; i < numInteiros; i++) {
            fprintf(arquivo_saida, "%d ", inteiros[i]);
        }
        fprintf(arquivo_saida, "float:");
        for (int i = 0; i < numFloats; i++) {
            fprintf(arquivo_saida, "%.2lf ", floats[i]);
        }
        fprintf(arquivo_saida, "p:");
        for (int i = 0; i < numPontos; i++) {
            fprintf(arquivo_saida, "(%.1lf,%.1lf) ", pontos[i].x, pontos[i].y);
        }
        fprintf(arquivo_saida, "\n");
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    return EXIT_SUCCESS;
}
