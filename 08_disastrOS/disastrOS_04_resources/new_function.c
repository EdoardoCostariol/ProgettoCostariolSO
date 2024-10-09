#include "new_function.h"
#include <sys/types.h>
#include <sys/time.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h" 
#include "disastrOS_timer.h"
#include "disastrOS_resource.h"
#include "disastrOS_descriptor.h"
#include <poll.h>
#include "disastrOS_globals.h"

void myFunction(void *args) {

    printf("Sto eseguendo il processo con pid: %d\n", disastrOS_getpid());

    //definizione della risorsa
    int resource_id = 1;
    int resource_type = 0; 
    int mode = 0; 

    int fd = disastrOS_openResource(resource_id, resource_type, mode);
    if (fd < 0) {
        printf("Errore nell'apertura della risorsa con ID %d e tipo %d\n", resource_id, resource_type);
        printf("Codice di errore: %d\n", fd);
        return;
    } else {
        printf("Risorsa %d aperta con file descriptor %d\n", resource_id, fd);
    }

    printf("Sleep per 5 secondi...\n");
    disastrOS_sleep(5);

    int close_res = disastrOS_closeResource(fd);
    if (close_res < 0) {
        printf("Errore nella chiusura della risorsa con file descriptor %d\n", fd);
    } else {
        printf("Risorsa con file descriptor %d chiusa con successo\n", fd);
    }

    printf("Processo terminato\n");
}
