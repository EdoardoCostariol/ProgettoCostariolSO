CC = gcc
CCOPTS = --std=gnu99 -Wall -fPIC  # Aggiunto -fPIC per le librerie dinamiche
AR = ar
LDFLAGS = -shared  # Flag per creare librerie condivise

HEADERS = disastrOS.h\
	disastrOS_constants.h\
	disastrOS_descriptor.h\
	disastrOS_globals.h\
	disastrOS_pcb.h\
	disastrOS_resource.h\
	disastrOS_syscalls.h\
	disastrOS_timer.h\
	linked_list.h\
	pool_allocator.h\

OBJS = pool_allocator.o\
       linked_list.o\
       disastrOS_timer.o\
       disastrOS_pcb.o\
       disastrOS_resource.o\
       disastrOS_descriptor.o\
       disastrOS.o\
       disastrOS_fork.o\
       disastrOS_wait.o\
       disastrOS_spawn.o\
       disastrOS_exit.o\
       disastrOS_shutdown.o\
       disastrOS_schedule.o\
       disastrOS_preempt.o\
       disastrOS_sleep.o\
       disastrOS_open_resource.o\
       disastrOS_close_resource.o\
       disastrOS_destroy_resource.o\
       disastrOS_exec.o

BINS = disastrOS_test

.phony: clean all

all: libdisastrOS.so libnewfunction.so $(BINS)

# Regola per creare file oggetto (.o) dai file sorgente (.c)
%.o: %.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@ $<

# Regola per creare la libreria dinamica principale (libdisastrOS.so)
libdisastrOS.so: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Regola per creare il binario principale (disastrOS_test)
disastrOS_test: disastrOS_test.c libdisastrOS.so
	$(CC) $(CCOPTS) -o $@ $^ -L. -ldisastrOS

# Regola per creare la libreria condivisa (libnewfunction.so)
libnewfunction.so: new_function.o libdisastrOS.so
	$(CC) $(LDFLAGS) -o $@ $^ -L. -ldisastrOS

# Compilazione di new_function.c in file oggetto (.o)
new_function.o: new_function.c
	$(CC) $(CCOPTS) -c -o $@ $<

# Regola per pulire i file generati
clean:
	rm -rf *.o *~ $(BINS) *.so
