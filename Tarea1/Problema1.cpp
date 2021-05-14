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

FlujoNeto* datToFlujoNeto(string name_file,int& length){
    int pos;
    FlujoNeto *data;

    ifstream arch(name_file,ios::binary | ios::ate);  
    if(!arch.is_open()){
        cerr << "No se logro abrir el archivo " << name_file << endl;
        return NULL;
    }
    pos = arch.tellg();
    length = pos/sizeof(FlujoNeto);
    data = new FlujoNeto[length];
    arch.seekg(0,ios::beg);
    arch.read((char *) data,pos);
    arch.close();

    return data;

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
int ContarFlujoNeto(int hora, int minuto, FlujoNeto data[], int length){
    int p = 0;
    for (int i = 0; i < length; i++)
    {
        if ((data[i].hora*100 + data[i].minuto <= hora*100 + minuto ))
            p += data[i].personas;
        
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
Asistencia* txtToAsistencia(string name_file, int& length){
    string linea;
    fstream fp;
    int i=0,o=0,n_lineas = 0,minuto,hora;

    fp.open(name_file,ios::in );

    if(!fp.is_open()){
        cerr << "No se logro abrir el archivo " << name_file << endl;
        return NULL;
    }
    
    while(getline(fp,linea))
        n_lineas++;
    fp.close();
    fp.open(name_file,ios::in);
    Asistencia* arreglo = new Asistencia[n_lineas];

    while (fp>>linea ){
        if (i==0){     
            if (linea == (string) "E")
               arreglo[o].estado=1;
            if(linea == (string) "S")
                arreglo[o].estado=0;
        }
        if (i==1)
            arreglo[o].rut=linea;

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
int CalcularTrabajadores(int hora,int minuto,Asistencia data[], int length){
    int a=0, sumahora = (hora*100+minuto);

    for (int i = 0; i < length; i++){
        if ((data[i].hora*100 + data[i].minuto <= sumahora)&&(data[i].estado == 1)){
            a++;
            int flag = 1;
            for (int o = i+1 ; o < length && flag; o++){
                if ((data[o].rut == data[i].rut)&&(data[o].estado==1))
                    data[o].estado = 2;
               if ((data[o].rut == data[i].rut)&&(data[o].estado==0)){
                    if(data[o].hora*100 + data[o].minuto <= sumahora)
                        a--;
                    
                    flag =0;
               }
           }   
        }
    }
    
    
    return a;
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

    int largo_flujo;
    FlujoNeto *datos_flujo = datToFlujoNeto("flujo-publico.dat",largo_flujo);
    int cantidad_de_personas = ContarFlujoNeto(i_hora,i_minuto,datos_flujo,largo_flujo);

    int largo_trabajadores;
    Asistencia *datos_trabajadores = txtToAsistencia("asistencia.txt",largo_trabajadores);
    int cantidad_de_trabajadores = CalcularTrabajadores(i_hora,i_minuto,datos_trabajadores,largo_trabajadores);
    
    delete[] datos_flujo;
    delete[] datos_trabajadores;

    return cantidad_de_personas + cantidad_de_trabajadores;
}



int main(){
    cout << "08:00" << " "  << cantidadPersonas("08:00") << endl;
    cout << "08:04" << " "  << cantidadPersonas("08:04") << endl;
    cout << "08:30" << " "  << cantidadPersonas("08:30") << endl;
    cout << "09:00" << " "  << cantidadPersonas("09:00") << endl;
    cout << "10:00" << " "  << cantidadPersonas("10:00") << endl;
    cout << "12:00" << " "  << cantidadPersonas("12:00") << endl;
    cout << "12:15" << " "  << cantidadPersonas("12:15") << endl;
    cout << "12:16" << " "  << cantidadPersonas("12:16") << endl;
    cout << "12:30" << " "  << cantidadPersonas("12:30") << endl;
    cout << "13:30" << " "  << cantidadPersonas("13:30") << endl;
    cout << "14:30" << " "  << cantidadPersonas("14:30") << endl;
    cout << "15:50" << " "  << cantidadPersonas("15:50") << endl;
    cout << "16:00" << " "  << cantidadPersonas("16:00") << endl;
    cout << "17:10" << " "  << cantidadPersonas("17:10") << endl;
    cout << "17:15" << " "  << cantidadPersonas("17:15") << endl;
    cout << "18:00" << " "  << cantidadPersonas("18:00") << endl;
    cout << "18:15" << " "  << cantidadPersonas("18:15") << endl;
    cout << "20:00" << " "  << cantidadPersonas("20:00") << endl;

    return 0;
}

