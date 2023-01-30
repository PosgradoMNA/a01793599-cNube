// SumaArreglos_GRO.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>

#include <chrono>
#include <cstdlib>


#define N 20000
#define chunk 500
#define mostrar 15

void imprimeArreglos(float* a, float* b, float* c );

//Declaring using for timestamps
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main()
{

    float a[N], b[N], c[N];
    int i;

    for ( i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 11) * 5;
    }
    
    int pedazos = chunk;
    int num_threadsForMethod = 20;

    std::cout << "Sumando arreglos en paralelo con " << num_threadsForMethod << " hilos y "<< chunk <<" pedazos\n" << std::endl;

    //Setting timer for getting time elapsed result
    auto initTime2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();


    //Setting parallel function, I just addedd the num_threads parameters
    #pragma omp parallel for num_threads( num_threadsForMethod )\
    shared( a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
        if (false && i % (chunk * 1) == 0 && i < 20000) { //Printing every Mod==0 in 1 times the chunk
            int tid = omp_get_thread_num();
            printf("Thread number is: %d where i= %d\n", tid, i );
        }
    }

    //Setting timer for getting time elapsed result
    auto endTime2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    printf("\n\nElapsed milliseconds: %d\n\n\n",+ (int)(endTime2 - initTime2));


    imprimeArreglos(a, b, c);


}

void imprimeArreglos(float* a, float* b, float* c )
{
    int random;
    srand((unsigned)time(NULL));
    for (int x = 0; x < mostrar; x++) 
    {
        random = rand() % N;
        std::cout << (x+1) << ". Imprimiendo los valores (a + b = c) en i=" << random << "     ("<<a[random]<<" + " << b[random] << ") = " << c[random] << std::endl;
    }
}
