#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "prodcons.h"
#include "semafori.h"

void produzione(int sem_id, buffer *vettore, int *stato, int dim, int chiave, int valore)
{

    printf("[%d] Produttore, chiave %d, accede...\n", getpid(), chiave);

    Wait_Sem(sem_id, SPAZIO_DISP);

    Wait_Sem(sem_id, MUTEX_P);

    int i = 0;
    while (stato[i] != LIBERO)
    {
        i++;
    }

    stato[i] = INUSO;

    printf("[%d] Produttore, chiave %d, buffer %d in uso...\n", getpid(), chiave, i);

    Signal_Sem(sem_id, MUTEX_P);

    sleep(rand() % 3 + 1);

    printf("[%d] Produttore, chiave %d, buffer %d, valore=%d\n", getpid(), chiave, i, valore);
    vettore[i].chiave = chiave;
    vettore[i].valore = valore;

    stato[i] = OCCUPATO;


    if (chiave == 1)
    {
        Signal_Sem(sem_id, MESSAGGIO_DISP_1);
    }
    else if (chiave == 2)
    {
        Signal_Sem(sem_id, MESSAGGIO_DISP_2);
    }
    else if (chiave == 3)
    {
        Signal_Sem(sem_id, MESSAGGIO_DISP_3);
    }
}

int consumazione(int sem_id, buffer *vettore, int *stato, int dim, int chiave)
{

    int valore;

    printf("[%d] Consumatore, chiave %d, accede...\n", getpid(), chiave);

    if (chiave == 1)
    {
        Wait_Sem(sem_id, MESSAGGIO_DISP_1);
    }
    else if (chiave == 2)
    {
        Wait_Sem(sem_id, MESSAGGIO_DISP_2);
    }
    else if (chiave == 3)
    {
        Wait_Sem(sem_id, MESSAGGIO_DISP_3);
    }

    Wait_Sem(sem_id, MUTEX_C);

    int i = 0;
    while (stato[i] != OCCUPATO || vettore[i].chiave != chiave)
    {
        i++;
    }

    stato[i] = INUSO;

    printf("[%d] Consumatore, chiave %d, buffer %d in uso...\n", getpid(), chiave, i);

    Signal_Sem(sem_id, MUTEX_C);

    sleep(rand() % 3 + 1);



    valore = vettore[i].valore;
    printf("[%d] Consumatore, chiave %d, buffer %d, valore=%d\n", getpid(), chiave, i, valore);

    stato[i] = LIBERO;
    Signal_Sem(sem_id, SPAZIO_DISP);

    return valore;
}