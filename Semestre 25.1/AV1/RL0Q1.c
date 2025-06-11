//Ana Emília Lobo e Martfeld Mutim 20241160001 e Rodrigo Amorim Alves 20241160002

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct{
    float distanciaOrigem;
    int x ; 
    int y;
    int entrada ;
}Pontos;



void bubble(Pontos p[], int n){
    for(int i = 0; i <n ; i++){
        for (int j = 0; j <n-1-i; j++){
            Pontos temp = p[j];
            if(p[j].distanciaOrigem>p[j+1].distanciaOrigem){
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

float calculoDistancia(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  }
// Processa cada linha do arquivo de entrada
void processarLinha(char *linha, FILE *arq_out) {
    Pontos pontos[250]; // Suporta até 250 pontos por linha (500 caracteres)
    int count = 0;
    float distanciaTotal = 0.0;
    char *token;

    // Extrai pontos usando strtok_r para thread safety
    char *resto;
    token = strtok_r(linha, " ()", &resto);
    while(token != NULL && count < 250) {
        int x, y;
        if(sscanf(token, "%d,%d", &x, &y) == 2) {
            pontos[count].x = x;
            pontos[count].y = y;
            pontos[count].distanciaOrigem = sqrt(x*x + y*y);
            count++;
        }
        token = strtok_r(NULL, " ()", &resto);
    }

    // Calcula distância total e shortcut
    for(int i = 0; i < count-1; i++) {
        distanciaTotal += calculoDistancia(
            pontos[i].x, pontos[i].y,
            pontos[i+1].x, pontos[i+1].y
        );
    }
    float shortcut = (count > 1) ? calculoDistancia(
        pontos[0].x, pontos[0].y,
        pontos[count-1].x, pontos[count-1].y
    ) : 0.0;

    // Ordena os pontos
    bubble(pontos, count);

    // Formata saída com buffer controlado
    char buffer[501] = ""; // Buffer de 500 + \0
    int escrito = 0;
    
    // Constrói a linha de saída
    escrito += snprintf(buffer + escrito, sizeof(buffer) - escrito, "points");
    for(int i = 0; i < count && escrito < 500; i++) {
        escrito += snprintf(buffer + escrito, sizeof(buffer) - escrito, 
                          " (%d,%d)", pontos[i].x, pontos[i].y);
    }
    
    // Adiciona métricas finais
    snprintf(buffer + escrito, sizeof(buffer) - escrito, 
            " distance %.2f shortcut %.2f\n", distanciaTotal, shortcut);

    // Escreve no arquivo de saída
    fputs(buffer, arq_out);
}

int main() {
    FILE *arq_in = fopen("L0Q1.in", "r");
    FILE *arq_out = fopen("L0Q1.out", "w");
    char linha[510]; // Buffer para 500 caracteres + \n + \0

    if(!arq_in || !arq_out) {
        perror("Erro ao abrir arquivos");
        return EXIT_FAILURE;
    }

    // Processa cada linha do arquivo
    while(fgets(linha, sizeof(linha), arq_in)) {
        linha[strcspn(linha, "\r\n")] = '\0'; // Remove quebras de linha
        processarLinha(linha, arq_out);
    }

    fclose(arq_in);
    fclose(arq_out);
    return EXIT_SUCCESS;
}