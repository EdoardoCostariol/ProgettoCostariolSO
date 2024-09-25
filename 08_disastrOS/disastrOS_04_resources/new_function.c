#include "new_function.h"

// Funzione che verrà chiamata con exec
int myFunction(void *args) {
    printf("Eseguo myFunction e ritorno all'esecuzione del programma dopo la chiamata alla exec \n");
    return 0;
}

