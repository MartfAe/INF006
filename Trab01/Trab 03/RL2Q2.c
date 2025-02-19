// Ana Emília Lobo e Martfeld Mutim, matricula nº: 20241160001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
  int valor;
  int profundidade;
  int diferenca;
  struct no *esquerda;
  struct no *direita;
  struct no *ancestral;
} No;

int calcularSoma(No *raiz){
  if(raiz != NULL){
    return raiz->valor + calcularSoma(raiz->esquerda) + calcularSoma(raiz->direita);
  }else{
    return 0;
  }
}

int adicionarNo(No **raiz, int valor){
  No *novoNo = (No*)malloc(sizeof(No));
  int profundidade = 0;
  novoNo->valor = valor;
  novoNo->diferenca = 0;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;
  novoNo->ancestral = NULL;
  novoNo->profundidade = profundidade;

  if(*raiz == NULL){
    *raiz = novoNo;
  }else{
    No *atual = *raiz;
    No *anterior = NULL;
    while(1){
      anterior = atual;
      if(valor < atual->valor){
        atual = atual->esquerda;
        profundidade++;
        if(atual == NULL){
          anterior->esquerda = novoNo;
          novoNo->ancestral = anterior;
          novoNo->profundidade = profundidade;
          return novoNo->profundidade;
        }
      }else if(valor > atual->valor){
        atual = atual->direita;
        profundidade++;
        if(atual == NULL){
          anterior->direita = novoNo;
          novoNo->ancestral = anterior;
          novoNo->profundidade = profundidade;
          return novoNo->profundidade;
        }
      }else{
        free(novoNo);
        return -1;
      }
    }
  }
  return 0;
}

void calcularDiferencas(No *raiz){
  if(raiz != NULL){
    raiz->diferenca = calcularSoma(raiz->direita) - calcularSoma(raiz->esquerda);
    calcularDiferencas(raiz->esquerda);
    calcularDiferencas(raiz->direita);
  }
}

void imprimirEmOrdem(No *raiz, char *saida, int *contador){
  if(raiz){
    imprimirEmOrdem(raiz->esquerda, saida, contador);
    if(*contador == 0){
      sprintf(saida, "%s%d (%d)", saida, raiz->valor, raiz->diferenca);
    }else{
      sprintf(saida, "%s %d (%d)", saida, raiz->valor, raiz->diferenca);
    }
    *contador = *contador + 1;
    imprimirEmOrdem(raiz->direita, saida, contador);
  }
}

int main(){
  FILE *arquivoEntrada = fopen("L2Q2.in", "r");
  FILE *arquivoSaida = fopen("L2Q2.out", "w");
  char buffer[1000];
  char delimitador[] = " ";
  int numeroLinha = 0;

  if(arquivoEntrada == NULL || arquivoSaida == NULL){
    printf("Erro ao abrir os arquivos.");
    return EXIT_FAILURE;
  }

  while(fgets(buffer, sizeof(buffer), arquivoEntrada) != NULL){
    No *raiz = NULL;
    char textoSaida[1000];
    int contador = 0;

    buffer[strcspn(buffer, "\n")] = '\0';
    buffer[strcspn(buffer, "\r")] = '\0';

    char *token = strtok(buffer, delimitador);

    if(numeroLinha != 0){
      sprintf(textoSaida, "\n");
    }else{
      sprintf(textoSaida, "");
    }

    while(token != NULL){
      int numero = atoi(token);
      int profundidade = adicionarNo(&raiz, numero);
      token = strtok(NULL, delimitador);
    }

    calcularDiferencas(raiz);
    imprimirEmOrdem(raiz, textoSaida, &contador);
    
    fputs(textoSaida, arquivoSaida);
    numeroLinha++;
  }

  fclose(arquivoEntrada);
  fclose(arquivoSaida);
  return 0;
}
