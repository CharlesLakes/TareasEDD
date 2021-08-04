#ifndef Hashing_hpp
#define Hashing_hpp
#define M 100
#define P 100
#define VACIA -1

typedef int typePass;
typedef char typeData;

struct block{
    typePass pass = VACIA;
    typeData data[P];
};

int hashInsert(block HT[], typePass k, typeData I[P] , int typeSize);
typeData* hashSearch(block HT[], typePass k);
#endif