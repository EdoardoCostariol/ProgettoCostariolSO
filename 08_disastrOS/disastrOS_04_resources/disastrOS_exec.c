#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"

void internal_exec() {
    const char* filename = (const char*) running->syscall_args[0];
    const char* func_name = (const char*) running->syscall_args[1];
    void* args = (void*) running->syscall_args[2];

    disastrOS_debug("internal_exec: trying to execute file %s with function %s\n", filename, func_name);

    // Apro lo shared object
    void* handle = dlopen(filename, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "internal_exec: Error loading shared object %s: %s\n", filename, dlerror());
        running->syscall_retvalue = DSOS_ESYSCALL_EXEC_FAILED;
        return;
    }

    dlerror();

    typedef void (*func_type)(void*);
    func_type func = (func_type) dlsym(handle, func_name); //trova la funzione specifica all'interno del file aperto
    
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        fprintf(stderr, "internal_exec: Error finding function %s: %s\n", func_name, dlsym_error);
        dlclose(handle);
        running->syscall_retvalue = DSOS_ESYSCALL_EXEC_FAILED;
        return;
    }

    // chiamo la funzione dallo shared object
    disastrOS_debug("internal_exec: calling function %s from shared object %s\n", func_name, filename);
    (*func)(args);

    dlclose(handle);

    running->syscall_retvalue = 0;
}
