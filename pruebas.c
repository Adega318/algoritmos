#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

#define N 32000
#define T 500
#define K 1000
#define umbral 100

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

void ord_ins(int v[], int n){
	int x, j, i;

	for(i=1; i<n; i++){
		x=v[i];
		j=i-1;
		while(j>=0 && v[j]>x){
			v[j+1]=v[j];
			j=j-1;
		}
		v[j+1]=x;
	}
}

double microsegundos(){
    struct timeval t;

    if (gettimeofday(&t, NULL)<0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void setvect(int v[], int n, int tipo){
	switch (tipo){
	case 1:
		aleatorio(v, n);
		break;
	case 2:
		ascendente(v, n);
		break;
	case 3:
		descendente(v, n);
		break;
	}
}

void intercambio(int v[], int a, int b){
	int aux;
	aux=v[a];
	v[a]=v[b];
	v[b]=aux;
}

void rapida_aux(int v[], int izq, int der){
	int x, pivote, i, j;

	if(izq+umbral<=der){
		x=rand() % (der-izq+1);
		x=x+izq;

		pivote=v[x];

		intercambio(v, izq, x);

		i=izq+1;
		j=der;

		while (i<=j){ 
			while((i<=der) && (v[i]<pivote)) i++;
			while (v[j]>pivote) j--;

			if(i<=j){ //1
				intercambio(v, i, j);

				i++;
				j--;
			}
		}
		
		intercambio(v, izq, j);

		rapida_aux(v, izq, j-1);
		rapida_aux(v, j+1, der);
	}
}

void ord_rapida(int v[], int n){
	rapida_aux(v, 0, n-1);
	if(umbral>1) ord_ins(v,n);
}



double timeTest2(int v[], int n, int tipo){
	double t1=0, t2=0, t=0;
	int i=0;

	setvect(v, n, tipo);

	t1=microsegundos();
	ord_rapida(v, n);
	t2=microsegundos();
	
	t=(t2-t1);
	if(t<T){
		t1 = microsegundos();
        for(i=0;  i<K; i++){
			setvect(v, n, tipo);
			ord_rapida(v, n);
		}
		t2 = microsegundos();
		t=(t2-t1);

		t1 = microsegundos();
        for(i=0;  i<K; i++){
			setvect(v, n ,tipo);
		}
		t2 = microsegundos();

		t=((t-(t2-t1))/K);
	}
	return t;
}



int main(){
	int v[N];
	int n, tipo=3;
	double t;
	inicializar_semilla();

	for(int i=0; i<=50; i++){
		for(n=500; n<=N; n=n*2){
			t=timeTest2(v, n, tipo);
			printf("(%d,%d),", n, (int)t);
		}
	}
	
	printf("\n");
	return 0;
}

/*
umbral 1:
aleatorio 1.10920
ascendente 1.08706
descendente 1.08562

umbral 10:
aleatorio 1.12212
ascendente 1.12423
descendente 1.10663

umbral 100:
aleatorio 1.11066
ascendente 1.21391
descendente 1.13627
*/