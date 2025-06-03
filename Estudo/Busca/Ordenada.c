int buscaLinear(*V, int N, int elem){
    for(i =0; i <N; i++){
        if(V[i]==elem){
            return i;
        }else if(elem <V[i]){
            return -1;
        }
        }

    }
    return -1;
}