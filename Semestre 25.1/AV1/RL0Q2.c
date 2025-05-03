//Ana Emília Lobo e Martfeld Mutim 20241160001 e Rodrigo Amorim Alves 20241160002

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções de manipulação de arquivos
char *carregarConteudoArquivo(const char *caminhoArquivo) {
  FILE *arquivo = fopen(caminhoArquivo, "r");
  if (!arquivo) {
    perror("Erro ao abrir o arquivo de entrada");
    exit(EXIT_FAILURE);
  }

  fseek(arquivo, 0, SEEK_END);
  long tamanhoArquivo = ftell(arquivo);
  rewind(arquivo);

  char *buffer = (char *)malloc((tamanhoArquivo + 1) * sizeof(char));
  fread(buffer, 1, tamanhoArquivo, arquivo);
  buffer[tamanhoArquivo] = '\0';

  fclose(arquivo);
  return buffer;
}

void salvarConteudoArquivo(const char *caminhoArquivo, const char *conteudo) {
  FILE *arquivo = fopen(caminhoArquivo, "w");
  if (!arquivo) {
    perror("Erro ao abrir o arquivo de saída");
    exit(EXIT_FAILURE);
  }

  fprintf(arquivo, "%s", conteudo);
  fclose(arquivo);
  printf("Arquivo de saída gerado com sucesso!\n");
}

// Funções auxiliares
void trocarElementos(char **elementoA, char **elementoB) {
  char *temporario = *elementoA;
  *elementoA = *elementoB;
  *elementoB = temporario;
}

// Implementação do Bubble Sort melhorada
void ordenarPorBolha(char *array[], int quantidade, int (*comparador)(char *, char *)) {
  int houveTroca;
  for (int i = 0; i < quantidade-1; i++) {
    houveTroca = 0;
    for (int j = 0; j < quantidade-i-1; j++) {
      if (comparador(array[j], array[j+1]) > 0) {
        trocarElementos(&array[j], &array[j+1]);
        houveTroca = 1;
      }
    }
    if (!houveTroca) break;
  }
}

// Funções de cálculo e comparação (removido const para consistência)
double calcularDistanciaDaOrigem(char *ponto) {
  int coordenadaX, coordenadaY;
  sscanf(ponto, "(%d,%d)", &coordenadaX, &coordenadaY);
  return sqrt(coordenadaX * coordenadaX + coordenadaY * coordenadaY);
}

int compararPorDistancia(char *pontoA, char *pontoB) {
  double distanciaA = calcularDistanciaDaOrigem(pontoA);
  double distanciaB = calcularDistanciaDaOrigem(pontoB);
  return (distanciaA > distanciaB) - (distanciaA < distanciaB);
}

int compararStrings(char *stringA, char *stringB) { 
    return strcmp(stringA, stringB); 
}

int compararNumeros(char *numeroA, char *numeroB) {
  double valorA = atof(numeroA);
  double valorB = atof(numeroB);
  return (valorA > valorB) - (valorA < valorB);
}

// Funções de verificação
int ehNumeroInteiro(char *str) {
  char *final;
  double valor = strtod(str, &final);
  return *final == '\0' && valor == (int)valor;
}

int ehCoordenadaValida(char *str) {
  return str[0] == '(' && str[strlen(str) - 1] == ')';
}

int main() {
  const char *caminhoEntrada = "./L0Q2.in";
  const char *caminhoSaida = "./L0Q2.out";

  char *conteudoArquivo = carregarConteudoArquivo(caminhoEntrada);

  char *linhas[1000];
  int totalLinhas = 0;

  char *linhaAtual = strtok(conteudoArquivo, "\r\n");
  while (linhaAtual) {
    linhas[totalLinhas++] = strdup(linhaAtual);
    linhaAtual = strtok(NULL, "\r\n");
  }

  char conteudoSaida[10000] = "";

  for (int i = 0; i < totalLinhas; i++) {
    char *elementos[100];
    int totalElementos = 0;

    char *elemento = strtok(linhas[i], " ");
    while (elemento) {
      elementos[totalElementos++] = strdup(elemento);
      elemento = strtok(NULL, " ");
    }

    char *textos[100], *inteiros[100], *decimais[100], *coordenadas[100];
    int totalTextos = 0, totalInteiros = 0, totalDecimais = 0, totalCoordenadas = 0;

    for (int j = 0; j < totalElementos; j++) {
      if (ehCoordenadaValida(elementos[j])) {
        coordenadas[totalCoordenadas++] = elementos[j];
      } else if (ehNumeroInteiro(elementos[j])) {
        inteiros[totalInteiros++] = elementos[j];
      } else if (isdigit(elementos[j][0]) || elementos[j][0] == '-') {
        decimais[totalDecimais++] = elementos[j];
      } else {
        textos[totalTextos++] = elementos[j];
      }
    }

    ordenarPorBolha(textos, totalTextos, compararStrings);
    ordenarPorBolha(coordenadas, totalCoordenadas, compararPorDistancia);
    ordenarPorBolha(decimais, totalDecimais, compararNumeros);
    ordenarPorBolha(inteiros, totalInteiros, compararNumeros);

    char linhaSaida[1024] = "";
    
    strcat(linhaSaida, "str:");
    for (int j = 0; j < totalTextos; j++) {
      strcat(linhaSaida, textos[j]);
      strcat(linhaSaida, " ");
    }
    if (totalTextos == 0) strcat(linhaSaida, " ");

    strcat(linhaSaida, "int:");
    for (int j = 0; j < totalInteiros; j++) {
      strcat(linhaSaida, inteiros[j]);
      strcat(linhaSaida, " ");
    }
    if (totalInteiros == 0) strcat(linhaSaida, " ");

    strcat(linhaSaida, "float:");
    for (int j = 0; j < totalDecimais; j++) {
      strcat(linhaSaida, decimais[j]);
      strcat(linhaSaida, " ");
    }
    if (totalDecimais == 0) strcat(linhaSaida, " ");

    strcat(linhaSaida, "p:");
    for (int j = 0; j < totalCoordenadas; j++) {
      strcat(linhaSaida, coordenadas[j]);
      if (j + 1 < totalCoordenadas) strcat(linhaSaida, " ");
    }

    strcat(conteudoSaida, linhaSaida);
    strcat(conteudoSaida, "\n");
  }

  salvarConteudoArquivo(caminhoSaida, conteudoSaida);

  free(conteudoArquivo);
  for (int i = 0; i < totalLinhas; i++) {
    free(linhas[i]);
  }

  return 0;
}