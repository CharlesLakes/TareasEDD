#include <iostream>
#include "Hashing.hpp"

int h(int k){
    return k;
};

int p(int k,int i){
    return i;
}

int hashInsert(block HT[], typePass k, typeData I[P]){
    int first, i;
    int pos = first = h(k);
    for (i = 1; HT[pos].pass != VACIA && HT[pos].pass != k; i++)
        pos = (first + p(k, i)) % M; 
    if (HT[pos].pass == k)
        return 0; 
    else {
        HT[pos].pass = k;
        for(int i = 0; i < P; i++)
            HT[pos].data[i] = I[i];
        return 1; 
    }

};

typeData* hashSearch(block HT[], typePass k) {
    int first, i;
    int pos = first = h(k);
    for (i = 1; HT[pos].pass != VACIA && HT[pos].pass != k; i++)
        pos = (first + p(k, i)) % M; 

    if (HT[pos].pass == k){
        return HT[pos].data; 
    }else{
        return NULL; 
    }
}