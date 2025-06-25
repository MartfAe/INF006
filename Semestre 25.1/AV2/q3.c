#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAMANHO_MAX_LINHA 4000

// Sublista de valores (floats) associados a uma categoria
typedef struct NoValor {
    float valor;
    struct NoValor* proximo;
} NoValor;

// Lista principal de categorias (inteiros)
typedef struct NoCategoria {
    int id;
    NoValor* sublistaValores; // Cada categoria tem sua própria sublista
    struct NoCategoria* anterior;
    struct NoCategoria* proximo;
} NoCategoria;

NoCategoria* criarNoCategoria(int id);
void inserirValorOrdenado(NoValor** sublista, float valor);
void inserirCategoriaOrdenada(NoCategoria** cabeca, int id);
void associarValorACategoria(NoCategoria* listaCategorias, float valor);
void exibirEstrutura(NoCategoria* lista, FILE* arqSaida);
void liberarMemoria(NoCategoria* lista);

// Cria um novo nó de categoria 
NoCategoria* criarNoCategoria(int id) {
    NoCategoria* no = (NoCategoria*)malloc(sizeof(NoCategoria));
    no->id = id;
    no->sublistaValores = NULL;
    no->anterior = NULL;
    no->proximo = NULL;
    return no;
}

// Cria um novo nó de valor
NoValor* criarNoValor(float valor) {
    NoValor* no = (NoValor*)malloc(sizeof(NoValor));
    no->valor = valor;
    no->proximo = NULL;
    return no;
}

// Insere um valor na sublista, mantendo a ordem DECRESCENTE
void inserirValorOrdenado(NoValor** cabecaSublista, float valor) {
    NoValor* novo = criarNoValor(valor);
    // Caso 1: A sublista está vazia ou o novo valor é o maior de todos
    if (*cabecaSublista == NULL || valor > (*cabecaSublista)->valor) {
        novo->proximo = *cabecaSublista;
        *cabecaSublista = novo;
        return;
    }
    // Caso 2: Percorrer a sublista para achar a posição correta
    NoValor* atual = *cabecaSublista;
    while (atual->proximo != NULL && atual->proximo->valor > valor) {
        atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

// Insere uma nova categoria na lista principal, mantendo a ordem CRESCENTE de IDs
void inserirCategoriaOrdenada(NoCategoria** cabeca, int id) {
    NoCategoria* novo = criarNoCategoria(id);
    if (*cabeca == NULL || id < (*cabeca)->id) {
        novo->proximo = *cabeca;
        if (*cabeca) (*cabeca)->anterior = novo;
        *cabeca = novo;
        return;
    }
    NoCategoria* atual = *cabeca;
    while (atual->proximo && atual->proximo->id < id) {
        atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    if (atual->proximo) atual->proximo->anterior = novo;
    atual->proximo = novo;
    novo->anterior = atual;
}

// Encontra a categoria correta para um valor e o insere de forma ordenada
// Substitui a complexa função 'associar' original
void associarValorACategoria(NoCategoria* listaCategorias, float valor) {
    NoCategoria* atual = listaCategorias;
    while (atual) {
        // A mesma regra de associação
        if (fabs(valor - atual->id) < 1.0) {
            inserirValorOrdenado(&(atual->sublistaValores), valor);
            return; // Encontrou a categoria, podemos parar
        }
        atual = atual->proximo;
    }
}

// Função de exibição
void exibirEstrutura(NoCategoria* lista, FILE* arqSaida) {
    fprintf(arqSaida, "[");
    NoCategoria* noCat = lista;
    while (noCat) {
        fprintf(arqSaida, "%d(", noCat->id);

        // A sublista já está ordenada, basta percorrer e imprimir
        NoValor* noVal = noCat->sublistaValores;
        while (noVal) {
            fprintf(arqSaida, "%.2f", noVal->valor);
            if (noVal->proximo) fprintf(arqSaida, "−>");
            noVal = noVal->proximo;
        }
        fprintf(arqSaida, ")");

        if (noCat->proximo) fprintf(arqSaida, "->");
        noCat = noCat->proximo;
    }
    fprintf(arqSaida, "]\n");
}

// Libera toda a memória alocada
void liberarMemoria(NoCategoria* lista) {
    NoCategoria* noCatAtual = lista;
    while (noCatAtual) {
        NoCategoria* tempCat = noCatAtual;
        noCatAtual = noCatAtual->proximo;

        NoValor* noValAtual = tempCat->sublistaValores;
        while (noValAtual) {
            NoValor* tempVal = noValAtual;
            noValAtual = noValAtual->proximo;
            free(tempVal);
        }
        free(tempCat);
    }
}

// Main simplificada, sem lista temporária e sem vazamento de memória
int main() {
    FILE* arqEntrada = fopen("L1Q3.in", "r");
    FILE* arqSaida = fopen("L1Q3.out", "w");

    if (!arqEntrada || !arqSaida) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char linha[TAMANHO_MAX_LINHA];
    while (fgets(linha, sizeof(linha), arqEntrada)) {
        NoCategoria* listaPrincipal = NULL;
        
        char* token = strtok(linha, " \n");
        int modo_leitura = -1; // -1: indefinido, 0: Categoria (LE), 1: Valor (LI)

        while (token) {
            if (strcmp(token, "LE") == 0) {
                modo_leitura = 0;
            } else if (strcmp(token, "LI") == 0) {
                modo_leitura = 1;
            } else {
                if (modo_leitura == 0) {
                    inserirCategoriaOrdenada(&listaPrincipal, atoi(token));
                } else if (modo_leitura == 1) {
                    // Processa o valor imediatamente, sem lista temporária
                    associarValorACategoria(listaPrincipal, atof(token));
                }
            }
            token = strtok(NULL, " \n");
        }

        exibirEstrutura(listaPrincipal, arqSaida);
        liberarMemoria(listaPrincipal);
    }

    fclose(arqEntrada);
    fclose(arqSaida);
    return 0;
}