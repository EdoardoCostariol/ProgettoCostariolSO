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

    printf("Running process PID: %d\n", disastrOS_getpid());

    //definizione della risorsa
    int resource_id = 1;
    int resource_type = 0; 
    int mode = 0; 

    int fd = disastrOS_openResource(resource_id, resource_type, mode);
    if (fd < 0) {
        printf("Error opening resource with ID %d and type %d\n", resource_id, resource_type);
        printf("Error code: %d\n", fd);
        return;
    } else {
        printf("Resource %d opened with file descriptor %d\n", resource_id, fd);
    }

    int close_res = disastrOS_closeResource(fd);
    if (close_res < 0) {
        printf("Error closing resource with file descriptor%d\n", fd);
    } else {
        printf("Resource with file descriptor %d closed successfully\n", fd);
    }

    printf("Process finished\n");
}
