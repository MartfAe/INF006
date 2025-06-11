/*Adapte o programa do exercício 1 para contar quantas comparações e trocas o
 Bubble Sort faz ao ordenar o vetor. Mostre os números na tela ao final.*/

#include <stdio.h>
#include <stdlib.h>

void bubble(int vetor[], int n){
    int comparacoes = 0;
    int trocas = 0;
    for(int i = 0 ; i <n; i++){
        for(int j = 0; j <n-1-i; j++){
            comparacoes++;
            if(vetor[j]>vetor[j+1]){
                trocas++;
                int temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1]= temp;
            }
        }
    }
    printf("Total de comparações: %d.\nTotal de trocas:%d\n", comparacoes, trocas);
}

int main(){
    int tamanho=5;
    int vetor[tamanho];

    for(int i =0; i < tamanho; i++){
        printf("Digite o %d valor de %d do seu vetor: ", i+1, tamanho);
        scanf("%d", &vetor[i]);
    }

    bubble(vetor, tamanho);

    return 0 ; 


}

