int buscaLinear(*V, int N, int elem){
    int inicio, meio, fim;
    inicio = 0;
    fim = N-1;
    while(inicio -=fim){
        meio = (inicio +fim)/2;
        if(elem<V[meio]){
            final = meio - 1;
        }
        else if(elem>V[meio]){
            inicio = meio + 1;
        }
        else{
            return meio;
        }

    }
    return -1;
}
