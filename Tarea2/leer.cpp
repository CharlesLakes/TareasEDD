
tPolinomio* Leer( string name_file , int& length){

    int largo;
    fstream fp;
    fp.open(name_file,ios::in);

    if(!fp.is_open())
        {cerr << "No se logro abrir el archivo" << name_file << endl;
        return NULL;}

    fp>>largo;
    tPolinomio* listapolinomios = new tPolinomio[largo];
    for(int i=0; i<largo;i++){
        int largo_poli;
        fp>>largo_poli;
        for(int a=0; a<largo_poli;a++){
        
            unsigned int e;
            int c;
            fp>>e;
            fp>>c;
            listapolinomios[i].push(e,c);
        }
    }
    length = largo;

return listapolinomios   
}

