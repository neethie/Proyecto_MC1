// ———— INCLUDES
#include <iostream>

// ———— NAMESPACE
using namespace std;

// ———— CONSTANTES
const short SPACES = 5;             // — Números de 5 dígitos (incluyendo 0)
const int MAX_DIGITS = 10;          // — Dígitos (0-9)
const int DEBUG_MODE = 1;           // — Modo debug [0: Desactivado, 1: Resumenes, 2: Detallado]
// ———— CONTADORES
// —— Inciso a
int counterDigitsRepeated = 0;
int counterDigitsNotRepeated = 0;
// —— Inciso b
int counterByDigits[10];            // - Contador total
int counterByTimesRepeated[10][5];  // - 10 dígitos * 5 veces máximo que se repite
// —— Inciso c
// ———— FUNCIONES
// —— Crear número
int* CreateNumber(int number) {
    int* tempNumber = (int*) malloc(SPACES * sizeof (int));
    if (tempNumber == NULL) {
        if (DEBUG_MODE)
            fprintf(stderr, "Error: No se pudo asignar memoria\n");
        return NULL;
    }
    int tmp = number;           
    for (int i = SPACES-1; i >= 0; i--) {
        tempNumber[i] = 0;
        (tmp % 10) ? tempNumber[i] = tmp % 10 : tempNumber[i] = 0;
        tmp /= 10;
    }
    return tempNumber;
}
// Contar números con dígitos repetidos o no
int CountRepeated(int number[]) {
    int counter = 0;
    for (int x = 0; x < SPACES; x++) {
        int tmpNumber[SPACES];
        // Copiar número
        for (int i = 0; i < SPACES; i++) 
            tmpNumber[i] = number[i];
        // Sustituir el número a buscar
        tmpNumber[x] = -1;
        for (int j = 0; j < SPACES; j++) {
            if (tmpNumber[j] == number[x]) {
                // Número repetido
                counter++;
            }
        }
    }
    if (counter)
        counterDigitsRepeated++;
    else
        counterDigitsNotRepeated++;
    return 1;
}

// Contar números por dígitos repetidos
int CountByDigits(int number[]) {
    if (DEBUG_MODE == 2)
        printf("Número: %d%d%d%d%d\n", number[0], number[1], number[2], number[3], number[4]);
    int tmpCounterByDigits[10];
    // Bucle para cada dígito 0-9
    for (int x = 0; x < MAX_DIGITS; x++) {
        tmpCounterByDigits[x] = 0;        
        for (int i = 0; i < SPACES; i++) {
            if (number[i] == x) {
                tmpCounterByDigits[x]++;
            }
        }
        // "Resumen"
        if (tmpCounterByDigits[x] > 1) {            
            counterByDigits[x]++;
            counterByTimesRepeated[x][ tmpCounterByDigits[x]-1 ]++;

        if (DEBUG_MODE == 2)
            printf("Dígito %d: %d veces en este número, números con el dígito repetido más de una vez: %d, dígito repetido %d veces: %d\n", 
                x, 
                tmpCounterByDigits[x], 
                counterByDigits[x], 
                tmpCounterByDigits[x], 
                counterByTimesRepeated[x][ tmpCounterByDigits[x]-1 ]);
        }
        
    }
    
    return 1;
}
// ———— MAIN
int main(int argc, char const *argv[])
{
    for (int i = 0; i < 100000; i++) {
        int* number = CreateNumber(i);
        if (number == NULL) {
            return 1;
        }
        CountRepeated(number);
        CountByDigits(number);
    }


    printf("a.\n");
    printf("Números con dígitos repetidos: %d\n", counterDigitsRepeated);
    printf("Números sin dígitos repetidos: %d\n", counterDigitsNotRepeated);
    printf("b.\n");
    for (int x = 0; x < MAX_DIGITS; x++) {
        printf("Dígito %d: Números con el dígito repetido más de una vez: %d\n", x, counterByDigits[x]);
    }
    printf("c.\n");
    for (int x = 0; x < MAX_DIGITS; x++) {
        printf("Existen");
        for (int i = 1; i < SPACES; i++) { // Bucle cuantas veces se repite (1 - 4) + 1 = [2, 5]
            printf(" %d número(s) con %d '%d',", counterByTimesRepeated[x][i], i+1, x);
        }
        printf("\n");
    }
    return 0;
}