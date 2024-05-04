#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FILAS 20
#define COLUMNAS 6

// Estructura para representar un asiento
typedef struct {
    int fila;
    int columna;
    bool ocupado;
    char pasajero[20];
} Asiento;

// Función para inicializar la matriz de asientos
void inicializarAsientos(Asiento asientos[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            asientos[i][j].fila = i + 1;
            asientos[i][j].columna = j + 1;
            asientos[i][j].ocupado = false;
            strcpy(asientos[i][j].pasajero, "");
        }
    }
}

// Función para imprimir la disposición de los asientos
void imprimirAsientos(Asiento asientos[FILAS][COLUMNAS]) {
    printf("  ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf("%3d ", j + 1);
    }
    printf("\n");
    for (int i = 0; i < FILAS; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < COLUMNAS; j++) {
            if (asientos[i][j].ocupado)
                printf("[X] ");
            else
                printf("[ ] ");
        }
        printf("\n");
    }
}

// Función para asignar asientos a un grupo de pasajeros
void asignarAsientos(Asiento asientos[FILAS][COLUMNAS], int cantidadPasajeros) {
    int pasajerosAsignados = 0;

    for (int i = 0; i < FILAS && pasajerosAsignados < cantidadPasajeros; i++) {
        for (int j = 0; j < COLUMNAS && pasajerosAsignados < cantidadPasajeros; j++) {
            if (!asientos[i][j].ocupado) {
                asientos[i][j].ocupado = true;
                printf("Asignando asiento %d-%d a pasajero %d\n", i + 1, j + 1, pasajerosAsignados + 1);
                printf("Ingrese el nombre del pasajero: ");
                scanf("%s", asientos[i][j].pasajero);
                pasajerosAsignados++;
            }
        }
    }

    if (pasajerosAsignados < cantidadPasajeros) {
        printf("Lo sentimos, no hay suficientes asientos disponibles para todos los pasajeros.\n");
    }
}

int main() {
    Asiento asientos[FILAS][COLUMNAS];
    int cantidadPasajeros;

    inicializarAsientos(asientos);
    imprimirAsientos(asientos);

    printf("Ingrese el número de pasajeros (máximo 6): ");
    scanf("%d", &cantidadPasajeros);

    if (cantidadPasajeros < 1 || cantidadPasajeros > 6) {
        printf("Número de pasajeros no válido.\n");
        return 1;
    }

    asignarAsientos(asientos, cantidadPasajeros);
    imprimirAsientos(asientos);

    return 0;
}
