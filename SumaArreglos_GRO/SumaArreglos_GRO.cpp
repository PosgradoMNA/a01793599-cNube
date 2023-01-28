// SumaArreglos_GRO.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>

#include <chrono>

#define N 50000
#define chunk 150
#define mostrar 15

void imprimeArreglo(float* d);

//Declaring using for timestamps
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main()
{
    std::cout << "Sumando arreglos en paralelo\n";

    float a[N], b[N], c[N];
    int i;

    for ( i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 15) * 10;
    }
    
    int pedazos = chunk;
    int num_threadsForMethod = 5;


    //Setting timer for getting time elapsed result
    auto initTime2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();


    //Setting parallel function, I just addedd the num_threads parameters
    #pragma omp parallel for num_threads( num_threadsForMethod )\
    shared( a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
        if (i % (chunk*4) == 0) { //Printing every Mod==0 in 4 times the chunk
            int tid = omp_get_thread_num();
            printf("Thread number is: %d where i= %d\n", tid, i );
        }
    }

    //Setting timer for getting time elapsed result
    auto endTime2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    printf("\n\nElapsed milliseconds: %d\n\n\n",+ (int)(endTime2 - initTime2));


    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float* d) 
{
    for (int x = 0; x < mostrar; x++) 
    {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}
