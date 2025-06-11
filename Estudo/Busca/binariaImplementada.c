#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int buscaBinaria(int vet[], int tam, int busca){
    int inicio =0, fim = tam-1, meio;
    while(inicio<=fim){
        meio=(inicio+fim)/2;
        if(vet[meio]==busca){
            return meio;
        }else if(vet[meio]>busca){
            fim = meio -1;
        }else{ 
            inicio = meio +1;
        }
        }
        return -1;
    }


void bubble(int vet[], int tam){
    int temp;
    for(int i =0; i <tam-1; i++){
        for(int j=0; j<tam-i-1; j++){
            if(vet[j]>vet[j+1]){
                temp=vet[j];
                vet[j]=vet[j+1];
                vet[j+1]=temp;
            }

        }
    }
}

void preencherVetor(int vet[], int tam){
    for(int i =0; i <tam; i++){
        vet[i]=rand()%100;
    }
}

void imprimirVetor(int vet[], int tam){
    for(int i =0; i<tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}

int main(){
    srand(time(NULL));
    int vet[10];
    int tam=10; 
    int busca;

    preencherVetor(vet, tam);
    printf("Vetor original:\n");
    imprimirVetor(vet, tam);
    printf("\nVetor organizado:\n");
    bubble(vet,tam);
    imprimirVetor(vet, tam);
    printf("digite um elemento para ser buscado:");
    scanf("%d", &busca);
    int resultado = buscaBinaria(vet, tam, busca);
    if(resultado != -1){
        printf("Elemento %d encontrado na posicao %d\n", busca, resultado);
    }
    printf("\n");
    return 0;
}

