#include <stdio.h>
​
​
int sum(const int a[], int i, int j); 
int max(int x, int y);
​
int main(void)
{   
    /*
    In c le variabili quando vengono dichiarate non si inizializzano a 0 automaticamente,
    ma viene solo riservato lo spazio in memoria per quella variabile, 
    mantenendo il dato che c'era prima in quello spazio.
    
    Qui c'erano 2 errori:
    il primo è che inizializzavi le matrici e l'array prima di ricevere le dimensioni in ingresso
    
    il secondo è il core dump, che è dovuto in parte dal primo;
    ossia cercavi di inizializzare h,V,p,c,x con un valore non definito da te,
    infatti prendeva il dato che c'era prima in quello spazio di memoria, e poteva essere un valore grandissimo 
    e quindi uscivi fuori dallo spazio utente assegnato all'esecuzione del programma 
    ed il sitema operativo quindi lo terminava.
​
    */
    int N=0; //numero grattaceli
    int K=0; //numero dei piani
​
    printf("Numero di grattacieli: N="); 
    scanf("%d", &N); 
    printf("Numero di colori: K="); 
    scanf("%d", &K); 
​
    int i; //indice grattacelo 
    int k; //indice colore
    int j;
​
    int h[N]; //piani del grattacelo
    int V[N][K]; 
    int p[N][K]; 
    int c[N]; //colore grattacelo
    int z[K];
​
    printf("Il vettore h del numero di piani di ciascun grattacielo e`:\n"); 
    
    for(i=0; i<N; i++){
        scanf("%d", &h[i]); 
    }
​
    // azzeramento
    for(i=0; i<N; i++){ 
        c[i]=0;
        for(k=0; k<K; k++){
            V[i][k]=0; 
            p[i][k]=0;
        }
    }
​
    for(k=0; k<K; k++){ 
        z[k]=0; 
    }
​
    for(i=0; i<N; i++){ 
        V[i][0] = sum(h,0,i);
    }
​
    for(k=1; k<K; k++){ 
        for(i=k; i<N; i++){
            V[i][k] = max(V[k-1][k-1], sum(h,k,i));
            p[i][k] = k-1;
​
            for(j=k; j<i; j++){
                if(max(V[j][k-1], sum(h,j+1,i))<V[i][k]){
                    V[i][k] = max(V[j][k-1], sum(h, j+1, i));
                    p[i][k] = j; 
                } 
            } 
        }
    } 
                    
    z[k-1]=N;
    for(k=1; k<K; k++){
        z[K-k-1] = p[z[K-k]][K-k];
    }
​
    
    j=0;
    c[0]=1;
​
    for(i=1; i<N; i++){
        if(i<z[j]){
            c[i] = c[i-1];
        }else{
            c[i] = c[i-1]+1;
            j = j+1;
        }
    }
​
​
    for(i=0; i<N; i++){
        printf("Il grattacielo numero %d e` di colore %d.\n", i+1, c[i]);
    }
​
    return 0;
}
​
int sum(const int a[], int i, int j){ 
    
    int s = 0; 
    for(int k=i; k<=j; k++){ 
        s=s+a[k];
    }
    return s;
}
​
/*
è più efficente fare la funzione max in questo modo
*/
int max(int x, int y){ 
​
    if(y>=x){ 
        return y; 
    } 
    return x; 
}
