#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>


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

double tiempoInsercion(int v[], int n, arbol *A);
double tiempoBusqueda(int v[], int n, arbol *A);

#define N 256000
#define T 500
#define K 1000


int main(){
	double power=1.23;
	int i=0;
	int v[N];
	double mem[6];
	int n;
	double t;
	arbol A=creararbol();
	inicializar_semilla();

	//insercion 1.17
	//busqueda 1.26
	tiempoInsercion(v, 256000, &A);
    tiempoBusqueda(v, 256000, &A);
    A=eliminararbol(A);

	for(n=8000; n<=N; n*=2){
		t=tiempoInsercion(v, n, &A);
		tiempoBusqueda(v, n, &A);
		A=eliminararbol(A);
		mem[i]=t;
		i++;
	}printf("\n");

	while(power<1.25){
		printf("%.3f: ", power);
		n=8000;
		for(i=0; i<=5; i++){
			printf("%.5f ", mem[i]/pow(n, power));
			n*=2;
		}
		printf("\n\n");

		power+=0.001;
	}

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

bool comprobacionInser(int v[], int n, arbol A){
    int i=0;

    for(i=0; i<n; i++){
        if(buscar(v[i], A)==NULL) return false;
    }
    return true;
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



double tiempoInsercion(int v[], int n, arbol *A){
    double t1=0, t2=0, t=0;
    int i=0;

    aleatorio(v, n);
    t1=microsegundos();
    for(i=0; i<n; i++){
        *A=insertar(v[i], *A);
    }
    t2=microsegundos();
    t=t2-t1;
    return t;
}

double tiempoBusqueda(int v[], int n, arbol *A){
    double t1=0, t2=0, t=0;
    int i=0;

    aleatorio(v, n);
    t1=microsegundos();
    for(i=0; i<n; i++){
        buscar(v[i], *A);
    }
    t2=microsegundos();
    t=t2-t1;
    return t;
}