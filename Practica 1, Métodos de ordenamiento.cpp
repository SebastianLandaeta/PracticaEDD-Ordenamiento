/*	Practica 1: Algoritmos de ordenamiento
    Ingeniería Informática
    Estructuras de Datos
    Sección 1
    Alumnos:
        Sebastián Landaeta (CI: 28.240.979)
        Antonietta Palazzo (CI: 28.619.939)
        Valery Medina (CI: 29.643.312)
*/

// == LIBRERÍAS ==
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <iomanip>

// == MACROS ==
#define SIZE 30000 // Tamaño de los arreglos
#define N_ALGORITMOS 6 // Número de algoritmos

#define ORDENADO 0
#define DESORDENADO 1
#define INVERSO 2

using namespace std;

// == CLASES ==
class Utilidad
{
    // == MÉTODOS ==
    public:
        // Mueve el cursor a una coordenada específica
        void gotoxy(int X, int Y)
        {
            HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD dwPos;
            dwPos.X = X;
            dwPos.Y = Y;
            SetConsoleCursorPosition(hcon, dwPos);
        }
        
        // Permite copiar el contenido de un arreglo en otro
        template <typename type>
        void copy_array(type origin[], type destiny[], int size)
        {
            for (int i = 0; i < size; i++)
            {
                destiny[i] = origin[i];
            }
        }
};

// Registro de los tiempos y sus algoritmos asociados
class Tiempo
{
    // == ATRIBUTOS ==
    public:
        string nombre_algoritmo;
        double tiempo[3];
};

// Métodos generales del programa
class Programa
{
    // == ATRIBUTO ==
    private:
        Utilidad utilidad;

    // == MÉTODOS ==
    public:
        // Llena los arreglos de forma ordenada
        void llenar_arreglo(int *arreglo, bool inverso)
        {
            for (int i = 0; i < SIZE; i++)
            {
                inverso == true ? arreglo[i] = SIZE - i : arreglo[i] = i + 1;
            }
        }

        // Usando el algoritmo de Fisher-Yates, desordena un arreglo
        void desordenar_arreglo(int *arreglo)
        {
            srand(time(NULL));

            int r;

            for (int i = SIZE - 1; i > 0; i--)
            {
                r = rand() % (i + 1);

                intercambiar_elementos(arreglo[r], arreglo[i]);
            }
        }

        // Intercambia los valores de dos variables
        template <typename type>
        void intercambiar_elementos(type &p1, type &p2)
        {
            type aux = p1;
            p1 = p2;
            p2 = aux;
        }

        // Muestra los campos de la tabla 1
        void mostrar_campos()
        {
            utilidad.gotoxy(20, 2);
            cout << "Ordenado";
            utilidad.gotoxy(39, 2);
            cout << "Desordenado";
            utilidad.gotoxy(60, 2);
            cout << "Inverso\n";
        }

        // Mide el tiempo de ejecución de un algoritmo
        double medir_tiempo(void (*algoritmo)(int[], int), int arreglo[], int size)
        {
            int aux[SIZE];
            Utilidad utilidad;
            unsigned tiempo_i, tiempo_f;
            
            // Copiar arreglo en auxiliar
            utilidad.copy_array(arreglo, aux, size);

            // Medir tiempo de ejecución
            tiempo_i = clock();
            algoritmo(aux, size);
            tiempo_f = clock();

            // Almacenar el tiempo en una variable
            double tiempo = (double(tiempo_f - tiempo_i) / CLOCKS_PER_SEC);

            return tiempo;
        }

        // Muestra los tiempos de cada algoritmo en la actividad 1
        void mostrar_tiempo_1(int x, int y, double tiempo)
        {
            utilidad.gotoxy(x, y);
            cout << fixed << setprecision(3) << tiempo << " segs";
        }

        // Reordena las posiciones de los nombres
        void reiniciar_nombres(Tiempo time[], string nombres[])
        {
            for (int i = 0; i < N_ALGORITMOS; i++)
            {
                nombres[i] = time[i].nombre_algoritmo;
            }
        }

        // Muestra los tiempos de cada algoritmo en la actividad 2
        void mostrar_tiempo_2(double tiempos[], string nombres[])
        {
            cout << nombres[0] << ": " << fixed << setprecision(3) << tiempos[0] << " segs\n";

            for (int i = 1; i < N_ALGORITMOS; i++)
            {
                cout << nombres[i] << ": " << fixed << setprecision(3) << tiempos[i] << " segs";
                cout << " (+ " << fixed << setprecision(3) << tiempos[i]-tiempos[0] << ")\n";
            }
        }

        // Muestra los tiempos de cada algoritmo en la actividad 3
        void mostrar_tiempo_3(double tiempos[], string nombres[])
        {
            for (int i = 0; i < N_ALGORITMOS; i++)
            {
                cout << nombres[i] << ": " << fixed << setprecision(3) << tiempos[i] << " segs\n";
            }
        }
};

// Contiene todos los algoritmos de ordenamiento
class Ordenamiento
{
    // == MÉTODOS ==
    public:
        // Ordena un arreglo usando el algoritmo de inserción
        static void insertsort(int arreglo[], int size)
        {
            Programa programa;

            for (int i = 1; i < size; i++)
            {
                for (int j = i; (j > 0) && (arreglo[j - 1] > arreglo[j]); j--)
                {
                    programa.intercambiar_elementos(arreglo[j], arreglo[j-1]);
                }
            }
        }
        
        // Ordena un arreglo usando el algoritmo de selección
        static void selectionsort(int arreglo[], int size)
        {
            Programa programa;
            int lowest;

            for (int i = 0; i < size; i++) 
            {
                lowest = i;

                for (int j = i + 1; j < size; j++) 
                {
                    if (arreglo[j] < arreglo[lowest])
                    {
                        lowest = j;
                    }
                }
                
                if (i != lowest)
                {
                    programa.intercambiar_elementos(arreglo[i], arreglo[lowest]);
                }
            }
        }

        // Ordena un arreglo usando el algoritmo burbuja
        static void bubblesort(int arreglo[], int size)
        {
            Programa programa;

            for (int i = 1; i < size; i++)
            {
                for (int j = size-1; j >= i; j--)
                {
                    if (arreglo[j-1] > arreglo[j])
                    {
                        programa.intercambiar_elementos(arreglo[j-1], arreglo[j]);
                    }
                }
            }
        }

        // Ordena un arreglo usando el algoritmo burbuja modificado
        static void modifiedbubblesort(int arreglo[], int size)
        {
            Programa programa;
            bool finalizar = false;
            
            for (unsigned int i = 1; i < size && !finalizar; i++) 
            {
                finalizar = true;

                for (unsigned int j = size-1; j >= i; j--) 
                {
                    if (arreglo[j-1] > arreglo[j]) 
                    {
                        programa.intercambiar_elementos(arreglo[j-1], arreglo[j]);
                        finalizar = false;
                    }
                }
            }
        }

        // Ordena un arreglo usando el algoritmo shell
        static void shellsort(int arreglo[], int size)
        {
            Programa programa;
            int gap;

            for (gap = size/2; gap > 0; gap /= 2)
            {
                for (int i = gap; i < size; i++)
                {
                    for (int j = i-gap; j >= 0 && arreglo[j+gap] < arreglo[j]; j -= gap)
                    {
                        programa.intercambiar_elementos(arreglo[j], arreglo[j+gap]);
                    }
                }
            }
        }
   
        // Compara dos elementos (necesario para quicksort)
        static int cmpfunc(const void *a, const void *b)
        {
	        return (*(int*)a - *(int*)b);
        }

        // Ordena un arreglo usando el algoritmo quicksort
        static void quicksort(int arreglo[], int size)
        {
            qsort(arreglo, size, sizeof(int), cmpfunc);
        }

        // Ordena los tiempos de ejecución usando shell
        static void stimes(double tiempos[], string nombres[])
        {
            Programa programa;

            for (int i = 1; i < N_ALGORITMOS; i++)
            {
                for (int j =  N_ALGORITMOS-1; j >= i; j--)
                {
                    if (tiempos[j-1] > tiempos[j])
                    {
                        programa.intercambiar_elementos(tiempos[j-1], tiempos[j]);
                        programa.intercambiar_elementos(nombres[j-1], nombres[j]);
                    }
                }
            }
        }
};

// == MAIN ==
int main()
{
    setlocale(LC_CTYPE, "Spanish");
    
    int ordenado[SIZE], desordenado[SIZE], inverso[SIZE];
    Programa programa;
    Utilidad utilidad;
    Ordenamiento ordenamiento;
    Tiempo time[N_ALGORITMOS];

    // Asignar los nombres de los algoritmos
    time[0].nombre_algoritmo = "Inserción";
    time[1].nombre_algoritmo = "Selección";
    time[2].nombre_algoritmo = "Burbuja";
    time[3].nombre_algoritmo = "Burbuja modificado";
    time[4].nombre_algoritmo = "Shell";
    time[5].nombre_algoritmo = "Quicksort";

    // Llenar arreglos
    programa.llenar_arreglo(ordenado, false);
    programa.llenar_arreglo(desordenado, false);
    programa.llenar_arreglo(inverso, true);
    
    // Desordenar arreglo
    programa.desordenar_arreglo(desordenado);

    // Crear arreglo de punteros a métodos
    void (*algoritmos[N_ALGORITMOS]) (int arreglo[], int size) = 
    {
        Ordenamiento::insertsort,
        Ordenamiento::selectionsort,
        Ordenamiento::bubblesort,
        Ordenamiento::modifiedbubblesort,
        Ordenamiento::shellsort,
        Ordenamiento::quicksort
    };

    // Actividad 1
    cout << "Actividad 1\n\n";
    programa.mostrar_campos();

    // Medir y mostrar los tiempos de cada algoritmo
    for (int i = 0; i < N_ALGORITMOS; i++)
    {
        cout << time[i].nombre_algoritmo;

        time[i].tiempo[ORDENADO] = programa.medir_tiempo(algoritmos[i], ordenado, SIZE);
        programa.mostrar_tiempo_1(20, i+3, time[i].tiempo[ORDENADO]);

        time[i].tiempo[DESORDENADO]= programa.medir_tiempo(algoritmos[i], desordenado, SIZE);
        programa.mostrar_tiempo_1(39, i+3, time[i].tiempo[DESORDENADO]);

        time[i].tiempo[INVERSO] = programa.medir_tiempo(algoritmos[i], inverso, SIZE);
        programa.mostrar_tiempo_1(60, i+3, time[i].tiempo[INVERSO]);

        cout << endl;
    }

    system("pause");
    system("cls");

    // Actividad 2
    cout << "Actividad 2\n\n";

    // Almacenar los tiempos y los nombres individualmente
    double t_ordenado[N_ALGORITMOS], t_desordenado[N_ALGORITMOS], t_inverso[N_ALGORITMOS];
    string nombres[N_ALGORITMOS];

    // Llenar los arreglos
    for (int i = 0; i < N_ALGORITMOS; i++)
    {
        nombres[i] = time[i].nombre_algoritmo;
        t_ordenado[i] = time[i].tiempo[ORDENADO];
        t_desordenado[i] = time[i].tiempo[DESORDENADO];
        t_inverso[i] = time[i].tiempo[INVERSO];
    }

    // Ordenar y mostrar los tiempos con el arreglo ordenado
    cout << "Arreglo ordenado\n";
    ordenamiento.stimes(t_ordenado, nombres);
    programa.mostrar_tiempo_2(t_ordenado, nombres);
    programa.reiniciar_nombres(time, nombres);

    // Ordenar y mostrar los tiempos con el arreglo desordenado
    cout << "\nArreglo desordenado\n";
    ordenamiento.stimes(t_desordenado, nombres);
    programa.mostrar_tiempo_2(t_desordenado, nombres);
    programa.reiniciar_nombres(time, nombres);

    // Ordenar y mostrar los tiempos con el arreglo inverso
    cout << "\nArreglo inverso\n";
    ordenamiento.stimes(t_inverso, nombres);
    programa.mostrar_tiempo_2(t_inverso, nombres);
    programa.reiniciar_nombres(time, nombres);

    system("pause");
    system("cls");

    // Actividad 3
    cout << "Actividad 3\n\n";

    // Medir tiempos
    for (int i = 0; i < N_ALGORITMOS; i++)
    {
        time[i].tiempo[DESORDENADO] = programa.medir_tiempo(algoritmos[i], desordenado, 3000);
        t_desordenado[i] = time[i].tiempo[DESORDENADO];
    }
    
    // Ordenar y mostrar tiempos
    ordenamiento.stimes(t_desordenado, nombres);
    programa.mostrar_tiempo_3(t_desordenado, nombres);

    system("pause");

    return 0;
}