#include <stdio.h>

/* Declaración constantes */
#define AFORO 60                   // Número de asientos en el avión
#define ASIENTOS_FILA 6            // Número de asientos por fila
#define FILAS AFORO / ASIENTOS_FILA

/* Declaración tipos */
typedef struct {
    int fila;
    int asiento;
    char pasajero[30];
} TarjetaEmbarque;

typedef int TipoInfoFilas[ASIENTOS_FILA];

/* Prototipos de funciones */
void imprimirTarjeta(TarjetaEmbarque tarjeta);
void buscarPlazas(int *asientosTotal, TipoInfoFilas asientosLibresFilas, int pax, TarjetaEmbarque tarjetas[]);
void mostrarCabina(const TipoInfoFilas situacion);

/* Subprogramas */
void imprimirTarjeta(TarjetaEmbarque tarjeta) {
    printf(".----------------------------.\n");
    printf("|     TARJETA DE EMBARQUE    |\n");
    printf("|   Pasajero: %-20s          |\n", tarjeta.pasajero); // Se imprime el nombre del pasajero
    printf("|   Fila: %3d  Asiento: %3d  |\n", tarjeta.fila, tarjeta.asiento);
    printf("'----------------------------'\n\n");
}

void buscarPlazas(int *asientosTotal, TipoInfoFilas asientosLibresFilas, int pax, TarjetaEmbarque tarjetas[]) {
    int paxSinAsiento = pax;

    for (int k = 0; k < FILAS && paxSinAsiento > 0; k++) {
        int dispo = asientosLibresFilas[k];
        
        if (paxSinAsiento <= dispo) {
            int primerAsiento = ASIENTOS_FILA - dispo;
            for (int M = 1; M <= paxSinAsiento; M++) {
                TarjetaEmbarque tarjeta;
                tarjeta.fila = k + 1;
                tarjeta.asiento = primerAsiento + M;
                printf("Ingrese el nombre del pasajero: ");
                scanf("%s", tarjeta.pasajero);
                tarjetas[*asientosTotal - paxSinAsiento] = tarjeta;
                imprimirTarjeta(tarjeta);
            }
            asientosLibresFilas[k] = dispo - paxSinAsiento;
            *asientosTotal -= paxSinAsiento;
            paxSinAsiento = 0;
        } else {
            int utilizados = dispo;
            int primerAsiento = ASIENTOS_FILA - dispo;

            for (int M = 1; M <= utilizados; M++) {
                TarjetaEmbarque tarjeta;
                tarjeta.fila = k + 1;
                tarjeta.asiento = primerAsiento + M;
                printf("Ingrese el nombre del pasajero: ");
                scanf("%s", tarjeta.pasajero);
                tarjetas[*asientosTotal - paxSinAsiento + (utilizados - dispo)] = tarjeta;
                imprimirTarjeta(tarjeta);
            }

            asientosLibresFilas[k] = 0;
            *asientosTotal -= utilizados;
            paxSinAsiento -= utilizados;
        }
    }

    if (paxSinAsiento > 0) {
        printf("No quedan asientos libres suficientes.\n");
    }
}

void mostrarCabina(const TipoInfoFilas situacion) {
    int pasillo = ASIENTOS_FILA / 2;

    for (int k = 0; k < FILAS; k++) {
        for (int A = ASIENTOS_FILA; A >= 1; A--) {
            if (A == pasillo) {
                printf("   ");
            }
            if (A > situacion[k]) {
                printf(" (*) ");
            } else {
                printf(" ( ) ");
            }
        }
        printf("\n");
    }
}

/* Programa principal */
int main() {
    TipoInfoFilas asientosLibresEnFila;
    TarjetaEmbarque tarjetas[AFORO];
    char tecla;
    int plazasAAsignar;
    int asientosLibresTotal = AFORO;

    for (int k = 0; k < FILAS; k ++) {
        asientosLibresEnFila[k] = ASIENTOS_FILA;
    }

    do {
        do {
            printf("                               \n");
            printf(" <· <· <·   M E N Ú   ·> ·> ·> \n");
            printf("                               \n");
            printf(" Seleccione una opción:        \n");
            printf("  (A) Asignar Asientos         \n");
            printf("  (M) Mostrar Cabina           \n");
            printf("  (F) Finalizar                \n");
            printf("                               \n");
            printf(" <· <· <· <· <· ·> ·> ·> ·> ·> \n");
            printf("                               \n");
            scanf(" %c", &tecla);
        } while (tecla != 'A' && tecla != 'M' && tecla != 'F');

        switch (tecla) {
            case ('A'):
                do {
                    printf("¿Número de plazas (de 1 a 6)?\n");
                    scanf("%d", &plazasAAsignar);
                } while (plazasAAsignar < 0 || plazasAAsignar > 6);

                buscarPlazas(&asientosLibresTotal, asientosLibresEnFila, plazasAAsignar, tarjetas);
                break;

            case ('M'):
                mostrarCabina(asientosLibresEnFila);
                break;

            default:
                break;
        }
    } while (tecla != 'F');
    printf("Gracias por volar con Dingo Airlines ;)\n");

    return 0;
}

