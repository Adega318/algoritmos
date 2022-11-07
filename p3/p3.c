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

//ARBOL
arbol crearArbol();
int esarbolvacio(arbol A);
static struct nodo *crearnodo(int e);
arbol insertar(int e, arbol A);
posicion buscar(int buscado, arbol A);
arbol eliminarArbol(arbol A);
posicion hijoizquierdo(arbol A);
posicion hijoderecho(arbol A);
int elemento(posicion P);
int numeroRepeticiones(posicion P);
int altura(arbol A);
void visualizar(arbol A);

//TEST
void test();

//RANDOM
void inicializar_semilla();
void aleatorio(int v [], int n);

//TIEMPOS
double microsegundos();
double tiempoInsercion(int v[], int n, arbol *A);
double tiempoBusqueda(int v[], int n, arbol *A);


#define N 256000
#define T 500
#define K 100
#define S 8000


int main(){
    int i=0, n, v[N];
    double mem[(int)log2(N/S)+1][2], t;
    arbol A=crearArbol();
    inicializar_semilla();

    for(n=S, i=0; n<=N; n*=2, i++){
        mem[i][0]=tiempoInsercion(v, n, &A);
        mem[i][1]=tiempoBusqueda(v, n, &A);
        A=eliminarArbol(A);
    }

    printf("\n|n       |t_ins(n)  |t_bus(n)\n");
    for(n=S, i=0; n<=N; n*=2, i++){
        printf("| %6d |", n);
        if(mem[i][0]==0) printf(" *"); else printf("  ");
        printf(" %6.0f |", mem[i][0]);
        if(mem[i][1]==0) printf(" *"); else printf("  ");
        printf(" %6.0f\n", mem[i][1]);
    }printf("\n");

    printf("Insercion de n elementos:\n");
    printf("|n       |t(n)       |t(n)/n^0.99 |t(n)/n^1.20 |t(n)/n^1.5\n");
    for(n=S, i=0; n<=N; n*=2, i++){
        t=mem[i][0];
        printf("| %6d | %9.2f | %.8f | %.8f | %.8f\n",
        n, t, t/pow(n, 0.99), t/pow(n, 1.2), t/pow(n, 1.5));
    }printf("\n");

    printf("Busqueda de n elementos:\n");
    printf("|n       |t(n)       |t(n)/n^1.01 |t(n)/n^1.25 |t(n)/n^1.55\n");
    for(n=S, i=0; n<=N; n*=2, i++){
        t=mem[i][1];
        printf("| %6d | %9.2f | %.8f | %.8f | %.8f\n",
        n, t, t/pow(n, 1.01), t/pow(n, 1.26), t/pow(n, 1.55));
    }printf("\n");

    return 0;
}


//ARBOL
arbol crearArbol(){
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

arbol eliminarArbol(arbol A){
    if(esarbolvacio(A)==0){
        eliminarArbol(A->izq);
        eliminarArbol(A->der);
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

int numeroRepeticiones(posicion P){
    return P->num_repeticiones;
}


int altura(arbol A){
    if(esarbolvacio(A)==1){
        return -1;
    }else return 1 + fmax(altura(A->izq),altura(A->der));
}

void visualizar(arbol A){
    printf("(");
    if(esarbolvacio(A)==0){
        if(esarbolvacio(A->izq)==0){
            visualizar(A->izq);
        }
        printf("%d", A->elem);
        if(esarbolvacio(A->der)==0){
            visualizar(A->der);
        }
    }printf(")");
}


//TEST
void test() {
    int i;
    arbol A = crearArbol();
    printf("Arbol vacio: ");
    visualizar(A);

    printf("\n");
    printf("Altura del arbol: %d\n", altura(A));

    printf("Insertamos por este orden 3-1-2-5-4-5 al arbol vacio\n");
    A = insertar(3, A);
    A = insertar(1, A);
    A = insertar(2, A);
    A = insertar(5, A);
    A = insertar(4, A);
    A = insertar(5, A);

    printf("Arbol: ");
    visualizar(A);
    printf("\nAltura del arbol: %d\n", altura(A));

    for(i = 1; i <= 6; i++) {
        printf("Busco %d y ", i);
        if(buscar(i, A) != NULL) {
            printf("encuentro %d repetido: %d veces\n", i,
                   numeroRepeticiones(buscar(i, A)));
        } else {
            printf("no encuentro nada\n");
        }
    }

    printf("Elimino el arbol\n");
    A = eliminarArbol(A);
    printf("Arbol vacío: ");
    visualizar(A);
    printf("\nAltura del arbol: %d\n", altura(A));
}


//ALEATORIO
void inicializar_semilla() {
    srand(time(NULL));
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;

    for (i=0; i < n; i++)
    v[i] = (rand() % m) - n;
}


//TIEMPOS
double microsegundos(){
    struct timeval t;

    if (gettimeofday(&t, NULL)<0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

double tiempoInsercion(int v[], int n, arbol *A){
    double t1, t2, t;
    int i;

    aleatorio(v, n);
    t1=microsegundos();
    for(i=0; i<n; i++){
        *A=insertar(v[i], *A);
    }
    t2=microsegundos();
    t=t2-t1;

    if(t<T){
        t=0;
    }
    return t;
}

double tiempoBusqueda(int v[], int n, arbol *A){
    double t1, t2, t;
    int i;

    aleatorio(v, n);
    t1=microsegundos();
    for(i=0; i<n; i++){
        buscar(v[i], *A);
    }
    t2=microsegundos();
    t=t2-t1;

    if(t<T){
        t=0;
    }
    return t;
}