#include <iostream>
#include <string.h>
using namespace std;

struct nodoString {
    string palabra;
    nodoString* sig;
};

struct hashDiccionario{
    nodoString ** hash;
    unsigned int largo;
};

unsigned int funcionHash( const string & clave, int B)
{
    unsigned int valor = 0;
    for(int i =0; i<clave.length();i++){
        valor = 37 * valor + clave[i];
    }
    return valor % B;
}

hashDiccionario* crearHash (unsigned int cantidadPalabras){
    hashDiccionario* hd = new hashDiccionario;
    hd->hash = new nodoString*[cantidadPalabras +1];
    for(int i=0; i<=cantidadPalabras; i++){
        hd->hash[i] = NULL;
    }
    hd->largo = cantidadPalabras;
    return hd;
}

void cargarPalabra (string& pal, hashDiccionario*& hd){
    unsigned int pos = funcionHash(pal, hd->largo);
    nodoString* nuevaPalabra = new nodoString;
    nuevaPalabra->palabra = pal;
    nuevaPalabra->sig = hd->hash[pos];
    hd->hash[pos] = nuevaPalabra;
}

bool existePalabra (string& pal, hashDiccionario* hd){
    unsigned int pos = funcionHash(pal, hd->largo);
    bool existe = false;
    nodoString* rec = hd->hash[pos];
    while(rec!=NULL){
        if(rec->palabra == pal ){
            existe = true;
        }
        rec = rec->sig;
    }
    return existe;
}

int main (){
    int N;
    cin >> N;
    hashDiccionario* diccionario = crearHash(N);
    for(int i=0; i<N ; i++){
        string pal;
        cin >> pal;
        cargarPalabra(pal, diccionario);
    }
    int M;
    cin >> M;
    for(int i=0; i<M; i++){
        string test;
        cin >> test;
        if(existePalabra(test, diccionario)){
            cout << "1"<< endl;
        }else{
            cout << "0"<< endl;
        }
    }
    return 0;
}