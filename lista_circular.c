#include "lista_circular.h"
#include "playlist.h"

void crear_listac (t_lista *p)
{
    *p = NULL;
}


int ponerSegundo(t_lista *p, void*dato, unsigned tamDato)
{
    // Asignacion de Memoria
    t_nodo* nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(nue == NULL)
        return 0;

    nue->info = malloc(tamDato);
    if(nue->info == NULL)
    {
        free(nue);
        return 0;
    }

    if(*p == NULL)
    {
        *p = nue;
        nue->sig = *p;
    }
    // El nuevo apuntara al siguiente de nuestra lista y el siguiente de la lista, al nuevo.
    else
    {
        nue->sig = (*p)->sig;
        (*p)->sig = nue;
    }
    memcpy(nue->info, dato, tamDato);
    nue->tam_info = tamDato;

    return 1;
}

int poner_listac_inicio (t_lista *p,void*info,unsigned tam)
{
    t_nodo *pri = *p;
    t_nodo *aux = *p;
    t_nodo *nue = malloc (sizeof(t_nodo));

    if (!nue)
    {
        return SIN_MEMORIA;
    }
    nue->info = malloc (tam);
    if(!nue->info)
    {
        free (nue);
        return SIN_MEMORIA;
    }

    memcpy(nue->info,info,tam);
    nue->tam_info=tam;

    if(*p == NULL)
    {
        nue->sig = nue;
    }
    else
    {
        while (aux->sig != pri)
        {
            aux = aux->sig;
        }
        aux->sig = nue;
        nue->sig = pri;
    }

    *p = nue;

    return 1;
}
int poner_listac_final (t_lista *p,void*info,unsigned tam)
{

    t_nodo *pri = *p;
    t_nodo *nue = malloc (sizeof(t_nodo));

    if (!nue)
    {
        return SIN_MEMORIA;
    }
    nue->info = malloc (tam);
    if(!nue->info)
    {
        free (nue);
        return SIN_MEMORIA;
    }

    memcpy(nue->info,info,tam);
    nue->tam_info=tam;

    if(*p == NULL)
    {
        nue->sig = nue;
        *p=nue;
    }
    else
    {
        while ((*p)->sig != pri)
        {
            p = &(*p)->sig;
        }

        (*p)->sig = nue;
        nue->sig = pri;

    }

    return 1;
}

int map_listac(t_lista *p, void accion(void*, void*), void *param)
{

    if (*p == NULL) return 0;

    t_nodo *aux = *p;

    if ((*p)->sig == *p)
    {
        accion((*p)->info, param);
        return 1;
    }


    accion((*p)->info, param);
    p = &(*p)->sig;


    while (*p != aux)
    {
        accion((*p)->info, param);
        p = &(*p)->sig;
    }

    return 1;
}

void mostrar_numeros(void*info)
{
    int *num = (int*)info;
    printf ("%d",*num);
}

void vaciar_listac(t_lista *p)
{
    if (!*p)
    {
        return; // Si la lista esta vacia, no hacemos nada
    }

    t_nodo *pri = *p;  // Guardamos el puntero al primer nodo
    t_nodo *sig = (*p)->sig;  // Iniciamos con el siguiente nodo del primero

    // Si hay ma3s de un nodo en la lista, entramos en el ciclo
    while (sig != pri)
    {
        t_nodo *aux = sig->sig; // Guardamos el siguiente nodo
        free(sig->info);        // Liberamos la informacion del nodo actual
        free(sig);              // Liberamos el nodo actual
        sig = aux;             // Avanzamos al siguiente nodo
    }

    // Liberamos el nodo que apuntaba a si mismo (el primer nodo que queda por liberar)
    free(pri->info);
    free(pri);

    *p = NULL;  // Marcamos la lista como vacia
}

int listac_vacia (t_lista *p)
{
    return *p == NULL;
}


int sacar_primero_listac(t_lista* l, void* dato, unsigned tam_buffer)
{
    t_lista* origial = l;
    t_nodo* aux;
    if(!*l)
        return 0;

    aux = *l;
    memcpy(dato, aux->info, minimo(tam_buffer, aux->tam_info));


    if(aux->sig == aux)
        *l = NULL;
    else
    {
        while((*l)->sig != aux)
            l = &(*l)->sig;
        (*l)->sig = aux->sig;
        *origial = aux->sig;
    }

    free(aux->info);
    free(aux);

    return 1;
}

int solo_un_elemento_listac (t_lista* p)
{

    return (*p)->sig == *p;
}

int intercambia_nodos(t_lista* l, int ant, int nue)
{
    int i;
    t_nodo *temp, *select, *aux, *ultimo, *ant_temp = NULL, *ant_select = NULL;

    if (ant == nue || *l == NULL) return 0;

    select = temp = ultimo = aux = *l;

    if(ant > nue)
    {
        i = ant;
        ant = nue;
        nue = i;
    }

    i = 0;
    while (aux->sig != *l)
    {
        if(i < ant)
        {
            ant_select = aux;
            select = aux->sig;
        }

        if(i < nue)
        {
            ant_temp = aux;
            temp = aux->sig;
        }

        aux = aux->sig;
        i++;
    }


    if(ant == 0)
    {
        while (ultimo->sig != *l)
        {
            ultimo = ultimo->sig;
        }

        ant_select = ultimo;
        *l = temp;
    }

    ant_select->sig = temp;


    if(nue == 0)
    {
        while (ultimo->sig != *l)
        {
            ultimo = ultimo->sig;
        }
        ant_temp = ultimo;
        *l = select;
    }
    ant_temp->sig = select;

    /// intercambio final
    aux = select->sig;
    select->sig = temp->sig;
    temp->sig = aux;

    return 1;
}
