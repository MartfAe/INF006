int buscaLinear(*V, int N, int elem){
    for(i =0; i <N; i++){
        if(V[i]==elem){
            return i;
        }

    }
    return -1;
}