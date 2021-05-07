#include <iostream>
#include <cmath>

using namespace std;

class A{
    private:
        int *B;
        unsigned long n;
        unsigned long k;
    public:
        A(){
            n = 0;
            k = 0;
            B = new int[(int) pow(2,k)];
        };
        bool setValue(unsigned long i,int v);
        int getValue(unsigned long i);
        void append(int v);
        void remove();
        unsigned long size();
        /*unsigned long size_k();*/
};
void A::append(int v){
    if((unsigned long) pow(2,k) == n){
        k++;
        int *temp = new int[(int) pow(2,k)];
        for(unsigned long i = 0; i < n; i++)
            temp[i] = B[i];
        delete[] B;
        B = temp;

    }
    B[n] = v;
    n++;
};
void A::remove(){
    if(n == 0) return;
    if((unsigned long) pow(2,k - 1) + 1 == n ){
        if(k > 0)
            k--;
        int *temp = new int[(int) pow(2,k)];
        for(long unsigned i = 0; i < n; i++)
            temp[i] = B[i];
        delete[] B;
        B = temp;

    }
    n--;
}
unsigned long A::size(){
    return n;
};
/*
unsigned long A::size_k(){
    return pow(2,k);
}*/

