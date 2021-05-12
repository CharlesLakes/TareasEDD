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
* struct FlujoNeto* datToFlujoNeto
******
* Interpreta y le los datos de el archivo .dat 
* y los convierte en una lista de struct FlujoNeto
******
* Input:
* string name_file : Nombre de el archivo binario
* int length: Variable por referencia que guardara el largo 
* de el arreglo de struct FlujoNeto
******
* Returns:
* struct FlujoNeto*, El arreglo de struct FlujoNeto contenido en el archivo binario
*****/

struct FlujoNeto* datToFlujoNeto(string name_file,int& length){
    int pos;
    struct FlujoNeto *data;

    ifstream arch(name_file,ios::binary | ios::ate);  
    if(arch.is_open()){
        pos = arch.tellg();
        length = pos/sizeof(struct FlujoNeto);
        data = new struct FlujoNeto[length];
        arch.seekg(0,ios::beg);
        arch.read((char *) data,pos);

        return data;
    }
    return NULL;

}

/*****
* void sortFlujoNeto
******
* Ordena la lista de struct FlujoNeto de menor a mayor segun su hora
******
* Input:
* struct FlujoNeto* data: Puntero que guarda la direccion de memoria de
* el arreglo de struct FlujoNeto
* int length : Largo de el arreglo de struct FlujoNeto
******
* Returns:
* void, No tiene rentorno
*****/
void sortFlujoNeto(struct FlujoNeto data[], int length){
    for(int i = 0; i < length - 1 ; i++){
        for(int a = 0; a < length - i - 1; a++){
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
* int length : Largo de el arreglo de struct FlujoNeto
******
* Returns:
* int, Cantidad de Personas
*****/
int ContarFlujoNeto(int hora, int minuto, struct FlujoNeto data[], int length){
    int p = 0;
    for (int i = 0; i < length; i++)
    {
        if ((data[i].hora*100 + data[i].minuto <= hora*100 + minuto )){
            p += data[i].personas;
        }
    }
    return p;
}




struct Asistencia{
    int estado;
    string rut;
    int  hora;
    int minuto;
};


/*****
* struct Asistencia* txtToAsistencia
******
* La funcion retorna el largo de los datos que se encuentran en el archivo
* los cuales estan en un formato "ESTADO RUT HH:MM"
******
* Input:
* string name_file: Nombre de el archivo 
* int& length: Variable donde se guardara el largo de el arreglo de struct Asistencia
******
* Returns:
* struct Asistencia*, Arreglo de struct de los datos leidos en el archivo
*****/
struct Asistencia* txtToAsistencia(string name_file, int& length){
    string linea;
    fstream fp;
    int i=0,o=0,n_lineas,minuto,hora;

    fp.open(name_file,ios::in);

    if(!fp.is_open())
        {cerr << "No se logro abrir el archivo" << name_file << endl;
        return NULL;}

    while (getline(fp,linea))
        n_lineas++;

    Asistencia* arreglo = new Asistencia[n_lineas];
    fp.seekg(0,ios::beg);

    while (fp>>linea)
    {
        if (i==0){
            if (linea==(string)"E"){
               arreglo[o].estado=1;
            }
            else{
                arreglo[o].estado=0;
            }    
        }
        if (i==1){
            arreglo[o].rut=linea;
        }
        if (i==2){
            InterpretarHora(linea,&hora,&minuto);
            arreglo[o].hora=hora;
            arreglo[o].minuto=minuto;
            i=-1;
            o++;
        }
        i++;
    }   
    fp.close();
    length=n_lineas;
    return arreglo;
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
* int length: El largo de el arreglo
******
* Returns:
* int, Cantidad de trabajadores en cierta hora
*****/
int CalcularTrabajadores(int hora,int minuto,struct Asistencia data[], int length){

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

    int largo_trabajadores;
    struct FlujoNeto *datos_trabajadores = datToFlujoNeto("test.dat",largo_trabajadores);
    sortFlujoNeto(datos_trabajadores,largo_trabajadores);

    return 0;
}