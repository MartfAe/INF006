// Ana Emília Lobo e Martfeld Mutim, matricula nº: 20241160001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    int depth;
    struct node *left_child;
    struct node *right_child;
    struct node *parent_node;
} Node;

int inserir(Node **root, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->parent_node = NULL;
    new_node->depth = 0;

    if (*root == NULL) {
        *root = new_node;
        return 0;
    }

    Node *current = *root;
    int current_depth = 0;
    
    while (1) {
        current_depth++;
        if (value < current->data) {
            if (current->left_child == NULL) {
                current->left_child = new_node;
                new_node->parent_node = current;
                new_node->depth = current_depth;
                return current_depth;
            }
            current = current->left_child;
        } else {
            if (current->right_child == NULL) {
                current->right_child = new_node;
                new_node->parent_node = current;
                new_node->depth = current_depth;
                return current_depth;
            }
            current = current->right_child;
        }
    }
}

Node *encontrar_maximo(Node *root) {
    Node *current = root;
    while (current->right_child != NULL) {
        current = current->right_child;
    }
    return current;
}

int main() {
    FILE *fp_in = fopen("L2Q1.in", "r");
    FILE *fp_out = fopen("L2Q1.out", "w");
    char linha[1000];
    char delimitador[] = " ";
    int contador_linha = 0;

    if (fp_in == NULL || fp_out == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return EXIT_FAILURE;
    }

    while (fgets(linha, sizeof(linha), fp_in) != NULL) {
        Node *arvore = NULL;
        char buffer_saida[1000] = {0};

        linha[strcspn(linha, "\n")] = '\0';
        linha[strcspn(linha, "\r")] = '\0';

        char *token = strtok(linha, delimitador);

        if (contador_linha > 0) {
            strcat(buffer_saida, "\n");
        }

        while (token != NULL) {
            int valor = atoi(token);
            int profundidade = inserir(&arvore, valor);
            char temp[20];
            sprintf(temp, "%d ", profundidade);
            strcat(buffer_saida, temp);
            token = strtok(NULL, delimitador);
        }

        Node *maximo = encontrar_maximo(arvore);
        char temp[50];
        if (maximo->parent_node == NULL) {
            sprintf(temp, "max %d alt %d pred NaN", maximo->data, maximo->depth);
        } else {
            sprintf(temp, "max %d alt %d pred %d", maximo->data, maximo->depth, maximo->parent_node->data);
        }
        strcat(buffer_saida, temp);

        fputs(buffer_saida, fp_out);
        contador_linha++;
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}