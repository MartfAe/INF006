#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES 1000
#define MAX_NOME 30

// Estrutura de nó para armazenar os nomes
typedef struct no {
    char nome[MAX_NOME];
    struct no *proximo;
} No;

// Estrutura de pilha, que agora armazena o topo e o tamanho
typedef struct {
    No *topo;
    int tamanho;
} Pilha;

// Função para inicializar a pilha
void inicializarPilha(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

// Função para empilhar um nome na pilha
void empilhar(Pilha *p, const char *nome) {
    No *novoNo = malloc(sizeof(No));
    if (novoNo) {
        strcpy(novoNo->nome, nome);
        novoNo->proximo = p->topo;
        p->topo = novoNo;
        p->tamanho++;
    } else {
        printf("Erro de alocação de memória!\n");
    }
}

// Função para desempilhar um nome da pilha
No* desempilhar(Pilha *p) {
    if (p->topo != NULL) {
        No *noRemovido = p->topo;
        p->topo = noRemovido->proximo;
        p->tamanho--;
        return noRemovido;
    }
    return NULL; // Retorna NULL se a pilha estiver vazia
}

// Função para imprimir a pilha (opcional para debugging)
void imprimirPilha(Pilha *p) {
    No *aux = p->topo;
    printf("\nPILHA");
    while (aux) {
        printf("%s\n", aux->nome);
        aux = aux->proximo;
    }
}

int main(void) {
    // Abrir os arquivos de entrada e saída
    FILE *entrada = fopen("L1Q2.in", "r");
    FILE *saida = fopen("L1Q2.out", "w");

    if (!entrada || !saida) {
        printf("Erro ao abrir arquivos!\n");
        return EXIT_FAILURE;
    }

    char linha[MAX_CARACTERES];
    const char delimitador[] = " ";

    // Pilhas principais e auxiliares
    Pilha pilhaPrincipal, pilhaAuxiliar;
    inicializarPilha(&pilhaPrincipal);
    inicializarPilha(&pilhaAuxiliar);

    while (fgets(linha, sizeof(linha), entrada)) {
        linha[strcspn(linha, "\n")] = '\0';  // Remove o '\n' da linha
        char *nome = strtok(linha, delimitador); // Separa o primeiro nome da linha
        char resultado[MAX_CARACTERES] = ""; // String para armazenar o resultado

        // Processar cada nome da linha
        while (nome != NULL) {
            int countPop = 0; // Contador para registrar o número de pops

            // Desempilhar elementos da pilha principal enquanto necessário para manter a ordem
            while (pilhaPrincipal.topo != NULL && strcmp(nome, pilhaPrincipal.topo->nome) < 0) {
                No *noDesempilhado = desempilhar(&pilhaPrincipal);
                countPop++;
                empilhar(&pilhaAuxiliar, noDesempilhado->nome);
                free(noDesempilhado); // Liberar memória
            }

            // Adicionar à saída o número de pops realizados
            if (countPop > 0) {
                char temp[50];
                sprintf(temp, "%dx-pop ", countPop);
                strcat(resultado, temp);
            }

            // Empilhar o nome atual na pilha principal
            empilhar(&pilhaPrincipal, nome);
            char tempPush[50];
            sprintf(tempPush, "push-%s ", pilhaPrincipal.topo->nome);
            strcat(resultado, tempPush);

            // Reempilhar da pilha auxiliar de volta para a principal
            while (pilhaAuxiliar.topo != NULL) {
                No *noAux = desempilhar(&pilhaAuxiliar);
                empilhar(&pilhaPrincipal, noAux->nome);
                sprintf(tempPush, "push-%s ", noAux->nome);
                strcat(resultado, tempPush);
                free(noAux); // Liberar memória
            }

            // Avançar para o próximo nome na linha
            nome = strtok(NULL, delimitador);
        }

        // Escrever a linha no arquivo de saída
        fputs(resultado, saida);
        printf("%s", resultado); // Imprimir no console

        // Adicionar uma nova linha no arquivo, se não for o final
        if (!feof(entrada)) {
            fputs("\n", saida);
            printf("\n");
        }
    }

    // Fechar os arquivos após a leitura
    fclose(entrada);
    fclose(saida);

    return EXIT_SUCCESS;
}
