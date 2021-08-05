#include "Hashing.hpp"
#define NULL nullptr

int h(int k){
    int i,  c = k*k, r = 0,left,right,m;
    for(i = 1; (int)(c/i) != 0; i *= 10) r++;
    m = (float) r/2;
    left = i;
    right = 1;
    for(int a = r; a > r - m + 1; a--) left /= 10;
    for(int a = 1; a < r - m; a++) right *= 10;
    return  (c%left)/right;
};

int h2(int k){
    return k*k;
};

int p(int k,int i){
    return i*h2(k);
};

int hashInsert(block HT[], typePass k, typeData I[], int typeSize,int& M){
    int first, i;
    int pos = first = h(k);

    for (i = 1; HT[pos].pass != VACIA && HT[pos].pass != k; i++)
        pos = (first + p(k, i)) % M; 
    if (HT[pos].pass == k)
        return 0; 
    else {
        HT[pos].pass = k;
        for(int i = 0; i < typeSize; i++)
            HT[pos].data[i] = I[i];
        return 1; 
    }

};

typeData* hashSearch(block HT[], typePass k, int& M) {
    int first, i;
    int pos = first = h(k);

    for (i = 1; HT[pos].pass != VACIA && HT[pos].pass != k; i++)
        pos = (first + p(k, i)) % M; 

    if (HT[pos].pass == k)
        return HT[pos].data; 
    else
        return NULL; 
}