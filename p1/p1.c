#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>

/**
 * Universidad de A Coruña
 * Algoritmos
 * Alumno 1: Welton Vieira dos Santos - welton.dossantos@udc.es
 * Alumno 2: Angel Lagares Vázquez - angel.lagares@udc.es
 */

/* obtiene la hora actual en microsegundos */
double microsegundos() {
  struct timeval t;
  if (gettimeofday(&t, NULL) < 0 )
    return 0.0;
  return (t.tv_usec + t.tv_sec * 1000000.0);
}

/* algoritmo fibonacci 1 */
int fib1(int n) {
  if (n < 2)
  {
    return n;
  } else {
    return fib1(n-1) + fib1(n-2);
  }
}

/* algoritmo fibonacci 2 */
int fib2(int n) {
  int i, j, k;
  i = 1; j = 0;
  for (k = 1; k < n+1; k++) {
    j = i + j;
    i = j - i;
  }
  return j;
}

/* algoritmo fibonacci 3 */
int fib3(int n) {
  int i, j, k, h, t;
  i = 1; j = 0; k = 0; h = 1; t = 0;
  while ( n > 0 ) {
    if ((n % 2) != 0) {
      t = j * h;
      j = (i * h) + (j * k) + t;
      i = (i * k) + t;
    }
    t = h * h;
    h = (2 * k * h) + t;
    k = (k * k) + t;
    n = n / 2;
  }
  return j;
}

// Validacion algoritmos
void test() {
  int a, b, c, n;
  printf("%8s %13s %12s %12s\n", "n", "f1", "f2", "f3");
  printf("     --------------------------------------------\n");
  for (n = 1; n < 11; n++)
  {
    a = fib1(n);
    b = fib2(n);
    c = fib3(n);
    printf("%8d %12d %12d %12d\n", n, a, b, c);
  }
}

// Compara tiempos de ejecucion del algoritmo fib 1
void medicion_fib1() {
   int n[5] = {2, 4, 8, 16, 32};
   int i;
   printf("Medicion Fibonacci 1:\n");
   printf("%5s %15s\n", "n", "tiempo");
   printf("%5s\n", "------------------------");
   for (i = 0; i < 5; i++) {
      double t1 = microsegundos();
      fib1(n[i]);
      double t2 = microsegundos();
      double t = t2-t1;
      printf("%5d %15.3f\n", n[i], t);      
   }
}

// Compara tiempos de ejecucion del algoritmo fib 2
void medicion_fib2() {
   int n[5] = {1000, 10000, 100000, 1000000, 10000000};
   int i;
   printf("Medicion Fibonacci 2:\n");
   printf("%8s %15s\n", "n", "tiempo");
   printf("%5s\n", "------------------------");
   for (i = 0; i < 5; i++) {
      double t1 = microsegundos();
      fib2(n[i]);
      double t2 = microsegundos();
      double t = t2-t1;
      printf("%8d %15.3f\n", n[i], t);      
   }
}

// Compara tiempos de ejecucion del algoritmo fib 3
void medicion_fib3() {
   int n[5] = {1000, 10000, 100000, 1000000, 10000000};
   int i;
   printf("Medicion Fibonacci 3:\n");
   printf("%8s %15s\n", "n", "tiempo");
   printf("%5s\n", "------------------------");
   for (i = 0; i < 5; i++) {
      double t1 = microsegundos();
      fib3(n[i]);
      double t2 = microsegundos();
      double t = t2-t1;
      printf("%8d %15.3f\n", n[i], t);      
   }
}

// Estudio de las cotas del algoritmo fib 1
void cotas_fib1() {
    int n;
    int i;
    double x, y, z, t1, t2, t;
    printf("Tiempos de ejecución Fibonacci 1:\n");
    printf("%5s", "----------------------------------");
    printf("%s\n", "------------------------------------");
    printf("%9s %12s %17s %14s %12s\n", "n", "t(n)", 
      "f(n)=1,1^n","f(n)=phi^n", "f(n)=2^n");
    printf("%5s", "----------------------------------");
    printf("%s\n", "------------------------------------");    
    for (n = 2; n <= 32; n = n * 2) {
        t1 = microsegundos();
        fib1(n);
        t2 = microsegundos();
        t = t2-t1;

        if (t < 500) {
          t1 = microsegundos();
          for (i = 0; i < 100000; ++i) {
            fib1(n);
          }
          t2 = microsegundos();
          t = (t2-t1)/100000;
          x = t / pow(1.1, n);
          y = t / pow(((1+sqrt(5))/2), n);
          z = t / pow(2, n);
          printf("(*) %5d%15.5f%15.6f%15.6f%15.8f\n", n, t, x, y, z);
        } else {
          x = t / pow(1.1, n);
          y = t / pow(((1+sqrt(5))/2), n);
          z = t / pow(2, n);
          printf("    %5d%15.5f%15.6f%15.6f%15.8f\n", n, t, x, y, z);
        }    
    }
    printf("%5s", "----------------------------------");
    printf("%s\n\n", "------------------------------------");    
}

// Estudio de las cotas del algoritmo fib 2
void cotas_fib2() {
    int n,i;
    double x, y, z, t1, t2, t;
    printf("Tiempos de ejecución Fibonacci 2:\n");
    printf("%5s", "----------------------------------------");
    printf("%s\n", "--------------------------------------");
    printf("%13s %15s %15s %11s %19s\n", "n", "t(n)", 
      "f(n)=n^0.8","f(n)=n", "f(n)=n*log(n)");
    printf("%5s", "----------------------------------------");
    printf("%s\n", "--------------------------------------");
    for (n = 1000; n <= 10000000; n = n * 10) {
        t1 = microsegundos();
        fib2(n);
        t2 = microsegundos();
        t = t2-t1;

        if (t < 500) {
          t1 = microsegundos();
          for (i = 0; i < 1000; ++i) {
            fib2(n);
          }
          t2 = microsegundos();
          t = (t2-t1)/1000;
          x = t / pow(n, 0.8);
          y = t / n;
          z = t / (n * log(n));
          printf("(*) %10d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        } else {
          x = t / pow(n, 0.8);
          y = t / n;
          z = t / (n * log(n));
          printf("    %10d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }    
    }
    printf("%5s", "----------------------------------------");
    printf("%s\n\n", "--------------------------------------");
}

// Estudio de las cotas del algoritmo fib 3
void cotas_fib3() {
    int n,i;
    double x, y, z, t1, t2, t;
    printf("Tiempos de ejecución Fibonacci 3:\n");
    printf("%5s", "--------------------------------------");
    printf("%s\n", "--------------------------------------");
    printf("%13s %14s %19s %13s %11s\n", "n", "t(n)",
     "f(n)=sqrt(log(n))","f(n)=log(n)", "f(n)=n^0.5");
    printf("%5s", "--------------------------------------");
    printf("%s\n", "--------------------------------------");
    for (n = 1000; n <= 10000000; n = n * 10) {
        t1 = microsegundos();
        fib3(n);
        t2 = microsegundos();
        t = t2-t1;

        if (t < 500) {
          t1 = microsegundos();
          for (i = 0; i < 10000; ++i) {
            fib3(n);
          }
          t2 = microsegundos();
          t = (t2-t1)/10000;
          x = t / sqrt(log(n));
          y = t / log(n);
          z = t / pow(n, 0.5);
          printf("(*) %10d%15.4f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        } else {
          x = t / sqrt(log(n));
          y = t / log(n);
          z = t / pow(n, 0.5);
          printf("    %10d%15.4f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
        }    
    }
    printf("%5s", "--------------------------------------");
    printf("%s\n", "--------------------------------------");
}
/**
 * Cuerpo principal 
 */
int main() {
	
	int i;
	test();
	for (i = 0; i < 5; ++i)
    {
        cotas_fib1();
        cotas_fib2();
        cotas_fib3();
      printf("\n");
    }
	return 0;
}
