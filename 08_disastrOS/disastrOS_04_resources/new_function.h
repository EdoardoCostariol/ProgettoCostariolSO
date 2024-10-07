#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef struct {
    int a;
    int b;
} FunctionArgs;

void myFunction(void* args);