#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void bubble(int vet[], int tam){
    int temp; 
    for(int i =0; i <tam-1; i++){
        for(int j=0; j <tam-i-1; j++){
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

    preencherVetor(vet, tam);
    printf("Vetor original:\n");
    imprimirVetor(vet, tam);
    bubble(vet,tam);
    printf("\nVetor organizado:\n");
    imprimirVetor(vet, tam);
    printf("\n");
    return 0;
}

