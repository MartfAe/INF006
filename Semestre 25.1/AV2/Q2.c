#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições de constantes para facilitar a manutenção e leitura
#define MAX_TAMANHO_LINHA 3001
#define CAPACIDADE_INICIAL_PILHA 100
#define MAX_TAMANHO_NOME 50
// Tamanho máximo do buffer de saída, calculado para acomodar todas as operações
#define MAX_BUFFER_OPERACAO (CAPACIDADE_INICIAL_PILHA * (MAX_TAMANHO_NOME + 10) + CAPACIDADE_INICIAL_PILHA * 10)

// --- Estrutura de Pilha Dinâmica ---
// Armazena nomes (strings) e gerencia sua capacidade dinamicamente.
typedef struct {
    char **elementos; // Array de ponteiros para strings (nomes)
    int quantidade;   // Número atual de elementos na pilha
    int capacidade;   // Capacidade máxima atual da pilha
} PilhaDinamica;

// --- Funções de Pilha ---

// Inicializa a pilha com uma capacidade inicial alocada.
void inicializar_pilha(PilhaDinamica *p, int capacidade_inicial) {
    p->elementos = (char **)malloc(sizeof(char *) * capacidade_inicial);
    if (p->elementos == NULL) {
        perror("Falha ao alocar memória para a pilha");
        exit(EXIT_FAILURE);
    }
    p->quantidade = 0;
    p->capacidade = capacidade_inicial;
}

// Libera toda a memória alocada pela pilha e seus elementos.
void destruir_pilha(PilhaDinamica *p) {
    for (int i = 0; i < p->quantidade; i++) {
        free(p->elementos[i]); // Libera a memória de cada string
    }
    free(p->elementos); // Libera o array de ponteiros
    p->elementos = NULL;
    p->quantidade = 0;
    p->capacidade = 0;
}

// Verifica se a pilha está vazia.
int esta_pilha_vazia(const PilhaDinamica *p) {
    return (p->quantidade == 0);
}

// Dobra a capacidade da pilha quando ela está cheia, realocando memória.
void redimensionar_pilha(PilhaDinamica *p) {
    int nova_capacidade = p->capacidade * 2;
    char **novos_elementos = (char **)realloc(p->elementos, sizeof(char *) * nova_capacidade);
    if (novos_elementos == NULL) {
        perror("Falha ao redimensionar a pilha");
        exit(EXIT_FAILURE);
    }
    p->elementos = novos_elementos;
    p->capacidade = nova_capacidade;
}

// Adiciona um nome ao topo da pilha, redimensionando se necessário.
void empilhar_item(PilhaDinamica *p, const char *nome) {
    if (p->quantidade == p->capacidade) {
        redimensionar_pilha(p);
    }
    // Aloca memória para a nova string e copia o nome
    p->elementos[p->quantidade] = (char *)malloc(sizeof(char) * (strlen(nome) + 1));
    if (p->elementos[p->quantidade] == NULL) {
        perror("Falha ao alocar memória para o nome");
        exit(EXIT_FAILURE);
    }
    strcpy(p->elementos[p->quantidade], nome);
    p->quantidade++;
}

// Remove e retorna o nome do topo da pilha. A memória do nome retornado deve ser liberada pelo chamador.
char* desempilhar_item(PilhaDinamica *p) {
    if (esta_pilha_vazia(p)) {
        return NULL;
    }
    p->quantidade--;
    return p->elementos[p->quantidade]; // Retorna o ponteiro para a string
}

// Retorna o nome do topo da pilha sem removê-lo.
char* ver_topo(const PilhaDinamica *p) {
    if (esta_pilha_vazia(p)) {
        return NULL;
    }
    return p->elementos[p->quantidade - 1];
}

// --- Funções Auxiliares ---

// Adiciona uma string de operação ao buffer de saída, garantindo espaçamento correto.
void adicionar_operacao_ao_buffer(char *buffer, const char *operacao, int *eh_primeira_operacao) {
    if (!(*eh_primeira_operacao)) {
        strcat(buffer, " ");
    }
    strcat(buffer, operacao);
    *eh_primeira_operacao = 0;
}

// --- Lógica Principal de Processamento ---

// Processa uma linha de entrada, manipulando a pilha de nomes e gerando a sequência de operações.
void processar_linha_entrada(char *linha, FILE *arquivo_saida) {
    PilhaDinamica pilha_nomes;
    inicializar_pilha(&pilha_nomes, CAPACIDADE_INICIAL_PILHA);

    // Array dinâmico para armazenar nomes temporariamente desempilhados antes de serem re-empilhados.
    char **nomes_desempilhados_temporarios = (char **)malloc(sizeof(char *) * CAPACIDADE_INICIAL_PILHA);
    if (nomes_desempilhados_temporarios == NULL) {
        perror("Falha ao alocar memória para nomes temporários");
        destruir_pilha(&pilha_nomes);
        exit(EXIT_FAILURE);
    }
    int contagem_desempilhados_temp = 0;
    int capacidade_desempilhados_temp = CAPACIDADE_INICIAL_PILHA;

    char buffer_operacoes_saida[MAX_BUFFER_OPERACAO];
    buffer_operacoes_saida[0] = '\0';
    int eh_primeira_operacao = 1; // Flag para controlar o espaço entre operações

    // Tokeniza a linha de entrada por espaços
    char *token_atual = strtok(linha, " ");
    while (token_atual != NULL) {
        // Desempilha nomes da pilha que são lexicograficamente maiores que o token_atual.
        // Estes nomes são armazenados temporariamente para serem re-empilhados depois.
        while (!esta_pilha_vazia(&pilha_nomes) && strcmp(ver_topo(&pilha_nomes), token_atual) > 0) {
            // Redimensiona o array temporário se necessário
            if (contagem_desempilhados_temp == capacidade_desempilhados_temp) {
                capacidade_desempilhados_temp *= 2;
                nomes_desempilhados_temporarios = (char **)realloc(nomes_desempilhados_temporarios, sizeof(char *) * capacidade_desempilhados_temp);
                if (nomes_desempilhados_temporarios == NULL) {
                    perror("Falha ao realocar nomes temporários");
                    destruir_pilha(&pilha_nomes);
                    exit(EXIT_FAILURE);
                }
            }
            nomes_desempilhados_temporarios[contagem_desempilhados_temp++] = desempilhar_item(&pilha_nomes);
        }

        // Se algum nome foi desempilhado, registra a operação de "pop".
        if (contagem_desempilhados_temp > 0) {
            char string_op_pop[30];
            sprintf(string_op_pop, "%dx-pop", contagem_desempilhados_temp);
            adicionar_operacao_ao_buffer(buffer_operacoes_saida, string_op_pop, &eh_primeira_operacao);
        }

        // Empilha o nome atual.
        empilhar_item(&pilha_nomes, token_atual);
        char string_op_push[MAX_TAMANHO_NOME + 10];
        sprintf(string_op_push, "push-%s", token_atual);
        adicionar_operacao_ao_buffer(buffer_operacoes_saida, string_op_push, &eh_primeira_operacao);

        // Re-empilha os nomes que foram temporariamente desempilhados, na ordem inversa.
        // Isso mantém a propriedade de "pilha parcialmente ordenada" ou "pilha de mínimos".
        for (int i = contagem_desempilhados_temp - 1; i >= 0; i--) {
            empilhar_item(&pilha_nomes, nomes_desempilhados_temporarios[i]);
            // Registra a operação de "push" para o nome re-empilhado.
            sprintf(string_op_push, "push-%s", nomes_desempilhados_temporarios[i]);
            adicionar_operacao_ao_buffer(buffer_operacoes_saida, string_op_push, &eh_primeira_operacao);
            // Libera a memória da string que foi desempilhada e agora já foi re-empilhada.
            free(nomes_desempilhados_temporarios[i]);
        }
        contagem_desempilhados_temp = 0; // Reseta para a próxima iteração
        
        token_atual = strtok(NULL, " "); // Próximo nome na linha
    }

    fprintf(arquivo_saida, "%s\n", buffer_operacoes_saida);

    // Garante que toda a memória alocada dinamicamente seja liberada ao final do processamento da linha.
    destruir_pilha(&pilha_nomes);
    free(nomes_desempilhados_temporarios);
}

// --- Função Principal ---

int main() {
    FILE *arquivo_entrada = fopen("L1Q2.in", "r");
    FILE *arquivo_saida = fopen("L1Q2.out", "w");

    if (!arquivo_entrada || !arquivo_saida) {
        perror("Erro ao abrir arquivos");
        return EXIT_FAILURE;
    }

    char buffer_linha[MAX_TAMANHO_LINHA];

    // Lê o arquivo linha por linha
    while (fgets(buffer_linha, sizeof(buffer_linha), arquivo_entrada)) {
        size_t tamanho_linha = strlen(buffer_linha);
        // Remove o caractere de nova linha '\n' se ele existir.
        if (tamanho_linha > 0 && buffer_linha[tamanho_linha - 1] == '\n') {
            buffer_linha[tamanho_linha - 1] = '\0';
        }
        processar_linha_entrada(buffer_linha, arquivo_saida);
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    return EXIT_SUCCESS;
}