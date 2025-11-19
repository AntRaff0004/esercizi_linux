#ifndef _PRODCONS_H_
#define _PRODCONS_H_

typedef struct {
    int chiave;
    int valore;
} buffer;

void produzione(int sem_id, buffer * vettore, int *stato, int dim, int chiave, int valore);
int consumazione(int sem_id, buffer * vettore, int *stato, int dim, int chiave);

#define SPAZIO_DISP 0
#define MESSAGGIO_DISP_1 1
#define MESSAGGIO_DISP_2 2
#define MESSAGGIO_DISP_3 3
#define MUTEX_P 4
#define MUTEX_C 5



#define LIBERO 0
#define INUSO 1
#define OCCUPATO 2

#endif