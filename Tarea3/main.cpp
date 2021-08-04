#include <iostream>
#include <fstream>
#include "Hashing.hpp"
#include "Grafo.hpp"
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
            hashInsert(list,temp.cod_producto,(char *) &temp,sizeof(producto));
        }else{
            oferta temp;
            file.read((char *) &temp,sizeof(oferta));
            hashInsert(list,temp.cod_producto,(char *) &temp,sizeof(oferta));
        }
    }

    file.close();
    return list;

}

void createVoucher(string in_filename,string out_filename,block* products, block* offer){
    fstream inFile, outFile;
    int N;

    inFile.open(in_filename,ios::in | ios::binary);
    outFile.open(out_filename,ios::out);
    inFile >> N;
    outFile << N << endl;
    
    for(int i = 0; i < N; i++){
        int C, value = 0;
        inFile >> C;

        tGrafo temp(C);
        oferta** list_cod = new oferta*[C];

        for(int j = 0; j < C; j++){
            int cod_product;
            inFile >> cod_product;

            producto * temp_product = (producto *) hashSearch(products,cod_product);
            list_cod[j] = (oferta *) hashSearch(offer,cod_product);
            value += temp_product->precio;

            if(list_cod[j] != NULL){
                int flag = 0;
                for(int k = 0; k < j && !flag; k++)
                    if(list_cod[k] != NULL){ 
                        flag = list_cod[k]->cod_producto == cod_product;
                        for(int h = 0; h < 10 && !flag; h++)
                            flag = list_cod[k]->productos_equivalentes[h] == cod_product;
                        if(flag){ temp.setEdge(k,j); temp.setMark(j,-1);};
                    };
                
            }else temp.setMark(j,-1);
        }

        for(int j = 0; j < C; j++)
            if(list_cod[j] != NULL){
                if(temp.getMark(j) == 0){
                    int cont = 1;
                    for(tVertice i = temp.first(j); i < temp.nVertex(); i = temp.next(j,i))
                        cont++;
                    value -= ((cont/list_cod[j]->cantidad_descuento))*list_cod[j]->descuento;
                }
            };
        delete[] list_cod;
        outFile << value << endl;
    }
}


int main(){
    block* products = fileToHash("productos.dat",1);
    block* offer = fileToHash("ofertas.dat",0);
    createVoucher("compras.txt","boletas2.txt",products,offer);


    delete[] products;
    delete[] offer;
    return 0;
}