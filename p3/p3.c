#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


struct nodo{
	int elem;
	int num_repeticiones;
	struct nodo *izq, *der;
};

typedef struct nodo *posicion;
typedef struct nodo *arbol;

//Declaracion de funciones del arbol
arbol creararbol();
int esarbolvacio(arbol A);
static struct nodo *crearnodo(int e);
arbol insertar(int e, arbol A);
posicion buscar(int buscado, arbol A);
arbol eliminararbol(arbol A);

posicion hijoizquierdo(arbol A);
posicion hijoderecho(arbol A);
int elemento(posicion P);
int numerorepeticiones(posicion P);

int altura(arbol A);
void visualizar(arbol A);

//Funciones de cotas
double microsegundos();
void inicializar_semilla();
void aleatorio(int v [], int n);

double tiempoInsercion(int v[], int n);
double tiempoBusqueda(int v[], int n);

#define N 256000
#define T 500
#define K 1000


int main(){
	int v[N];
	int n;
	double t;
	inicializar_semilla();


	printf("Insercion de n elementos:\n");
	printf("|n       |t(n)       |t(n)/n^1.18 |t(n)/n^1.25 |t(n)/n^1.3\n");
	for(n=8000; n<=N; n*=2){
		t=tiempoInsercion(v, n);
		printf("| %6d | %9.2f | %.8f | %.8f | %.8f\n", n, t, t/pow(n, 1.05), t/pow(n, 1.25), t/pow(n, 1.3));
	}printf("\n");

	printf("Busqueda de n elementos:\n");
	printf("|n       |t(n)       |t(n)/n^1.22 |t(n)/n^1.27 |t(n)/n^1.32\n");
	for(n=8000; n<=N; n*=2){
		t=tiempoBusqueda(v, n);
		printf("| %6d | %9.2f | %.8f | %.8f | %.8f\n", n, t, t/pow(n, 1.22), t/pow(n, 1.27), t/pow(n, 1.32));
	}
	printf("\n");

	return 0;
}



arbol creararbol(){
	arbol A=NULL;
	return A;
}

int esarbolvacio(arbol A){
	return A==NULL;
}

static struct nodo *crearnodo(int e){
	struct nodo *p = malloc(sizeof(struct nodo));
	if (p == NULL) {
		printf("memoria agotada\n");
		exit(EXIT_FAILURE);
	}
	p->elem = e;
	p->num_repeticiones = 1;
	p->izq = NULL;
	p->der = NULL;
	return p;
}

arbol insertar(int e, arbol A){
	if (A == NULL)
		return crearnodo(e);
	else if (e < A->elem)
		A->izq = insertar(e, A->izq);
	else if (e > A->elem)
		A->der = insertar(e, A->der);
	else
		A->num_repeticiones++;
	return A;
}

posicion buscar(int buscado, arbol A){
	posicion p;
	if(esarbolvacio(A)==0){
		if(A->elem==buscado) p= A;
		if(A->elem<buscado) p= buscar(buscado, A->der);
		if(A->elem>buscado) p= buscar(buscado, A->izq);
	}else p= NULL;
	return p;
}

arbol eliminararbol(arbol A){
	if(esarbolvacio(A)==0){
		eliminararbol(A->izq);
		eliminararbol(A->der);
		free(A);
		A=NULL;
	}
	return A;
}

posicion hijoderecho(arbol A){
	return A->der;
}

posicion hijoizquierdo(arbol A){
	return A->izq;
}

int elemento(posicion P){
	return P->elem;
}

int numerorepeticiones(posicion P){
	return P->num_repeticiones;
}


int altura(arbol A){
    if(esarbolvacio(A)==1){
        return 0;
    }else return 1 + fmax(altura(A->izq),altura(A->der));
}

void visualizar(arbol A){
    if(esarbolvacio(A)==0){
		if(esarbolvacio(A->izq)==0){
			printf("(");
			visualizar(A->izq);
			printf(")");
		}
		printf("%d", A->elem);
		if(esarbolvacio(A->der)==0){
			printf("(");
			visualizar(A->der);
			printf(")");
		}
	}else printf("Vacio");
}


//TIEMPOS
double microsegundos(){
    struct timeval t;

    if (gettimeofday(&t, NULL)<0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
	srand(time(NULL));
}

void aleatorio(int v [], int n) {
	int i, m=2*n+1;

	for (i=0; i < n; i++)
	v[i] = (rand() % m) - n;
}



double tiempoInsercion(int v[], int n){
	double t1=0, t2=0, t=0;
	int i=0;
	arbol A=creararbol();


	aleatorio(v, n);
	t1=microsegundos();
	for(i=0; i<n; i++){
		A=insertar(v[i], A);
	}
	t2=microsegundos();
	t=t2-t1;
	A=eliminararbol(A);
	return t;
}

double tiempoBusqueda(int v[], int n){
	double t1=0, t2=0, t=0;
	int i=0;
	arbol A=creararbol();

	aleatorio(v, n);
	for(i=0; i<n; i++){
		A=insertar(v[i], A);
	}

	aleatorio(v, n);
	t1=microsegundos();
	for(i=0; i<n; i++){
		buscar(v[i], A);
	}
	t2=microsegundos();
	t=t2-t1;
	A=eliminararbol(A);
	return t;
}