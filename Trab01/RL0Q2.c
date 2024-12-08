//Ana Emília Lobo, matricula 20241160001

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
    char strPonto[50];  // Variável para armazenar a string do ponto
} Ponto;

// Função para calcular a distância Euclidiana de um ponto à origem
float calcularDistanciaOrigem(float x, float y) {
    return sqrt(x * x + y * y);
}

// Função para ordenar strings em ordem alfabética
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

// Função para ordenar inteiros em ordem crescente
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

// Função para ordenar floats em ordem crescente
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

// Função para ordenar pontos pela distância à origem
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

    if (arquivo_entrada == NULL || arquivo_saida == NULL) {
        perror("Erro ao abrir arquivos");
        return EXIT_FAILURE;
    }

    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, arquivo_entrada)) {
        linha[strcspn(linha, "\n")] = 0; // Remove o '\n' do final da linha

        char strings[MAX_ELEMENTOS][MAX_LINHA];
        int inteiros[MAX_ELEMENTOS], intCount = 0, stringCount = 0, floatCount = 0, coordCount = 0;
        float floats[MAX_ELEMENTOS];
        Ponto pontos[MAX_ELEMENTOS];

        char *token = strtok(linha, " ");
        while (token) {
            // Identificar pontos no formato (x,y)
            if (sscanf(token, "(%f,%f)", &pontos[coordCount].x, &pontos[coordCount].y) == 2) {
                strcpy(pontos[coordCount].strPonto, token);  // Armazena o ponto como string
                pontos[coordCount].distanciaOrigem = calcularDistanciaOrigem(pontos[coordCount].x, pontos[coordCount].y);
                coordCount++;
            }
            // Identificar inteiros (números inteiros)
            else if (strspn(token, "0123456789-") == strlen(token)) {
                inteiros[intCount++] = atoi(token);
            }
            // Identificar floats (números decimais)
            else if (strspn(token, "0123456789.-") == strlen(token)) {
                floats[floatCount++] = atof(token);
            }
            // Identificar strings
            else {
                strcpy(strings[stringCount++], token);
            }
            token = strtok(NULL, " ");
        }

        // Ordenação das categorias
        ordenarStrings(strings, stringCount);
        ordenarInteiros(inteiros, intCount);
        ordenarFloats(floats, floatCount);
        ordenarPontos(pontos, coordCount);

        // Formatação da saída
        int isFirst = 1;  // Variável para controlar a primeira impressão

        if (stringCount > 0) {
            if (!isFirst) fprintf(arquivo_saida, " ");  // Adiciona espaço se não for a primeira categoria
            fprintf(arquivo_saida, "str:");
            for (int i = 0; i < stringCount; i++) {
                fprintf(arquivo_saida, "%s ", strings[i]);
            }
            isFirst = 0;
        }

        if (intCount > 0) {
            if (!isFirst) fprintf(arquivo_saida, " ");  // Adiciona espaço se não for a primeira categoria
            fprintf(arquivo_saida, "int:");
            for (int i = 0; i < intCount; i++) {
                fprintf(arquivo_saida, "%d ", inteiros[i]);
            }
            isFirst = 0;
        }

        if (floatCount > 0) {
            if (!isFirst) fprintf(arquivo_saida, " ");  // Adiciona espaço se não for a primeira categoria
            fprintf(arquivo_saida, "float:");
            for (int i = 0; i < floatCount; i++) {
                fprintf(arquivo_saida, "%.2f ", floats[i]);
            }
            isFirst = 0;
        }

        if (coordCount > 0) {
            if (!isFirst) fprintf(arquivo_saida, " ");  // Adiciona espaço se não for a primeira categoria
            fprintf(arquivo_saida, "p:");
            for (int i = 0; i < coordCount; i++) {
                fprintf(arquivo_saida, "%s ", pontos[i].strPonto);
            }
            isFirst = 0;
        }

        fprintf(arquivo_saida, "\n");  // Coloca a quebra de linha no final da linha de dados
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    return EXIT_SUCCESS;
}
