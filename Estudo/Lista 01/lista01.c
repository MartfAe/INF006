//Q01:
// 1 <logn<n<nlogn<n^2<n^3<n^4<n^5<2^n<n!

// Q02:
//a) Complexidade: O(n)
for(int i =0; i <n; i++){
    if(vet[i]==busca){
        return i;
    }
}

//b) Complexidade: O(log2N)
int inicio =0, fim = n-1, meio;
while(inicio<=fim){
    meio=(inicio+fim)/2
if(vet[meio]==busca){
    return meio;
    }else if(vet[meio]>busca){
        fim = meio-1;
    }else{
        inicio = meio +1;
    }
}

//c) Complexidade: O(n)

if(M>=N){
    printf("Vetor cheio");
    return;
}
int i = M-1;

while(i>=0 && vet[i]>novoElemento){
    vet[i+1]=vet[i];
    i--;
}
vet[i+1]= novoElemento;
M++;

// Q03: 
//Pior caso, pivô: É quando o pivô gera partições desiguais.
//Se o vetor já está ordenado (ex: [1, 2, 3, 4, 5]) ou invertido (ex: [5, 4, 3, 2, 1]).
//Com [1, 2, 3, 4, 5], o pivô 1 particiona em [] e [2, 3, 4, 5].
//Na próxima chamada, o pivô 2 particiona em [] e [3, 4, 5], e assim por diante.

b)/*Menor memória auxiliar para os dados, constantes menores e melhor localidade de cache.*/

//c) Ebora tenham o mesmo grau de complexidade, o Quicksort é geralmente mais rápido que o Mergesort em prática.
//O quick sempre divide e intercala da mesma forma, já o merge o pivô divide o vetor em duas partes, quase iguais. 

