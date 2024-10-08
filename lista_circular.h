#ifndef LISTA_CIRCULAR_H_INCLUDED
#define LISTA_CIRCULAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#define SIN_MEMORIA 0
#define MAX_USER 20
#define OPCION_VALIDA(a) ((a) == 'Y' || (a) == 'y' || (a) == 'N' || (a) == 'n')

void crear_listac (t_lista *p);
void vaciar_listac (t_lista *p);
int listac_vacia (t_lista *p);
int ponerSegundo(t_lista *p, void*dato, unsigned tamDato);
int poner_listac_inicio (t_lista *,void*info,unsigned tam);
int poner_listac_final (t_lista *,void*info,unsigned tam);
int map_listac (t_lista *p, void accion (void*,void*),void *param);
void mostrar_numeros(void*info);
int sacar_primero_listac(t_lista* l, void* dato, unsigned tam_buffer);
int solo_un_elemento_listac (t_lista* l);
int intercambia_nodos(t_lista* l,int ant,int nue);

#endif // LISTA_CIRCULAR_H_INCLUDED
