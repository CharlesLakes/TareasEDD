#include <iostream>
#include <fstream>
#include "Hashing.hpp"
using namespace std;

struct producto {
    int cod_producto;
    char nombre_producto[31];
    int precio;
};

struct oferta {
    int cod_producto;
    int cantidad_descuento;
    int descuento;
    int productos_equivalentes[10];
};

block* fileToHash(string filename,int type = 1){
    int size;
    block* list = new block[M];
    fstream file;
    file.open(filename,ios::in);
    if(!file.is_open()){
        cerr << "No se logro abrir el archivo -> " << filename<< endl;
        return NULL;
    }

    file.read((char *) &size,sizeof(int));

    for(int i = 0;i < size; i++){
        if(type){
            producto temp;
            file.read((char *) &temp,sizeof(producto));
            hashInsert(list,temp.cod_producto,(char *) &temp);
        }else{
            oferta temp;
            file.read((char *) &temp,sizeof(oferta));
            hashInsert(list,temp.cod_producto,(char *) &temp);
        }
    }

    file.close();
    return list;

}

void createVoucher(string in_filename,string out_filename,block* products, block* offer){
    fstream inFile;
    fstream outFile;

    inFile.open(in_filename,ios::in);
    outFile.open(out_filename,ios::out);

    int N;
    inFile >> N;

    for(int i = 0; i < N; i++){
        int C;
        inFile >> C;
        for(int j = 0; j < C; j++){
            
        }
    }
}


int main(){
    block* products = fileToHash("productos.dat",1);
    block* offer = fileToHash("ofertas.dat",0);
    


    

}