#include "Grafo.hpp"
#define NULL nullptr


tGrafo::tGrafo(int n){
    lista = new Vertice[n];
    size = n;
};


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

int tGrafo::nVertex(){
    return size;
};

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

int tGrafo::getMark (tVertice v){
    return lista[v].marca;
};

void tGrafo::setMark (tVertice v, int marca){
    lista[v].marca = marca;
};


tVertice tGrafo::first (tVertice v){
    if(lista[v].vecinos == NULL) return size;
    return lista[v].vecinos->id;
}

tVertice tGrafo::next (tVertice v, tVertice w){
    Vecino *temp;
    for(temp = lista[v].vecinos; temp != NULL && temp->id != w; temp = temp->vecinos);
    if(temp == NULL || temp->vecinos == NULL)
        return size;
    return temp->vecinos->id;
}