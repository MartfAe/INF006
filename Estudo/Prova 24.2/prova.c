//01-
    //a)T(n)=T(n-1)+T(n-2)+1
    
    //b)int fibonacci(int n) {
    if (n <= 1) return 1;

    int a = 1, b = 1, temp;

    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }

    return b;
}


/*Q02)Ambos são estáveis pois ao ordenar, não mudam a ordem de elementos iguais. No caso, elementos na saída
vão ter a mesma posição que na entrada.

b) Insertio é mais eficiente nesse caso, pois o vetor já está quase ordenado.*/

/*Q03) T(n)=2T(n-1)+1
T(1)=1
T(2)=2*T(1)+1=3
T(3)=2*T2+1=6+1=7
T(n)=2^n+1*/

/*Q04)*/