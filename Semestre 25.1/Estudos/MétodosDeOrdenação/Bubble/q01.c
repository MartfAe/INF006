/*Escreva um programa que leia um vetor de 5 números inteiros e use o 
Bubble Sort para ordená-lo em ordem crescente.Ao final, imprima o vetor ordenado.*/
#include <stdio.h>
#include <stdlib.h>

void bubble(int v[], int n){
    for(int i =0; i<n; i++){
        for(int j = 0; j <n -1-i; j++){
            if(v[j]>v[j+1]){
                int temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

int main(){
    int tamanho;
    int vetor[tamanho];

    printf("Digite o tamanho do vetor que deseja ordenar:");
    scanf("%d", &tamanho);

    for(int i =0; i <tamanho ;i++){
        printf("Digite o %dº valor de %d do seu vetor:", i+1, tamanho);
        scanf("%d", &vetor[i]);
    }

    bubble(vetor, tamanho);

    printf("Vetor ordenado:\n");
    for(int i =0; i <tamanho; i++){
        printf("%d ", vetor[i]);
    }

    printf("\n");

    return 0;

}