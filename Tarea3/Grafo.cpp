#include "Grafo.hpp"
#define NULL nullptr

/*****
* tGrafo::tGrafo
******
* Crea la lista de adyacencia 
******
* Input:
* typePass n : El numero de elementos de la lista
******
* Returns:
* nada
*****/

tGrafo::tGrafo(int n){
    lista = new Vertice[n];
    size = n;
};


/*****
* tGrafo::~tGrafo
******
* Elimina la memoria asignada
******
******
* Returns:
* nada
*****/

tGrafo::~tGrafo(){
    Vecino* temp;
    for(int i = 0; i < size; i++){
        temp = lista[i].vecinos;
        while(temp != NULL){
            Vecino* aux = temp->vecinos;
            delete temp;
            temp = aux;
        }
    }
    delete[] lista;
}

/*****
* int tGrafo::nVertex
******
* Retorna el size de la lista enlazada, es decir la cantidad de nodos
******
******
* Returns:
* Retorna el size de la lista enlazada
*****/

int tGrafo::nVertex(){
    return size;
};

/*****
* void tGrafo::setEdge
******
* Crea una enlaze entre dos nodos v1 -> v2
******
* Input:
* tVertice v1: Nodo 1
* tVertice v3: Nodo 2
******
* Returns:
*****/


void tGrafo::setEdge (tVertice v1, tVertice v2){
    if(lista[v1].vecinos == NULL){
        lista[v1].vecinos = new Vecino;
        lista[v1].vecinos->id = v2;
        return;
    }
    Vecino* temp = lista[v1].vecinos;
    while(temp->vecinos != NULL)
        temp = temp->vecinos;
    temp->vecinos = new Vecino;
    temp->vecinos->id = v2;
    
};

/*****
* int tGrafo::getMark
******
* Obtiene la marca de un nodo
******
* Input:
* tVertice v: Nodo 
******
* Returns:
* retonarna la marca de el nodo
*****/

int tGrafo::getMark (tVertice v){
    return lista[v].marca;
};

/*****
* void tGrafo::setMark
******
* Le asigna una marca a un nodo
******
* Input:
* tVertice v: Nodo 
* int marca: Le asigna marca a un nodo
******
* Returns:
* retonarna la marca de el nodo
*****/

void tGrafo::setMark (tVertice v, int marca){
    lista[v].marca = marca;
};

/*****
* tVertice tGrafo::first
******
* Obtiene el primer vecino
******
* Input:
* tVertice v: Nodo 
******
* Returns:
* retorna el Nodo
*****/

tVertice tGrafo::first (tVertice v){
    if(lista[v].vecinos == NULL) return size;
    return lista[v].vecinos->id;
}

/*****
* tVertice tGrafo::next
******
* Obtiene el siguiente vecino
******
* Input:
* tVertice v: Nodo 
* tVertice w: Vecindo de el nodo v
******
* Returns:
* retorna el Nodo siguiente a w
*****/

tVertice tGrafo::next (tVertice v, tVertice w){
    Vecino *temp;
    for(temp = lista[v].vecinos; temp != NULL && temp->id != w; temp = temp->vecinos);
    if(temp == NULL || temp->vecinos == NULL)
        return size;
    return temp->vecinos->id;
}