#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

//GENERALES
void inicializar_semilla();
void aleatorio(int [], int);
void ascendente(int [], int);
void descendente(int [], int);
void setVedtor(int [], int, int);

//TIEMPOS
#define N 8000
#define S 500
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

//ORDENACION
void ord_monticulo(int [], int);

//TESTS_TIEMPOS
double testTiempo_monticulo(int [], int, monticulo);
double testTiempos_ord_monticulos(int [], int , monticulo);

//TESTES
bool testOrd_monticulos(int [], int);


int main(){
    int v[N];
    inicializar_semilla();
    testOrd_monticulos(v, S);

    return 0;
}


//GENERALES
void inicializar_semilla() {
    srand(time(NULL));
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;

    for (i=0; i < n; i++)
    v[i] = (rand() % m) - n;
}

void ascendente(int v [], int n) {
    int i;

    for (i=0; i < n; i++)
    v[i] = i;
}

void descendente(int v[], int n){
    int i, i2=0;

    for(i=n-1; i>=0; i--){
        v[i2]=i;
        i2++;
    }
}

void setVedtor(int v[], int n, int s){
    switch (s)
    {
    case 1:
        aleatorio(v, n);
        break;
    case 2:
        ascendente(v, n);
        break;
    case 3:
        descendente(v, n);
        break;
    
    default:
        break;
    }
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
    for(i=0; i<=max-1; i++){
        M->vector[i]=v[i];
    }
    M->ultimo=max-1;
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


//ORDENACION
void ord_monticulo(int v[], int n){
    int i;
    monticulo M;
    iniciar_monticulo(&M);
    crear_monticulo(v, n, &M);
    for(i=n; i==1; i--){
        v[i]=eliminar_mayor(&M);
    }
}


//TEST_TIEMPOS
double testTiempo_monticulo(int v[], int n, monticulo M){
    double t1, t2, t;
    int i;
    setVedtor(v, n, 2);

    t1=microsegundos();
        crear_monticulo(v, n, &M);
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

double testTiempos_ord_monticulos(int v[], int n, monticulo M){
    double t1, t2, t;
    int i;
    setVedtor(v, n, 1);

    t1=microsegundos();
        ord_monticulo(v, n);
    t2=microsegundos();
    t=t2-t1;
    if(t<T){
        t1=microsegundos();
        for(i=0; i<=K; i++){
            setVedtor(v, n, 1);
            ord_monticulo(v, n);
        }
        t2=microsegundos();
        t=t2-t1;
        t1=microsegundos();
        for(i=0; i<=K; i++){
            setVedtor(v, n, 1);
        }
        t2=microsegundos();
        t=(t-t2+t1)/K;
    }
    return t;
}


//TESTS
bool testOrd_monticulos(int v[], int n){
	int i;
	bool ret=true;

    setVedtor(v, n, 1);
    ord_monticulo(v, n);

	for(i=1; i<n; i++){
		if(v[i]<v[i-1]) ret=false;
	}
	return ret;
}