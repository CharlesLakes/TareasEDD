#ifndef Grafo_hpp
#define Grafo_hpp
typedef int tVertice;
struct Vecino{
    int id;
    Vecino* vecinos;
};

struct Vertice{
    int marca = 0;
    Vecino* vecinos;
};

class tGrafo{
    private:
        Vertice* lista;
        int size;
    public:
        tGrafo(int n);
        ~tGrafo(){};
        int nVertex();
        void setEdge (tVertice v1, tVertice v2);
        int getMark (tVertice v);
        void setMark (tVertice v, int marca);
        tVertice first (tVertice v);
        tVertice next (tVertice v, tVertice w);
};

#endif