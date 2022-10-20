//Enrique Adega Fernandez - e.adega@udc.es 
// Antonio Buceta Paz - antonio.buceta@udc.es


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

void inicializar_semilla();
void aleatorio(int v [], int n);
void ascendente(int v [], int n);
void descendente(int v[], int n);
bool testOrden(int v[], int n);
void printV(int v[], int n);
void ord_ins(int v[], int n);
double microsegundos();
void setvect(int v[], int n, int tipo);
double timeTest(int v[], int n, int tipo);
double CAleatoria(int n);
double CAscendente(int n);
double CDescendente(int n);
void intercambio(int v[], int a, int b);
void rapida_aux(int v[], int izq, int der);
void ord_rapida(int v[], int n);
double timeTest2(int v[], int n, int tipo);

#define N 32000
#define T 500
#define K 1000
#define umbral 10

int main(){
	int v[N];
	int n;
	double t;
	inicializar_semilla();
	
	
	//tiempos de ordenación por inserción
	printf("Ordenación por inserción\n");
	printf("|aleatorio:\n|n:\t|t(n)\t\t\t|subestimada\t|ajustada\t|sobrestimada\n");
	for(n=500; n<=N; n=n*2){
		printf("|%6d\t|",n);
		t=timeTest(v, n, 1);
		printf("%14.5f\t| %1.8f\t| %1.8f\t| %1.8f\n", t, t/pow(n, 1.8), t/pow(n, 1.99), t/pow(n, 2.2));
	}printf("\n");

	printf("|ascendente:\n|n:\t|t(n)\t\t\t|subestimada\t|ajustada\t|sobrestimada\n");
	for(n=500; n<=N; n=n*2){
		printf("|%6d\t|",n);
		t=timeTest(v, n, 2);
		printf("%14.5f\t| %1.8f\t| %1.8f\t| %1.8f\n", t, t/pow(n, 0.8), t/pow(n, 1), t/pow(n, 1.2));
	}printf("\n");

	printf("|descendente:\n|n:\t|t(n)\t\t\t|subestimada\t|ajustada\t|sobrestimada\n");
	for(n=500; n<=N; n=n*2){
		printf("|%6d\t|",n);
		t=timeTest(v, n, 3);
		printf("%14.5f\t| %1.8f\t| %1.8f\t| %1.8f\n", t, t/pow(n, 1.8), t/pow(n, 1.99), t/pow(n, 2.2));
	}printf("\n");

	//tiempos de ordenación rápida con umbrales 1, 10 y 100
	printf("\nOrdenación rapida umbral: %d\n", umbral); 
	printf("|aleatorio:\n|n:\t|t(n)\t\t\t|subestimada\t|ajustada\t|sobrestimada\n");
	for(n=500; n<=N; n=n*2){
		printf("|%6d\t|",n);
		t=timeTest2(v, n, 1);
		printf("%14.5f\t| %1.8f\t| %1.8f\t| %1.8f\n", t, t/pow(n, 1), t/pow(n,1.12)/*CAleatoria(n)*/, t/(pow(n, 1.3)));
	}printf("\n");

	printf("|ascendente:\n|n:\t|t(n)\t\t\t|subestimada\t|ajustada\t|sobrestimada\n");
	for(n=500; n<=N; n=n*2){
		printf("|%6d\t|",n);
		t=timeTest2(v, n, 2);
		printf("%14.5f\t| %1.8f\t| %1.8f\t| %1.8f\n", t, t/pow(n, 1), t/pow(n,1.12)/*CAscendente(n)*/, t/pow(n, 1.3));
	}printf("\n");

	printf("|descendente:\n|n:\t|t(n)\t\t\t|subestimada\t|ajustada\t|sobrestimada\n");
	for(n=500; n<=N; n=n*2){
		printf("|%6d\t|",n);
		t=timeTest2(v, n, 3);
		printf("%14.5f\t| %1.8f\t| %1.8f\t| %1.8f\n", t, t/pow(n, 1), t/pow(n,1.12)/*CDescendente(n)pow(n,1.12)*/, t/pow(n, 1.3));
	}printf("\n");
	return 0;
}

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

bool testOrden(int v[], int n){
	int i;
	bool ret=true;

	for(i=1; i<n; i++){
		if(v[i]<v[i-1]) ret=false;
	}
	return ret;
}

void printV(int v[], int n){
	int i;

	for(i=0; i<n; i++){
		printf("|%3d", v[i]);
	}
	printf("\n\n");
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

double timeTest(int v[], int n, int tipo){
	double t1=0, t2=0, t=0;
	int i=0;

	setvect(v, n, tipo);

	t1=microsegundos();
	ord_ins(v, n);
	t2=microsegundos();
	
	t=(t2-t1);
	if(t<T){
		t1 = microsegundos();
        for(i=0;  i<K; i++){
			setvect(v, n, tipo);
			ord_ins(v, n);
		}
		t2 = microsegundos();
		t=(t2-t1);

		t1 = microsegundos();
        for(i=0;  i<K; i++){
			setvect(v, n, tipo);
		}
		t2 = microsegundos();

		t=((t-(t2-t1))/K);

		printf("(*)");
	}else printf("   ");
	return t;
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

double CAleatoria(int n){
	double potencia;
	switch (umbral)
	{
	case 1:
		potencia=1.11;
		break;
	case 10:
		potencia=1.12;
		break;
	case 100:
		potencia=1.11;
		break;
	default:
		potencia=1;
		break;
	}
	return pow(n, potencia);
}

double CAscendente(int n){
	double potencia;
	switch (umbral)
	{
	case 1:
		potencia=1.09;
		break;
	case 10:
		potencia=1.12;
		break;
	case 100:
		potencia=1.21;
		break;
	default:
		potencia=1;
		break;
	}
	return pow(n, potencia);
}

double CDescendente(int n){
	double potencia;
	switch (umbral)
	{
	case 1:
		potencia=1.08;
		break;
	case 10:
		potencia=1.11;
		break;
	case 100:
		potencia=1.14;
		break;
	default:
		potencia=1;
		break;
	}
	return pow(n, potencia);
}

void intercambio(int v[], int a, int b){
	int aux;
	aux=v[a];
	v[a]=v[b];
	v[b]=aux;
}


//ordenacion rapida
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

		printf("(*)");
	}else printf("   ");
	return t;
}