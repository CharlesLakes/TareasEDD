#ifndef Hashing_hpp
#define Hashing_hpp
#define P 100
#define VACIA -1

typedef int typePass;
typedef char typeData;

struct block{
    typePass pass = VACIA;
    typeData data[P];
};

int hashInsert(block HT[], typePass k, typeData I[], int typeSize,int& M);
typeData* hashSearch(block HT[], typePass k, int& M);
#endif