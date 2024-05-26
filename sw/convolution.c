#include <stdio.h>

#define SIZEX 10
#define SIZEY 5

// Funcion para realizar la convolucion de dos secuencias
void convolucion(int X[], int Y[], int N, int M, int Z[]) {
    int resultado_longitud = N + M - 1;
    
    // Inicializar el resultado con ceros
    for (int i = 0; i < resultado_longitud; i++) {
        Z[i] = 0;
    }
    
    // Calcular la convolucion
    for (int n = 0; n < resultado_longitud; n++) {
        for (int m = 0; m < M; m++) {
            if (n - m >= 0 && n - m < N) {
                Z[n] += X[n - m] * Y[m];
            }
        }
    }
}

int main() {
    // Definir las secuencias
    int X[SIZEX] = {1, 2, 3, 4, 3, 7, 6, 10, 5, 8};
    int Y[SIZEY] = {3, 3, 5, 6, 7};
    
    // Longitud de las secuencias
    int N = SIZEX;
    int M = SIZEY;
    
    // Longitud de la secuencia resultante de la convolucion
    int resultado_longitud = N + M - 1;
    int resultado[resultado_longitud];
    
    // Calcular la convolucion
    convolucion(X, Y, N, M, resultado);
    
    // Imprimir el resultado
    printf("Resultado de la convolucion:\n");
    for (int i = 0; i < resultado_longitud; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");
    
    return 0;
}
