#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINHA 500
#define MAX_ELEMENTOS 100

typedef struct Ponto {
    float x;
    float y;
    float distanciaOrigem;
} Ponto;

double calcularDistanciaOrigem(float x, float y) {
    return sqrt(x * x + y * y);
}

// Função para ordenar strings em ordem alfabética manualmente
void ordenarStrings(char strings[MAX_ELEMENTOS][MAX_LINHA], int numStrings) {
    for (int i = 0; i < numStrings - 1; i++) {
        for (int j = i + 1; j < numStrings; j++) {
            if (strcmp(strings[i], strings[j]) > 0) {
                char temp[MAX_LINHA];
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], temp);
            }
        }
    }
}

// Função para ordenar inteiros em ordem crescente manualmente
void ordenarInteiros(int inteiros[MAX_ELEMENTOS], int numInteiros) {
    for (int i = 0; i < numInteiros - 1; i++) {
        for (int j = i + 1; j < numInteiros; j++) {
            if (inteiros[i] > inteiros[j]) {
                int temp = inteiros[i];
                inteiros[i] = inteiros[j];
                inteiros[j] = temp;
            }
        }
    }
}

// Função para ordenar floats em ordem crescente manualmente
void ordenarFloats(float floats[MAX_ELEMENTOS], int numFloats) {
    for (int i = 0; i < numFloats - 1; i++) {
        for (int j = i + 1; j < numFloats; j++) {
            if (floats[i] > floats[j]) {
                float temp = floats[i];
                floats[i] = floats[j];
                floats[j] = temp;
            }
        }
    }
}

// Função para ordenar pontos por distância à origem manualmente
void ordenarPontos(Ponto pontos[MAX_ELEMENTOS], int numPontos) {
    for (int i = 0; i < numPontos - 1; i++) {
        for (int j = i + 1; j < numPontos; j++) {
            if (pontos[i].distanciaOrigem > pontos[j].distanciaOrigem) {
                Ponto temp = pontos[i];
                pontos[i] = pontos[j];
                pontos[j] = temp;
            }
        }
    }
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
        float floats[MAX_ELEMENTOS];
        Ponto pontos[MAX_ELEMENTOS];
        
        int numStrings = 0, numInteiros = 0, numFloats = 0, numPontos = 0;

        char *token = strtok(linha, " ");
        while (token != NULL) {
            // Identifica pontos no formato (x,y)
            if (sscanf(token, "(%f,%f)", &pontos[numPontos].x, &pontos[numPontos].y) == 2) {
                pontos[numPontos].distanciaOrigem = calcularDistanciaOrigem(pontos[numPontos].x, pontos[numPontos].y);
                numPontos++;
            }
            // Identifica floats
            else if (sscanf(token, "%f", &floats[numFloats]) == 1 && strchr(token, '.') != NULL) {
                numFloats++;
            }
            // Identifica inteiros
            else if (sscanf(token, "%d", &inteiros[numInteiros]) == 1) {
                numInteiros++;
            }
            // Identifica strings
            else {
                strcpy(strings[numStrings], token);
                numStrings++;
            }
            token = strtok(NULL, " ");
        }

        // Ordenação manual de cada categoria
        ordenarStrings(strings, numStrings);
        ordenarInteiros(inteiros, numInteiros);
        ordenarFloats(floats, numFloats);
        ordenarPontos(pontos, numPontos);

        // Escreve os resultados no arquivo de saída
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
            fprintf(arquivo_saida, "%.2f ", floats[i]);
        }
        fprintf(arquivo_saida, "p:");
        for (int i = 0; i < numPontos; i++) {
            fprintf(arquivo_saida, "(%.1f,%.1f) ", pontos[i].x, pontos[i].y);
        }
        fprintf(arquivo_saida, "\n");
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    return EXIT_SUCCESS;
}
