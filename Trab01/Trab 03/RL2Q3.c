// Ana Emília Lobo e Martfeld Mutim, matricula nº: 20241160001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
  int valor;
  int altura;
  struct No *pai;
  struct No *direita;
  struct No *esquerda;
} No;

void removerNo(No **raiz, int valor);

int inserirNo(No **raiz, int valor){
  No *novo = (No*)malloc(sizeof(No));
  int altura = 0;
  novo->valor = valor;
  novo->esquerda = NULL;
  novo->direita = NULL;
  novo->pai = NULL;
  novo->altura = altura;

  if(*raiz == NULL){
    *raiz = novo;
  }else{
    No *atual = *raiz;
    No *pai = NULL;
    while(1){
      pai = atual;
      if(valor < atual->valor){
        atual = atual->esquerda;
        altura++;
        if(atual == NULL){
          pai->esquerda = novo;
          novo->pai = pai;
          novo->altura = altura;
          return novo->altura;
        }
      }else{
        atual = atual->direita;
        altura++;
        if(atual == NULL){
          pai->direita = novo;
          novo->pai = pai;
          novo->altura = altura;
          return novo->altura;
        }
      }
    }
  }
  return 0;
}

No *buscarNo(No *raiz, int valor){
    No *atual = raiz;
    while(atual != NULL){
      if(valor < atual->valor){
        atual = atual->esquerda;
      }else if(valor > atual->valor){
        atual = atual->direita;
      }else{
        return atual;
      }
    }
    return NULL;
  }

void atualizarAltura(No *pai){
  if(pai != NULL){
    No *atual = pai;
    while(atual != NULL){
      if(atual->esquerda != NULL){
        atual->esquerda->altura = atual->altura + 1;
        atualizarAltura(atual->esquerda);
      }
      if(atual->direita != NULL){
        atual->direita->altura = atual->altura + 1;
        atualizarAltura(atual->direita);
      }
      break;
    }
  }
}

No *sucessor(No *folha){
  No *atual = folha->direita;
  while(atual->esquerda != NULL){
    atual = atual->esquerda;
  }
  return atual;
}

void removerFolha(No **raiz, No *folha){
  if(folha->pai != NULL){
    if(folha->pai->esquerda == folha){
      folha->pai->esquerda = NULL;
    }else{
      folha->pai->direita = NULL;
    }
  }else{
    *raiz = NULL;
  }
  free(folha);
}

void removerComUmFilho(No **raiz, No *folha){
  if(folha->pai == NULL){
    if(folha->esquerda != NULL){
      folha->esquerda->altura = 0;
      *raiz = folha->esquerda;
      folha->esquerda->pai = NULL;
    }else{
      folha->direita->altura = 0;
      *raiz = folha->direita;
      folha->direita->pai = NULL;
    }
    atualizarAltura(*raiz);
  }else{
    if(folha->pai->esquerda == folha){
      if(folha->esquerda != NULL){
        folha->pai->esquerda = folha->esquerda;
        folha->esquerda->pai = folha->pai;
      }else{
        folha->pai->esquerda = folha->direita;
        folha->direita->pai = folha->pai;
      }
    }else{
      if(folha->esquerda != NULL){
        folha->pai->direita = folha->esquerda;
        folha->esquerda->pai = folha->pai;
      }else{
        folha->pai->direita = folha->direita;
        folha->direita->pai = folha->pai;
      }
    }
    atualizarAltura(folha->pai);
  }
  free(folha);
}

void removerComDoisFilhos(No **raiz, No *folha){
  No *sucessorNo = sucessor(folha);
  folha->valor = sucessorNo->valor;
  atualizarAltura(folha);
  removerNo(&sucessorNo, sucessorNo->valor);
}

void removerNo(No **raiz, int valor){
  No *atual = buscarNo(*raiz, valor);
  if(atual == NULL){
    inserirNo(raiz, valor);
    return;
  }

  if(atual->esquerda == NULL && atual->direita == NULL){
    removerFolha(raiz, atual);
  }else if(atual->esquerda == NULL || atual->direita == NULL){
    removerComUmFilho(raiz, atual);
  }else{
    removerComDoisFilhos(raiz, atual);
  }
}

void escreverEmOrdem(No *raiz, char *texto, int *elementos){
  if(raiz){
    escreverEmOrdem(raiz->esquerda, texto, elementos);
    if(*elementos == 0){
      sprintf(texto, "%s%d (%d)", texto, raiz->valor, raiz->altura);
    }else{
      sprintf(texto, "%s %d (%d)", texto, raiz->valor, raiz->altura);
    }
    *elementos = *elementos + 1;
    escreverEmOrdem(raiz->direita, texto, elementos);
  }
}

int main(){
  FILE *entrada = fopen("L2Q3.in", "r");
  FILE *saida = fopen("L2Q3.out", "w");
  char linha[1000];
  char espaco[] = " ";
  int numeroLinha = 0;

  if(entrada == NULL || saida == NULL){
    printf("Arquivos nao podem ser abertos.");
    return EXIT_FAILURE;
  }

  while(fgets(linha, sizeof(linha), entrada) != NULL){
    No *raiz = NULL;
    char texto[1000];
    int elementos = 0;

    linha[strcspn(linha, "\n")] = '\0';
    linha[strcspn(linha, "\r")] = '\0';

    char *parte = strtok(linha, espaco);

    if(numeroLinha != 0){
      sprintf(texto, "\n");
    }else{
      sprintf(texto, "");
    }

    while(parte != NULL){
      if(parte[0] == 'a'){
        parte = strtok(NULL, espaco);
        int valor = atoi(parte);
        inserirNo(&raiz, valor);
      }else if(parte[0] == 'r'){
        parte = strtok(NULL, espaco);
        int valor = atoi(parte);
        removerNo(&raiz, valor);
      }
      parte = strtok(NULL, espaco);
    }

    escreverEmOrdem(raiz, texto, &elementos);
    fputs(texto, saida);
    numeroLinha++;
  }

  fclose(entrada);
  fclose(saida);
  return 0;
}
