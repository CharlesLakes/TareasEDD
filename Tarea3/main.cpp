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

/*****
* block* fileToHash 
******
* Interpreta y lee los datos de el archivo .bat
* y los guarda en una lista usando hashing
******
* Input:
* string filename : nombre del archivo
* float alpha : porcentaje del arreglo que debe estar lleno
* int& size : largo del arreglo
* int type : producto(1) u oferta(0)
******
* Returns:
* list, lista con los elementos ordenados por hashing   
*****/

block* fileToHash(string filename, float alpha, int& size, int type = 1){
    block* list;
    fstream file;
    file.open(filename,ios::in);
    if(!file.is_open()){
        cerr << "No se logro abrir el archivo -> " << filename<< endl;
        return NULL;
    }

    file.read((char *) &size,sizeof(int));

    int M = (size/alpha);
    while(size >= M) M++;
    

    list = new block[M];

    for(int i = 0;i < size; i++){
        if(type){
            producto temp;
            file.read((char *) &temp,sizeof(producto));
            if(!hashInsert(list,temp.cod_producto,(char *) &temp,sizeof(producto),M))
                cerr << "La llave ya a sido ingresada." << endl;
        }else{
            oferta temp;
            file.read((char *) &temp,sizeof(oferta));
            if(!hashInsert(list,temp.cod_producto,(char *) &temp,sizeof(oferta),M))
                cerr << "La llave ya a sido ingresada." << endl;
        }
    }
    size = M;
    
    file.close();
    return list;

}

/*****
* void createVoucher
******
* Lee las compras y genera la boleta
******
* Input:
* string in_filename : nombre del archivo de entrada
* string out_filename : nombre del archivo de salida
* block* products : lista con los productos de la tienda
* block* offer : lista con los descuentos de la tienda
* int& M_product : largo de la tabla de hashing de los productos
* int& M_offer : largo de la tabla de hashing de los descuentos
******
* Returns:
* No tiene retorno
*****/

void createVoucher(string in_filename,string out_filename,block* products, block* offer,int& M_product, int& M_offer){
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
            
            producto * temp_product = (producto *) hashSearch(products,cod_product,M_product);
            list_cod[j] = (oferta *) hashSearch(offer,cod_product,M_offer);
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
    int M_products, M_offer;
    block* products = fileToHash("productos.dat",0.7,M_products,1);
    block* offer = fileToHash("ofertas.dat",0.7,M_offer,0);

    createVoucher("compras.txt","boletas.txt",products,offer,M_products,M_offer);


    delete[] products;
    delete[] offer;
    return 0;
}