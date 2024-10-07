#include "new_function.h"


void myFunction(void *args) {
    FunctionArgs *functionArgs = (FunctionArgs *)args;

    printf("Eseguo myFunction %d e ritorno all'esecuzione del programma dopo la chiamata alla exec \n", disastrOS_getpid());

    int x = functionArgs->a;
    int y = functionArgs->b;
    int sum = x + y;
    printf("La somma di %d e %d è %d\n", x, y, sum);
    printf("TERMINA TUTTO\n");
}

