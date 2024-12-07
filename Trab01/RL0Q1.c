#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINHA 500
#define MAX_PONTOS 100

// struct para armazenar pontos
typedef struct Ponto {
    int x;
    int y;
    char *strPonto; // Ponteiro para string, alocação dinâmica
    double distanciaOrigem;
} Ponto;

// Função para calcular a distância euclidiana entre dois pontos
double calcularDistancia(const Ponto p1, const Ponto p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Função para calcular a distância euclidiana total
double calcularDistanciaTotal(const Ponto pontos[], int quantidade) {
    double distanciaTotal = 0.0;
    for (int i = 0; i < quantidade - 1; i++) {
        distanciaTotal += calcularDistancia(pontos[i], pontos[i + 1]);
    }
    return distanciaTotal;
}

// Função auxiliar merge para o merge sort
void mergePontos(Ponto pontos[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Ponto *esq = (Ponto *)malloc(n1 * sizeof(Ponto));
    Ponto *dir = (Ponto *)malloc(n2 * sizeof(Ponto));

    for (int i = 0; i < n1; i++) {
        esq[i] = pontos[inicio + i];
    }
    for (int i = 0; i < n2; i++) {
        dir[i] = pontos[meio + 1 + i];
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (esq[i].distanciaOrigem <= dir[j].distanciaOrigem) {
            pontos[k++] = esq[i++];
        } else {
            pontos[k++] = dir[j++];
        }
    }

    while (i < n1) {
        pontos[k++] = esq[i++];
    }
    while (j < n2) {
        pontos[k++] = dir[j++];
    }

    free(esq);
    free(dir);
}

// Função para ordenar, através do merge sort, o array de pontos com relação à distância à origem
void ordenarPontos(Ponto pontos[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2; // Prevenindo overflow
        ordenarPontos(pontos, inicio, meio);
        ordenarPontos(pontos, meio + 1, fim);
        mergePontos(pontos, inicio, meio, fim);
    }
}

// Função para converter o array de pontos em string (com alocação dinâmica)
char* pontosParaString(const Ponto pontos[], int quantidade) {
    char *str = (char*)malloc(MAX_LINHA * sizeof(char)); // Alocação dinâmica!

    str[0] = '\0'; // Inicializa a string
    for (int i = 0; i < quantidade; i++) {
        // Adiciona o ponto à string
        char ponto[50];
        sprintf(ponto, "(%d,%d)", pontos[i].x, pontos[i].y);
        strcat(str, ponto);
    }
    return str;
}

int main() {
    FILE *arquivo_entrada = fopen("L0Q1.in", "r"); // Abre L0Q1.in para leitura
    FILE *arquivo_saida = fopen("L0Q1.out", "w"); // Abre L0Q1.out para escrita

    if (arquivo_entrada == NULL || arquivo_saida == NULL) {
        printf("Erro ao abrir arquivos de entrada ou saída\n");
        return EXIT_FAILURE;
    } else {
        printf("Arquivos abertos com sucesso\n");
    }

    char linha[MAX_LINHA];
    Ponto pontos[MAX_PONTOS];
    const char delimPonto[] = " ";
    const char delimCoordX[] = ","; // delimitador para X
    const char delimCoordY[] = ")"; // delimitador para Y
    char *parte;
    char *endptr;
    int contadorPontos = 0;
    char *strPontos;

    while (fgets(linha, MAX_LINHA, arquivo_entrada) != NULL) {
        printf("Linha lida: %s\n", linha);

        parte = strtok(linha, delimPonto);
        contadorPontos = 0;

        while (parte != NULL && contadorPontos < MAX_PONTOS) {
            printf("Processando parte: %s\n", parte);

            pontos[contadorPontos].strPonto = strdup(parte);

            char *x_str = strtok(NULL, delimCoordX);
            char *y_str = strtok(NULL, delimCoordY);

            if (x_str && y_str) {
                pontos[contadorPontos].x = (int)strtol(x_str, &endptr, 10);
                pontos[contadorPontos].y = (int)strtol(y_str, &endptr, 10);
                pontos[contadorPontos].distanciaOrigem = sqrt(pow(pontos[contadorPontos].x, 2) + pow(pontos[contadorPontos].y, 2));
                printf("Ponto extraído: x=%d, y=%d\n", pontos[contadorPontos].x, pontos[contadorPontos].y);
                contadorPontos++;
            } else {
                printf("Erro ao processar coordenadas de %s\n", parte);
            }

            parte = strtok(NULL, delimPonto);
        }

        if (contadorPontos == 0) {
            printf("Nenhum ponto encontrado na linha\n");
            continue;
        }

        // Calcular as distâncias
        double distanciaTotal = calcularDistanciaTotal(pontos, contadorPontos);
        double atalho = calcularDistancia(pontos[0], pontos[contadorPontos - 1]); // Atalho entre o primeiro e último ponto

        // Ordenar os pontos por distância
        ordenarPontos(pontos, 0, contadorPontos - 1);
        strPontos = pontosParaString(pontos, contadorPontos);

        // Criar texto e salvar no arquivo
        char texto[MAX_LINHA];
        sprintf(texto, "pontos %s distancia %.2lf atalho %.2lf\n", strPontos, distanciaTotal, atalho);
        fputs(texto, arquivo_saida);
        printf("Escrevendo no arquivo de saída: %s\n", texto);

        for (int i = 0; i < contadorPontos; i++) {
            free(pontos[i].strPonto);
        }
        free(strPontos);
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    printf("Processamento concluído\n");
    return EXIT_SUCCESS;
}
