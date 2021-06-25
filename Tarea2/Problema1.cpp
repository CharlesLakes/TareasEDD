#include <iostream>
#include <fstream>

struct tNodo{
    unsigned int E;
    int C;
    tNodo* sig;
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
        tNodo *iLista;
        unsigned int n;
        unsigned Emax;
    public:
        tPolinomio();
        ~tPolinomio();
        void append(unsigned int iE, int iC);
        float evaluar(float x,unsigned int e);
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
    Emax = 0;
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
* void tPolinomio::clear
******
* Limpia o reinicializa la lista
******
* Input: 
* Sin entradas
******
* Returns:
* void, No tiene un retorno
*****/
void tPolinomio::clear(){
    while(iLista != NULL){
        tNodo *aux = iLista->sig;
        delete[] iLista;
        iLista = aux;
    }
    n = 0;
    Emax = 0;
};

/*****
* int tPolinomio::coeficiente
******
* Recibe la entrada del exponete, busca y retorna el coeficiente del monomio 
******
* Input: 
* unsigned iE : Entrada del exponente
******
* Returns:
* int C, retorna el coeficiente
*****/
int tPolinomio::coeficiente(unsigned iE){
    tNodo *aux = iLista;
    int C = 0;
    while(aux != NULL){
        if(aux->E == iE)
            C = aux->C;
        aux = aux->sig;
    }
    return C;
}

/*****
* void tPolinomio::append
******
* Agrega un nuevo nodo a la lista 
******
* Input: 
* unsigned int iE : Entrada del exponente
* int iC :  Entrada del coeficiente
******
* Returns:
* void, No tiene un retorno
*****/
void tPolinomio::append(unsigned int iE, int iC){
    tNodo *tempNodo = new tNodo;
    tNodo *searchNodo = iLista;
    tempNodo->E = iE;
    tempNodo->C = iC;
    if(n == 0){
        iLista = tempNodo;
    }else{
        while (searchNodo->sig != NULL)
            searchNodo = searchNodo->sig;
        searchNodo->sig = tempNodo;
    }
    
    if(Emax < iE)
        Emax = iE;
    n++;
}

/*****
* float tPolinomio::evaluar
******
* Función recursiva que evalua la x en un polinomio
* y retornando el resultado
******
* Input: 
* float x : Número por el cual se reemplaza la x
* unsigned int e = 0 : Contador de exponente
******
* Returns:
* float , es el Polinomio evaluado en x
*****/
float tPolinomio::evaluar(float x,unsigned int e = 0){
    int C = coeficiente(e);
    if(e == Emax)
        return C;
    return C + x*evaluar(x,e + 1);
}




using namespace std;


/*****
* tPolinomio* ObtenerPolinomios
******
* Interpreta y lee los datos de el archivo .txt 
* y los guarda en una lista
******
* Input:
* string name_file : Nombre de el archivo de texto
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
            listapolinomios[i].append(e,c);
        }
    }
    
    length = largo;
    pos = fp.tellg();

    fp.close();
    return listapolinomios;
}


/*****
* void InterpretarOperaciones
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
* void, No tiene un retorno
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