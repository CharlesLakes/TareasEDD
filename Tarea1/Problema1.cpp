#include <iostream>
#include <fstream>
using namespace std;

struct FlujoNeto{
    int hora;
    int minuto;
    int personas;
};


/*****
* int datToFlujoNeto
******
* Interpreta y le los datos de el archivo .dat 
* y los convierte en una lista de struct FlujoNeto
******
* Input:
* string name_file : Nombre de el archivo binario
* struct FlujoNeto** data: Puntero de puntero que guarda 
* la direccion de memoria de el puntero que guardara los 
* datos afuera de la funcion
******
* Returns:
* int, Cantidad de struct FlujoNeto de el archivo name_file
*****/

int datToFlujoNeto(string name_file,struct FlujoNeto **data){
    int pos, lenght;

    ifstream arch(name_file,ios::binary | ios::ate);  
    if(arch.is_open()){
        pos = arch.tellg();
        lenght = pos/sizeof(struct FlujoNeto);
        *data = new struct FlujoNeto[lenght];
        arch.seekg(0,ios::beg);
        arch.read((char *) *data,pos);

        return lenght;
    }
    return 0;

}

/*****
* void sortFlujoNeto
******
* Ordena la lista de struct FlujoNeto de menor a mayor segun su hora
******
* Input:
* int lenght : Largo de el arreglo de struct FlujoNeto
* struct FlujoNeto* data: Puntero que guarda la direccion de memoria de
* el arreglo de struct FlujoNeto
******
* Returns:
* void, No tiene rentorno
*****/
void sortFlujoNeto(int lenght, struct FlujoNeto *data){
    for(int i = 0; i < lenght - 1 ; i++){
        for(int a = 0; a < lenght - i - 1; a++){
            if(data[a].hora*100 + data[a].minuto > data[a + 1].hora*100 + data[a + 1].minuto){
                struct FlujoNeto temp;
                temp = data[a + 1];
                data[a + 1] = data[a];
                data[a] = temp;
            }
        }
    }
}

/*****
* int cantidadPersonas
******
* Entrega la cantidad de personas en cierta hora
******
* Input:
* string hora : La hora en un formato hh:mm
******
* Returns:
* int, Devuelve la cantidad de personas en el local
*****/

int cantidadPersonas(string hora){
    

    return 0;
}