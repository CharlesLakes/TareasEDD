#include "Hashing.hpp"
#include <iostream>
//#define NULL nullptr

/*****
* int h
******
* Le asigna una casilla en la cual será guardada la información con clave k
******
* Input:
* typePass k : clave del dato
******
* Returns:
* (c%left)/right, posición de la clave en la tabla
*****/

int h(typePass k){
    int i,  c = k*k, r = 0,left,right,m;
    for(i = 1; (int)(c/i) != 0; i *= 10) r++;
    m = (float) r/2;
    left = i;
    right = 1;
    for(int a = r; a > r - m + 1; a--) left /= 10;
    for(int a = 1; a < r - m; a++) right *= 10;
    return  (c%left)/right;
};

/*****
* int h2
******
* Eleva k al cuadraado
******
* Input:
* typePass k : clave del dato
* int M : largo de la tabla de hashing
******
* Returns:
* 2 si el M es impar y 1 si par
*****/

int h2(typePass k, int M){
    if(M%2 == 0)
        return 1;
    return 2;
};

/*****
* int p
******
* Politica de colisión
******
* Input:
* typePass k : clave del dato
* int i : cantidad de colisiones
* int M :  largo de la tabla de hashing
******
* Returns:
* i*h2(k), nueva posición del dato en la tabla (cantidad de colisiones) por (k al cuadrado)
*****/

int p(int k,int i, int M){
    return i*h2(k,M);
};

/*****
* int hashInsert
******
* Resumen Función
******
* Input:
* block HT[] : la tabla de hashing
* typePass k : clave del dato
* typeData I[] : struct casteado en chart
* int typeSize : largo del struct
* int& M : largo de la tabla de hashing
******
* Returns:
* 0, no se inserta el dato
* 1, se inserta con éxito el dato
*****/

int hashInsert(block HT[], typePass k, typeData I[], int typeSize,int& M){
    int first, i;
    int pos = first = h(k) % M;

    for (i = 1; HT[pos].pass != VACIA && HT[pos].pass != k; i++)
        pos = (first + p(k, i, M)) % M; 

    if (HT[pos].pass == k){
        return 0;
    }else {
        HT[pos].pass = k;
        for(int i = 0; i < typeSize; i++)
            HT[pos].data[i] = I[i];
        return 1; 
    }

};

/*****
* typeData* hashSearch
******
* Busca si hay un dato con una clave k en la tabla de hashing
******
* Input:
* block HT[] : la tabla de hashing
* typePass k : clave del dato
* int& M : largo de la tabla de hashing
******
* Returns:
* HT[pos].data, retorna el dato con clave k
* NULL, si no hay nada retorna indefinido
*****/

typeData* hashSearch(block HT[], typePass k, int& M) {
    int first, i;
    int pos = first = h(k) % M;

    for (i = 1; HT[pos].pass != VACIA && HT[pos].pass != k; i++)
        pos = (first + p(k, i, M)) % M; 
    

    if (HT[pos].pass == k)
        return HT[pos].data; 
    else
        return NULL; 
}