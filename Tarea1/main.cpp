#include <iostream>
#include <fstream>
#include "Problema1.cpp"

using namespace std;

void generadorDeArchivoTest(){

    struct FlujoNeto{
        int hora;
        int minuto;
        int personas;
    };

    ofstream arch("test.dat",ios::binary);
    struct FlujoNeto test[5];
    test[0] = {10,24,-10};
    test[1] = {10,10,50};
    test[2] = {20,30,10};
    test[3] = {20,9,10};
    test[4] = {20,0,10};
    arch.write((char *) &test,sizeof(test));
}

void LeeYOrdenTest(){
    int length;
    struct FlujoNeto *data = datToFlujoNeto("test.dat",length);

    for(int i = 0; i < length ; i++){
        cout << "Pos: " << i << endl;
        cout << '\t' << "Hora: " << data[i].hora << endl;
        cout << '\t' << "Minuto: " << data[i].minuto << endl;
        cout << '\t' << "Personas: " << data[i].personas << endl;
   }


    cout << "Ordenado:" << endl << endl;
    for(int i = 0; i < length ; i++){
        cout << "Pos: " << i << endl;
        cout << '\t' << "Hora: " << data[i].hora << endl;
        cout << '\t' << "Minuto: " << data[i].minuto << endl;
        cout << '\t' << "Personas: " << data[i].personas << endl;
   }

   delete[] data;
}

void testcontarflujo(int hora, int minuto){
    generadorDeArchivoTest();
    int length;
    struct FlujoNeto *data = datToFlujoNeto("test.dat",length);

    int c = ContarFlujoNeto(hora,minuto,data,length);
    cout << c << endl;
};


int main(){
    cout << cantidadPersonas("14:00") << endl;
    return 0;
}