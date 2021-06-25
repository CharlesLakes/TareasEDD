#include <iostream>
#include <fstream>

using namespace std;

struct tNodo{
    unsigned int E;
    int C;
    tNodo* izq;
    tNodo* der;
};

/*****
* class tPolinomio
******
* Clase polinomio
******
* Input: 
* Sin entradas
******
* Returns:
* No tiene un retorno
*****/

class tPolinomio{
    private:
        tNodo *Padre;
        unsigned int n;
    public:
        tPolinomio();
        ~tPolinomio();
        float evaluar(float x);
        void insert(unsigned int iE, int iC);
        int coeficiente(unsigned iE);
        void clear();
        
};

/*****
* tPolinomio::tPolinomio
******
* Se define el constructor de la clase
******
* Input: 
* Sin entradas
******
* Returns:
* No tiene un retorno
*****/

tPolinomio::tPolinomio(){
    n = 0;
}

/*****
* tPolinomio::~tPolinomio
******
* Limpia o reinicializa la lista
******
* Input: 
* Sin entradas
******
* Returns:
* No tiene un retorno
*****/

tPolinomio::~tPolinomio(){
    clear();
}


/*****
* void coefHelp()
******
* Funcion recursiva que a partir de un nodo padre busca el coeficiente de un exponente determinado, el cual es devuelto a partir del puntero i
******
* Input:
* tNodo* temp: puntero a nodo
* unsigned int iE: entrada del exponente
* int *i: puntero a la respuesta
* .......
******
* Returns:
* void, sin retorno
*****/

void coefHelp(tNodo* temp,unsigned int iE,int *i){
    if(temp == NULL) return;
    coefHelp(temp->izq,iE,i);
    coefHelp(temp->der,iE,i);
    if(iE == temp->E){
        *i = temp->C;
    };
};

/*****
* int tPolinomio::coeficiente()
******
* Obtiene el coeficiente del monomio
******
* Input:
* unsigned int iE: entrada del exponente
* .......
******
* Returns:
* int i, que contiene la respuesta (coeficiente)
*****/

int tPolinomio::coeficiente(unsigned int iE){
    int i;
    coefHelp(Padre,iE,&i);
    return i;
};

/*****
* void clearHelp()
******
* funcion recursiva, la cual reinicializa el arbol
******
* Input:
* tNodo* temp: puntero a nodo
* .......
******
* Returns:
* void, sin retorno
*****/

void clearHelp(tNodo* temp){
    if(temp == NULL) return;
    clearHelp(temp->izq);
    clearHelp(temp->der);
    delete temp;
};

/*****
* void tPolinomio::clear()
******
* reinicializa desde el nodo Padre
******
* Input:
* Sin parámetros
* .......
******
* Returns:
* void, sin retorno
*****/

void tPolinomio::clear(){
    clearHelp(Padre);
};

/*****
* void insertHelp
******
* funcion recursiva que inserta un valor al nodo
******
* Input:
* tNodo* nuevo: nuevo puntero
* tNodo* temp: puntero a nodo
* .......
******
* Returns:
* void, sin retorno
*****/

void insertHelp(tNodo* nuevo, tNodo* temp){
    if(temp->E > nuevo->E){
        if(temp->izq == NULL){
            temp->izq = nuevo;
            return;
        };
        insertHelp(nuevo,temp->izq);
    }else{
        if(temp->der == NULL){
            temp->der = nuevo;
            return;
        };
        insertHelp(nuevo,temp->der);
    };
};

/*****
* void tPolinomio::insert()
******
* inserta un valor al nodo
******
* Input:
* unsigned int iE: entrada del exponente
* int iC: entrada del coeficiente
* .......
******
* Returns:
* void, sin retorno
*****/

void tPolinomio::insert(unsigned int iE, int iC){
    tNodo *nuevo = new tNodo;
    nuevo->E = iE;
    nuevo->C = iC;
    if(Padre == NULL) {
        Padre = nuevo;
        return;
    }
    insertHelp(nuevo,Padre);

}


/*****
* void inOrdenInverso
******
* funcion recursiva que recorre el arbol en in-orden
******
* Input:
* tNodo* nodo: nodo temporal
* float x: x evaluado 
* unsigned int Emin: exponente minimo
* float* resultado: direccion de memoria en que se guarda el resultado
* unsigned int* temp: guarda el E temporal de los nodos
* .......
******
* Returns:
* void, sin retorno
*****/

void inOrdenInverso(tNodo* nodo, float x ,unsigned int Emin,float* resultado,unsigned int* temp) {
    if (nodo == NULL) return;
    inOrdenInverso (nodo->der,x,Emin,resultado,temp); // visita hijo derecho en in-orden
    if (nodo->E == *temp) {
        *resultado += nodo->C;
    }else{
        for (unsigned int a = 0; a < *temp - nodo->E; a++)
            *resultado *= x;
        *resultado += nodo->C;
    }
    *temp = nodo->E;
    inOrdenInverso (nodo->izq,x,Emin,resultado,temp); // visita hijo izquierdo en in-orden 
    if(Emin == *temp && temp != 0){
        for(unsigned int a = 0; a < Emin; a++)
            *resultado *= x;
    }
}

/*****
* float tPolinomio::evaluar()
******
* Evalua segun x en el polinomio
******
* float x: numero por el cual se reemplaza la x
* .......
******
* Returns:
* TipoRetorno, Descripción retorno
*****/

float tPolinomio::evaluar(float x) {
    if(Padre == NULL) return 0;

    unsigned int Emax,Emin;
    tNodo *T = Padre;
    while(T->izq != NULL) T = T->izq;
    Emin = T->E;

    T = Padre;
    while(T->der != NULL) T = T->der;
    Emax = T->E;


    float resultado = 0;
    inOrdenInverso (Padre,x,Emin,&resultado,&Emax);
    return resultado;
}


/*****
* tPolinomio* ObtenerPolinomios()
******
* Interpreta y lee los datos de el archivo .txt y los guarda en una lista
******
* Input:
* string name_file: nombre del archivo de texto
* int& pos : Posición de el cursor al leer
* int& length : Variable por referencia que guardara el largo 
* .......
******
* Returns:
* listapolinomios, lista de tipo tPolinomio que contiene los polinomios
*****/


tPolinomio* ObtenerPolinomios(string name_file ,int& pos,int& length){

    int largo;
    fstream fp;
    fp.open(name_file,ios::in);

    if(!fp.is_open()){
        cerr << "No se logro abrir el archivo" << name_file << endl;
        return NULL;
    }

    fp>>largo;
    tPolinomio* listapolinomios = new tPolinomio[largo];
    for(int i = 0; i < largo;i++){
        int largo_poli;
        fp >> largo_poli;
        for(int a=0; a<largo_poli;a++){
            unsigned int e;
            int c;
            fp >> e;
            fp >> c;
            listapolinomios[i].insert(e,c);
        }
    }
    
    length = largo;
    pos = fp.tellg();

    fp.close();
    return listapolinomios;
}

/*****
* void InterpretarOperaciones()
******
* Lee el archivo con los polinomios, busca el desado,
* evalua, obtiene el coficiente y finalmente lo escribe en otro archivo
******
* Input:
* string input_file : Nombre de el archivo que se lee
* string output_file : Nombre de el archivo donde se escribe
* tPolinomio polinomios[] : Lista que contiene los polinomios
* int& length : Variable por referencia que guardara el largo
* int pos = 0 : Posición de el cursor al escribir
* .......
******
* Returns:
* void, sin retorno
*****/

void InterpretarOperaciones(string input_file,string output_file,tPolinomio polinomios[],int lenght,int pos = 0){
    fstream in;
    fstream out;
    string line;
    string operation;

    in.open(input_file,ios::in);
    out.open(output_file,ios::out);

    in.seekg(pos,ios::beg);
    while(in >> line){
        operation = line;

        in >> line;
        int i = stoi(line);

        in >> line;

        if(operation == (string) "EVALUAR"){
            float x = stof(line);
            out << polinomios[i].evaluar(x) << endl;
        }

        if(operation == (string) "COEFICIENTE"){
            unsigned int x = stoi(line);
            out << polinomios[i].coeficiente(x) << endl;
        }
            
    }

    in.close();
    out.close();
}


int main(){
    int pos,lenght;
    tPolinomio* polinomios = ObtenerPolinomios("in.txt",pos,lenght);
    InterpretarOperaciones("in.txt","out.txt",polinomios,lenght,pos);

    return 0;
}

