/*Modifique o exercício anterior para que o vetor seja ordenado em ordem decrescente.*/

#include <stdio.h>
#include <stdlib.h>

void bubble(int v[], int tam){
    for(int i =0; i < tam; i++){
        for(int j = 0 ; j < tam -i - 1; j++){
            if(v[j]<v[j+1]){
                int temp = v[j];
                v[j]= v[j+1];
                v[j+1] = temp;
            }
        
        }
    }
}


int main(){
    int tamanho;
    int vetor[tamanho];

    printf("Informe o tamanho desejado para seu vetor:");
    scanf("%d", &tamanho);

    for(int i =0; i <tamanho; i++){
        printf("Digite o %dº valor de %d do seu vetor: ", i+1, tamanho);
        scanf("%d", &vetor[i]);
    }

    bubble(vetor, tamanho);

    printf("Vetor ordenado em ordem decrescente:\n");

    for(int i =0; i <tamanho; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}