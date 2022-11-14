#include <stdio.h>
#include <time.h>
#include <sys/time.h>
//GENERALES
void ascendente(int [], int);

//TIEMPOS
#define T 500
#define K 1000
double microsegundos();

//MONTICULOS
#define TAM 512000
typedef struct{
    int vector[TAM];
    int ultimo;
}monticulo;
void iniciar_monticulo(monticulo*);
void crear_monticulo(int [], int, monticulo*);
void hundir(monticulo* , int);
int eliminar_mayor(monticulo *);

int main(){
    int v[5];
    ascendente(v, 5);
    for(int j=0; j<5; j++){
        v[j]=j;
    }
    monticulo M;
    iniciar_monticulo(&M);

    crear_monticulo(v, 4, &M);

    for(int i=0; i<=M.ultimo; i++){printf("%d", M.vector[i]);}
    printf("\n%d", eliminar_mayor(&M));
    printf(" %d\n", M.vector[0]);
    
    return 0;
}


//GENERALES
void ascendente(int v [], int n) {
	int i;

	for (i=0; i < n; i++)
	v[i] = i;
}


//TIEMPOS
double microsegundos(){
    struct timeval t;

    if (gettimeofday(&t, NULL)<0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


//MONTICULOS
void iniciar_monticulo(monticulo* M){
    M->ultimo=-1;
}

void crear_monticulo(int v[], int max, monticulo* M){
    int i;
    for(i=0; i<=max; i++){
        M->vector[i]=v[i];
    }
    M->ultimo=max;
    for(i=M->ultimo/2; i>=0; i--){
        hundir(M, i);
    }
}

void hundir(monticulo* M, int i){
    int hizq, hder, j=-1, aux;
    while (j!=i)
    {
        hizq=2*i+1;
        hder=2*(i+1);
        j=i;

        if(hder<=M->ultimo && M->vector[hder]>M->vector[i]){
            i=hder;
        }
        if(hizq<=M->ultimo && M->vector[hizq]>M->vector[i]){
            i=hizq;
        }
        aux=M->vector[i];
        M->vector[i]=M->vector[j];
        M->vector[j]=aux;
    }
}

int eliminar_mayor(monticulo* M){
    int x;
    if(M->ultimo==-1) return -1;
    else{
        x=M->vector[0];
        M->vector[0]=M->vector[M->ultimo];
        M->ultimo=M->ultimo-1;
        if(M->ultimo>-1) hundir(M,0);
        return x;
    }
}

testTiempo_monticulo(int v[], int n, monticulo M){
    double t1, t2, t;
    int i;
    ascendente(v, n);

    t1=microsegundos();
        crear_monticulo(v, n-1, &M);
    t2=microsegundos();
    t=t2-t1;
    if(t<T){
        t1=microsegundos();
        for(i=0; i<=K; i++) crear_monticulo(v, n-1, &M);
        t2=microsegundos();
        t=(t2-t1)/K;
    }
    return t;
}