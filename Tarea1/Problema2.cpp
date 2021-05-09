#include <iostream>
#include <cmath>

using namespace std;

class A{
    private:
        int *B;
        unsigned long n;
        unsigned long b;
    public:
        A(){
            n = 0;
            b = 1;
            B = new int[b];
        };
        ~A(){
            delete[] B;
        }
        bool setValue(unsigned long i,int v);
        int getValue(unsigned long i);
        void append(int v);
        void remove();
        unsigned long size();
};



/*****
* void A::setValue
******
* Cambia el valor de un elemento de el arreglo solo si existe
******
* Input: 
* unsigned long i: La posición que quieres asignar el valor
* int v: El valor que quieres introducir en el arreglo
******
* Returns:
* bool, retorna True si se pudo asignar y False si no tuvo ningun efecto en el arreglo
*****/
bool A::setValue(unsigned long i,int v){

};

/*****
* int A::getValue
******
* Obtiene el valor de una posición de el arreglo
******
* Input: 
* unsigned long i: La posición de el valor que quieres obtener
******
* Returns:
* int, El valor que quieres obtener
*****/
int A::getValue(unsigned long i){

}


/*****
* void A::append
******
* Agrega un elemento al final arregla gestionando el espacio de memoria
******
* Input:
* int v: El valor el cual se quiere ingresar al arreglo
******
* Returns:
* void, No tiene un retorno
*****/
void A::append(int v){
    if(b == n){
        b *= 2;
        int *temp = new int[b];
        for(unsigned long i = 0; i < n; i++)
            temp[i] = B[i];
        delete[] B;
        B = temp;

    }
    B[n] = v;
    n++;
};

/*****
* void A::remove
******
* Elimina el ultimo elemente de el arreglo gestionando el uso de memoria
******
* Input: Sin entradas
******
* Returns:
* void, No tiene un retorno
*****/
void A::remove(){
    if(n == 0) return;
    if( ((unsigned long) b/2) + 1 == n && n > 1){
        if(b > 1)
            b /= 2;
        int *temp = new int[b];
        for(long unsigned i = 0; i < n; i++)
            temp[i] = B[i];
        delete[] B;
        B = temp;

    }
    n--;
}

/*****
* void A::size
******
* Obtiene la cantidad de elementos de el arreglo
******
* Input: Sin entradas
******
* Returns:
* unsigned long, Retorna la cantidad de elementos de el arreglo
*****/

unsigned long A::size(){
    return n;
};

