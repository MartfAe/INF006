
//Complexidade:O(nlog(n))
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