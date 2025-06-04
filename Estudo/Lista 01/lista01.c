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


//Q04:
//Complexidade:O(n)
void mergeCrescente(int a[], int b[], int c[], int n){
    int i =0, j=0, m=0;
    while(i<n && j<n){
        if(a[i]<b[j]){
            c[m]== a[i];
            i++;
        }else{
            c[m]= b[j];
            j++;
        }
        m++;
    }
    while(i<n){
        c[m]= a[i];
        i++;
        m++;
    }
    while(j<n){
        c[m]= b[j];
        j++;
        m++;
    }
}

mergeDecrescente(int a[], int b[], int c[], int n){
    int i =n-1, j=n-1, m=0;
    while(i>=0 && j>=0){
        if(a[i]>b[j]){
            c[m]= a[i];
            i--;
        }else{
            c[m]= b[j];
            j--;
        }
        m++;
    }
    while(i>=0){
        c[m]= a[i];
        i--;
        m++;
    }
    while(j>=0){
        c[m]= b[j];
        j--;
        m++;
    }
}

/*Q5: 
Bubble, Insertion e Merge são estáveis.
Bubble: [2s, 2d,1]- 1º passo, n troca, igauais. 2º troca 2d com 1. 3º troca 2s com 1, 2s e 2d mantém ordem
Intertion: [3, 2, 2]=pega 3 pra ordenar- compara 3 com 2, [2,3] e[2], compara 3 e 2, vira [2,2,3]
Merge[2,1,2], divide [2,1] e [2]- Compara 2 e1, [1,2] e [2], junta. 
*/

/*Q6
T(n)=T(n-1)+T(n-2)+1
fibonacci=f(n-1) + f(n-2);
n=0; f=1;
n=1; f = 1
n = 2; f = (f1)+f0=2*/
int fibonacci(int n){
    if(n<=1){
        return n;
    }
    int a =0;
    b=1;
    for(int i =2; i<n; i++){
        int temp = a+b;
        a=b;
        b=temp;
    }
    return b;
}

//Q7a) Insertion Sort, porque (10*10)/4 = 25 . Merge = log8 = 3 e log16 = 4; log8<log10<log6) *10 > insertion
//log = 2^x 

/*Q09) O insertion acaba sendo melhor que o selection para dados quase ordenados.
 O selection faz menos troca que o insertion.*/

 /*Q10)*/

 /*Q11)O algoritmo B deve ser utilizado para quando 2^N<5n^5*/

 /*Q12) Responsável por medir a memória total que o algoritmo utiliza.*/