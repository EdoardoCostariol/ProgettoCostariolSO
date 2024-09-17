#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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

    disastrOS_debug("internal_exec: successfully loaded function '%s' from shared object '%s'\n", func_name, filename);

    printf("Processo %d: eseguo exec per avviare la funzione '%s' dal file '%s'\n", disastrOS_getpid(), func_name, filename);

    //modifico il contesto per eseguire la nuova funzione
    getcontext(&running->cpu_state);
    running->cpu_state.uc_stack.ss_sp=running->stack;
    running->cpu_state.uc_stack.ss_size=STACK_SIZE;
    running->cpu_state.uc_stack.ss_flags=0;
    sigemptyset(&running->cpu_state.uc_sigmask);
    makecontext(&running->cpu_state,(void(*)(void))func,1,args);
    
    running->syscall_retvalue = 0;

    printf("Processo %d: exec completato, ora eseguo la nuova funzione '%s'.\n", disastrOS_getpid(), func_name);
}
