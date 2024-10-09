#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"

void internal_exec() {
    // Estraggo i parametri dalla PCB corrente
    const char* filename = (const char*)running->syscall_args[0];
    const char* func_name = (const char*)running->syscall_args[1];
    void* args = (void*)running->syscall_args[2];

    disastrOS_debug("internal_exec: trying to execute file %s with function %s\n", filename, func_name);
    
    void* handle = dlopen(filename, RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        running->syscall_retvalue = DSOS_ESYSCALL_EXEC_FAILED; // Indica errore
        return;
    }
    
    typedef void (*func_type)(void*, PCB*);
    func_type func = (func_type)dlsym(handle, func_name);
   
    if (!func) {
        fprintf(stderr, "Function %s not found: %s\n", func_name, dlerror());
        dlclose(handle);
        running->syscall_retvalue = DSOS_ESYSCALL_EXEC_FAILED; // Indica errore
        return;
    }
    disastrOS_debug("internal_exec: successfully loaded function '%s' from shared object '%s'\n", func_name, filename);
    running->status=Zombie;

    PCB* new_pcb = PCB_alloc();
    if (!new_pcb) {
        printf("Error: could not allocate PCB for the first process.\n");
        exit(1);
    }

    // Configurao il nuovo contesto
    if (getcontext(&new_pcb->cpu_state) == -1) {
        perror("getcontext failed");
        return;
    }
    // Imposto lo stack usando quello già presente in new_pcb
    new_pcb->cpu_state.uc_stack.ss_sp = new_pcb->stack; 
    new_pcb->cpu_state.uc_stack.ss_size = STACK_SIZE; 
    new_pcb->cpu_state.uc_stack.ss_flags = 0; 
    new_pcb->cpu_state.uc_link = NULL; // imposto uguale a NULL per evitare che torni all'esecuzione del main


    printf("Switching to new context with PID %d\n", new_pcb->pid);
    
    makecontext(&new_pcb->cpu_state, (void(*)(void))func, 1, args);

    new_pcb->status = Running;
    running->status = Suspended;  // Metti in stato sospeso il processo corrente
    running = new_pcb;
    printf("Running process PID: %d\n", running->pid);
    

    setcontext(&running->cpu_state);

    fprintf(stderr, "Error: setcontext should not return!\n");

    dlclose(handle);
}
