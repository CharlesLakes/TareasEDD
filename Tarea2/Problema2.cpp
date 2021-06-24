#include <iostream>
#include <fstream>

struct tNodo{
    unsigned int E;
    int C;
    tNodo* izq;
    tNodo* der;
};

class tPolinomio{
    private:
        tNodo *Padre;
        unsigned int n;
        unsigned Emax;

    public:
        tPolinomio();
        ~tPolinomio();
        void insert(unsigned int iE, int iC , tNodo *n=NULL);
        float evaluar(float x);
        int coeficiente(unsigned iE);
        void clear();
        
};


tPolinomio::tPolinomio(){
    n = 0;
    Emax = 0;
}
tPolinomio::~tPolinomio(){
    clear();
}

void tPolinomio::insert(unsigned int iE, int iC, tNodo *n= NULL){
    return;
}



// recorrido in-orden de un ABB T
void tPolinomio::evaluar(float x) {
    int resultado = 0;
    int temp = Emax;
    inOrdenInverso (Padre,x,Emin,&resultado,&temp);
}
void inOrdenInverso (tNodo nodo, float x ,int Emin,int* resultado,int* temp) {
    if (nodo == NULL) return;
    inOrdenInverso (nodo->der,x,resultado,temp); // visita hijo derecho en in-orden
    if (nodo.E == *temp) *resultado += nodo.C;
    for (int a = 0; a < temp - nodo.E; a++)
        *resultado *= x;
    *resultado += nodo.C;
    *temp = nodo.E;
    
    inOrdenHelp (nodo->izq,x,resultado,temp); // visita hijo izquierdo en in-orden 
    if(Emin == *temp && temp != 0){
        for(int a = 0; a < Emin; a++)
            *resultado *= x;
    }
}

