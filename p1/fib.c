#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#define K 1000
#define T 500

int fib1(int n);
int fib2(int n);
int fib3(int n);
void test(int n);
double microsegundos();
void midTempFib1();
void midTempFib2();
void midTempFib3();

int main(){
    test(10);
    printf("-------------------------------------------------------------------------\n\n");
    midTempFib1();
    printf("-------------------------------------------------------------------------\n\n");
    midTempFib2();
    printf("-------------------------------------------------------------------------\n\n");
    midTempFib2();
    printf("-------------------------------------------------------------------------\n\n");
    midTempFib3();
}

int fib1(int n){
    if (n<2)return n;
    else return fib1(n-1)+fib1(n-2);
}

int fib2(int n){
    int i=1, j=0;
    for (int k=1; k<=n; k++){
        j=i+j;
        i=j-i;
    }
    return j;
}

int fib3(int n){
    int i=1, j=0, k=0, h=1, t=0;
    while (n>0){
        if(n%2==1){
            
            t=j*h;
            j=i*h+j*k+t;
            i=i*k+t;
        }
        t=h*h;
        h=2*k*h+t;
        k=k*k+t;
        n=n/2;
    }
    return j;
}

void test(int n){
    printf("  n|  f1|  f2|  f3\n");
    for(int i=0; i<=n;i++) printf("%3d| %3d| %3d| %3d\n", i, fib1(i), fib2(i), fib3(i));
}

double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL)<0) return 0.0;
    return (t.tv_usec + t.tv_sec + 1000000.0);    
}


void midTempFib1(){
    int n;
    double t1, t2, t, x, y, z;
    char bucle=' ';
    printf("Fib 1:\n");
    printf("           n           t(n)     t(n)/1.1^n      t(n)/Fi^n       t(n)/2^n\n\n");
    for(n=2; n<=32; n=n*2){
        t1 = microsegundos();
        fib1(n);
        t2 = microsegundos();
        t = t2-t1;
        if(t<T){
            int i;
            t1 = microsegundos();
            for(i=0;  i<=K; i++) fib1(n);
            bucle='*';
            t2 = microsegundos();
            t=(t2-t1)/i;
        }
        x = t / pow(1.1, n);
        y = t / pow((1+sqrt(5))/2, n);
        z = t / pow(2, n);
        printf("%12d%15.3f%15.6f%15.6f%15.6f  %c\n", n, t, x, y, z, bucle);
        bucle=' ';
    }
}

void midTempFib2(){
    int n;
    double t1, t2, t, x, y, z;
    char bucle=' ';
    printf("Fib 2:\n");
    printf("           n           t(n)     t(n)/n^0.8         t(n)/n  t(n)/n*log(n)\n\n");
    for(n=1000; n<=10000000; n=n*10){
        t1 = microsegundos();
        fib2(n);
        t2 = microsegundos();
        t = t2-t1;
        if(t<T){
            int i;
            t1 = microsegundos();
            for(i=0;  i<=K; i++) fib2(n);
            bucle='*';
            t2 = microsegundos();
            t=(t2-t1)/i;
        }
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / n*log(n);
        printf("%12d%15.3f%15.6f%15.6f%15.6f  %c\n", n, t, x, y, z, bucle);
        bucle=' ';
    }
}

void midTempFib3(){
    int n;
    double t1, t2, t, x, y, z;
    char bucle=' ';
    printf("Fib 3:\n");
    printf("           n           t(n) t(n)/rt log(n)    t(n)/log(n)     t(n)/n^0.5\n\n");
    for(n=1000; n<=10000000; n=n*10){
        t1 = microsegundos();
        fib3(n);
        t2 = microsegundos();
        t = t2-t1;
        if(t<T){
            int i;
            t1 = microsegundos();
            for(i=0;  i<=K; i++) fib3(n);
            bucle='*';
            t2 = microsegundos();
            t=(t2-t1)/i;
        }
        x = t / sqrt(log(n));
        y = t / log(n);
        z = t / pow(n, 0.5);
        printf("%12d%15.3f%15.6f%15.6f%15.6f  %c\n", n, t, x, y, z, bucle);
        bucle=' ';
    }
}
