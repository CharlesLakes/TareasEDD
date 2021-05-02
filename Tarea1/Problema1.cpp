#include <iostream>
#include <fstream>
using namespace std;

struct FlujoNeto{
    int hora;
    int minuto;
    int personas;
};


/*****
* void InterpretarHora
******
* La funcion interpreta la hora segun un string
******
* Input:
* string str_hora = String de la hora
* int *hora: Puntero a la variable donde se guardara la hora
* int *minuto: Puntero a la variable donde se guardara el minuto
******
* Returns:
* void, sin return
*****/
void InterpretarHora(string str_hora ,int *hora, int *minuto ){
    string str1,str2;
    int pos = str_hora.find(':');
    str1 = str_hora.substr(0,pos);
    str2 = str_hora.substr(pos + 1);
    *hora = stoi(str1);
    *minuto = stoi(str2);
}




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

int datToFlujoNeto(string name_file,struct FlujoNeto *data[]){
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
* struct FlujoNeto* data: Puntero que guarda la direccion de memoria de
* el arreglo de struct FlujoNeto
* int lenght : Largo de el arreglo de struct FlujoNeto

******
* Returns:
* void, No tiene rentorno
*****/
void sortFlujoNeto(struct FlujoNeto data[], int lenght){
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
* int ContarFlujoNeto
******
* La funcion cuenta la personas segun el FlujoNeto
******
* Input:
* int hora: La hora requerida
* int minuto: El minuto requerido
* struct FlujoNeto* data: Puntero que guarda la direccion de memoria de
* el arreglo de struct FlujoNeto
* int lenght : Largo de el arreglo de struct FlujoNeto
******
* Returns:
* int, Cantidad de Personas
*****/
int ContarFlujoNeto(int hora, int minuto, struct FlujoNeto data[], int lenght){

}




struct Asistencia{
    int estado;
    string rut;
    int hora;
    int minuto;
};


/*****
* int txtToAsistencia
******
* La funcion retorna el largo de los datos que se encuentran en el archivo
******
* Input:
* string name_file: Nombre de el archivo en un formato "ESTADO RUT HH:MM"
* struct Asistencia **data: Puntero que apunta a otro puntero al que se le
* asignara memoria y la informacion
******
* Returns:
* int, Cantidad de datos
*****/
int txtToAsistencia(string name_file, struct Asistencia *data[]){

}





/*****
* int CalcularTrabajadores
******
* La funcion cuenta la personas que esta trabajando segun la hora dada
******
* Input:
* int hora: La hora requerida
* int minuto: El minuto requerido
* struct Asistencia *data: Puntero que guarda el arreglo de los struct
* int lenght: El largo de el arreglo
******
* Returns:
* int, Cantidad de trabajadores en cierta hora
*****/
int CalcularTrabajadores(int hora,int minuto,struct Asistencia data[], int lenght){

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
    int i_hora,i_minuto;
    InterpretarHora(hora,&i_hora,&i_minuto);

    struct FlujoNeto *datos_trabajadores;
    int largo_trabajadores = datToFlujoNeto("test.dat",&datos_trabajadores);
    sortFlujoNeto(datos_trabajadores,largo_trabajadores);




    return 0;
}