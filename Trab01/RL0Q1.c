//Ana Emília Lobo, matricula 20241160001
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINHA 1000
#define MAX_PONTOS 1000

// Struct para armazenar coordenadas
typedef struct Ponto {
    float x;
    float y;
    char point[50];
    float distanciaOrigem;
} Ponto;

// Função para calcular a menor distância euclidiana entre dois pontos
float calcularDistancia(const Ponto p1, const Ponto p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Função para calcular a distância euclidiana total
float calcularDistanciaTotal(const Ponto pontos[], int quantidade) {
    float distanciaTotal = 0.0;
    for (int i = 0; i < quantidade - 1; i++) {
        distanciaTotal += calcularDistancia(pontos[i], pontos[i + 1]);
    }
    return distanciaTotal;
}

// Função para converter o array de pontos em string
void pontosParaString(Ponto pontos[], int quantidade, char *str, size_t str_size) {
    str[0] = '\0';
    for (int i = 0; i < quantidade; i++) {
        snprintf(str + strlen(str), str_size - strlen(str), "%s ", pontos[i].point);
    }
    if (strlen(str) > 0) {
        str[strlen(str) - 1] = '\0'; // Remove o espaço extra no final
    }
}

// Função para ordenar strings usando Bubble Sort (ordem alfabética)
void ordenarStrings(char strings[MAX_PONTOS][50], int numStrings) {
    for (int i = 0; i < numStrings - 1; i++) {
        for (int j = i + 1; j < numStrings; j++) {
            if (strcmp(strings[i], strings[j]) > 0) {
                // Troca as strings
                char temp[50];
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], temp);
            }
        }
    }
}

// Função para ordenar inteiros usando Bubble Sort (ordem crescente)
void ordenarInteiros(int inteiros[MAX_PONTOS], int numInteiros) {
    for (int i = 0; i < numInteiros - 1; i++) {
        for (int j = i + 1; j < numInteiros; j++) {
            if (inteiros[i] > inteiros[j]) {
                // Troca os inteiros
                int temp = inteiros[i];
                inteiros[i] = inteiros[j];
                inteiros[j] = temp;
            }
        }
    }
}

// Função para ordenar floats usando Bubble Sort (ordem crescente)
void ordenarFloats(float floats[MAX_PONTOS], int numFloats) {
    for (int i = 0; i < numFloats - 1; i++) {
        for (int j = i + 1; j < numFloats; j++) {
            if (floats[i] > floats[j]) {
                // Troca os floats
                float temp = floats[i];
                floats[i] = floats[j];
                floats[j] = temp;
            }
        }
    }
}

// Função para ordenar pontos pela distância à origem usando Bubble Sort
void ordenarPontos(Ponto pontos[MAX_PONTOS], int numPontos) {
    for (int i = 0; i < numPontos - 1; i++) {
        for (int j = i + 1; j < numPontos; j++) {
            if (pontos[i].distanciaOrigem > pontos[j].distanciaOrigem) {
                // Troca os pontos
                Ponto temp = pontos[i];
                pontos[i] = pontos[j];
                pontos[j] = temp;
            }
        }
    }
}

int main() {
    FILE *arquivo_entrada = fopen("L0Q1.in", "r");
    FILE *arquivo_saida = fopen("L0Q1.out", "w");

    if (arquivo_entrada == NULL || arquivo_saida == NULL) {
        printf("Erro ao abrir os arquivos\n");
        return EXIT_FAILURE;
    }

    char linha[MAX_LINHA];
    Ponto pontos[MAX_PONTOS];
    char stringCoordenadas[MAX_LINHA];
    int contadorPontos;

    while (fgets(linha, MAX_LINHA, arquivo_entrada) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove o '\n' do final da linha
        contadorPontos = 0;
        char *parte = strtok(linha, " ");

        while (parte != NULL && contadorPontos < MAX_PONTOS) {
            if (parte[0] == '(' && parte[strlen(parte) - 1] == ')') {
                strcpy(pontos[contadorPontos].point, parte);
                sscanf(parte, "(%f,%f)", &pontos[contadorPontos].x, &pontos[contadorPontos].y);
                pontos[contadorPontos].distanciaOrigem = sqrt(pow(pontos[contadorPontos].x, 2) + pow(pontos[contadorPontos].y, 2));
                contadorPontos++;
            }
            parte = strtok(NULL, " ");
        }

        if (contadorPontos < 2) {
            continue;
        }

        // Calcular a distância total e o atalho
        float distanciaTotal = calcularDistanciaTotal(pontos, contadorPontos);
        float atalho = calcularDistancia(pontos[0], pontos[contadorPontos - 1]);

        // Ordenar os pontos por distância à origem
        ordenarPontos(pontos, contadorPontos);

        // Converter os pontos em string
        pontosParaString(pontos, contadorPontos, stringCoordenadas, sizeof(stringCoordenadas));

        // Escrever no arquivo de saída
        fprintf(arquivo_saida, "pontos %s distancia %.2f atalho %.2f\n", stringCoordenadas, distanciaTotal, atalho);
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    return EXIT_SUCCESS;
}
