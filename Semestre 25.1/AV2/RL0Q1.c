#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- ESTRUTURAS E FUNÇÕES AUXILIARES ---
typedef struct{
    int *numeros;
    int tamanho;
    int capacidade; 
    long long sum; 
    int ordemOriginal;
    int manter; 
}listaNumeros;

int comparaInteiros(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

int comparaLista(const void *a, const void *b){
    const listaNumeros* listaA =(const listaNumeros*)a;
    const listaNumeros* listaB =(const listaNumeros*)b;
    if(listaB->sum > listaA->sum) return 1;
    if(listaB->sum <listaA->sum) return -1;
    return 0;
}

void addNumLista(listaNumeros* lista, int numero){
    if(lista->tamanho >= lista->capacidade){
        lista -> capacidade = (lista -> capacidade ==0) ? 10 : lista-> capacidade*2;
        lista -> numeros = (int*)realloc(lista->numeros, lista->capacidade * sizeof(int));
    }
    lista->numeros[lista->tamanho++]= numero;
    lista->sum += numero;
}

// --- FUNÇÕES DE ARQUIVO ---
FILE* abrir_arquivo(const char *nome_do_arquivo, const char *modo) {
    FILE *arquivo = fopen(nome_do_arquivo, modo);
    if (arquivo == NULL) {
        char msg_erro[100];
        sprintf(msg_erro, "Erro ao abrir o arquivo '%s'", nome_do_arquivo);
        perror(msg_erro);
        exit(EXIT_FAILURE);
    }
    return arquivo;
}

void fechar_arquivo(FILE *arquivo) {
    if (arquivo != NULL) {
        fclose(arquivo);
    }
}

// --- FUNÇÃO PRINCIPAL ---
int main(){
    FILE *arquivo_in = abrir_arquivo("L1Q1.in", "r");
    FILE *arquivo_out = abrir_arquivo("L1Q1.out", "w");

    char line[3001];

    while(fgets(line, sizeof(line), arquivo_in) != NULL){
        line[strcspn(line, "\n")] = 0;
        listaNumeros listas[1000];
        int contadorLista = 0;
        char *token = strtok(line, " ");
        
        while(token != NULL){
            if(strcmp(token, "start")==0){
                if(contadorLista > 0 && listas[contadorLista-1].tamanho ==0){}
                else{
                    if (contadorLista < 1000) { // Adicionando uma verificação de segurança
                        listas[contadorLista] = (listaNumeros){.numeros=NULL, .tamanho = 0, .capacidade = 0, .sum=0, .ordemOriginal = contadorLista, .manter =1 };
                        contadorLista++;
                    }
                }
            } else if(contadorLista > 0 && (isdigit(token[0]) || (token[0]=='-' && isdigit(token[1])))){
                addNumLista(&listas[contadorLista-1], atoi(token));
            }
            token = strtok(NULL, " ");
        }

        for(int i =0; i <contadorLista; i++){
            if(listas[i].tamanho > 0) qsort(listas[i].numeros, listas[i].tamanho, sizeof(int), comparaInteiros);
        }

        for(int i = contadorLista-1; i >=0; i--){
            if(!listas[i].manter){ 
                continue; 
            }
            for(int j = i-1; j >=0; j--){
                if(listas[j].sum == listas[i].sum){
                    listas[j].manter = 0;
                }
            }
        }
        
        listaNumeros listaFinal[1000];
        int contadorFinal = 0;
        for(int i = 0; i < contadorLista; i++){
            if(listas[i].manter && listas[i].tamanho > 0){
                if (contadorFinal < 1000) { // Adicionando uma verificação de segurança
                    listaFinal[contadorFinal++] = listas[i];
                }
            } else {
                free(listas[i].numeros);
            }
        }

        qsort(listaFinal, contadorFinal, sizeof(listaNumeros), comparaLista);

        for(int i = 0; i < contadorFinal; i++){
            fprintf(arquivo_out, "start");
            for(int j = 0; j < listaFinal[i].tamanho; j++){
                fprintf(arquivo_out, " %d", listaFinal[i].numeros[j]);
            }
            if(i < contadorFinal - 1){
                fprintf(arquivo_out, " ");
            }
            free(listaFinal[i].numeros);
        }
        fprintf(arquivo_out, "\n");
    }
    
    fechar_arquivo(arquivo_in);
    fechar_arquivo(arquivo_out);

    printf("Processo concluído. Verifique o arquivo L1Q1.out.\n");

    return 0;
}