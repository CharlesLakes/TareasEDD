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
    inOrdenHelp (Padre,x,&resultado,Emax);
}
void inOrdenHelp (tNodo nodo, float x , int *resultado,int temp , int i=0) {
    if (nodo == NULL) return;
    inOrdenHelp (nodo->der); // visita hijo derecho en in-orden
    if (nodo.E==temp) resultado+=nodo.C;
    for (int a = 0; a < temp-nodo.E; a++)
    {
        resultado*= x;
    }
    inOrdenHelp (nodo->izq); // visita hijo izquierdo en in-orden 
}

