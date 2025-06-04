
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