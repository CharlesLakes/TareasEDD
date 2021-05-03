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
    test[0] = {15,24,10};
    test[1] = {10,10,10};
    test[2] = {15,30,10};
    test[3] = {10,9,10};
    test[4] = {9,0,10};
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

    sortFlujoNeto(data,length);
    cout << "Ordenado:" << endl << endl;
    for(int i = 0; i < length ; i++){
        cout << "Pos: " << i << endl;
        cout << '\t' << "Hora: " << data[i].hora << endl;
        cout << '\t' << "Minuto: " << data[i].minuto << endl;
        cout << '\t' << "Personas: " << data[i].personas << endl;
   }

   delete[] data;
}


int main(){
    LeeYOrdenTest();

    return 0;
}