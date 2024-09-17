CC = gcc
CCOPTS = --std=gnu99 -Wall -fPIC  # Aggiunto -fPIC per compilare codice indipendente dalla posizione (necessario per le librerie dinamiche)
AR = ar
LDFLAGS = -shared  # Flag per creare una libreria condivisa

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

LIBS = libdisastrOS.a  # Libreria statica
SHARED_LIBS = libnewfunction.so  # Libreria dinamica

BINS = disastrOS_test

.phony: clean all

all: $(LIBS) $(SHARED_LIBS) $(BINS)

# Regola per creare file oggetto (.o) dai file sorgente (.c)
%.o: %.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@ $<

# Regola per creare la libreria statica (.a)
libdisastrOS.a: $(OBJS) $(HEADERS)
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

# Regola per creare il binario principale (disastrOS_test)
disastrOS_test: disastrOS_test.c $(LIBS) $(SHARED_LIBS)
	$(CC) $(CCOPTS) -o $@ $^

# Regola per creare la libreria condivisa (.so)
libnewfunction.so: new_function.o  # Puoi aggiungere altri file oggetto se necessario
	$(CC) $(LDFLAGS) -o $@ $^

# Compilazione di new_function.c in file oggetto (.o)
new_function.o: new_function.c
	$(CC) $(CCOPTS) -c -o $@ $<

# Regola per pulire i file generati
clean:
	rm -rf *.o *~ $(LIBS) $(BINS) $(SHARED_LIBS)
