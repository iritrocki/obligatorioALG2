#include <iostream>
using namespace std;
struct NodoIntAVL
{
    int dato;
    int balance;
    NodoIntAVL* izq;
    NodoIntAVL* der;
};

void insertarEnArbol(NodoIntAVL* &arbol, int dato);

void insertarEnArbol(NodoIntAVL* &arbol, int dato){
    bool vario_h = false;
    NodoIntAVL* arbolCopia1;
    NodoIntAVL* arbolCopia2;
    if(arbol == NULL){
        arbol = new NodoIntAVL();
        arbol->dato = dato;
        arbol->der=NULL;
        arbol->izq=NULL;
        arbol->balance = 0;
        vario_h=true;
    }
    else if (arbol->dato > dato){
        insertarEnArbol(arbol->izq, dato);
        if(vario_h){
            switch(arbol->balance){
                case 1:
                    arbol->balance = 0;
                    vario_h = false;
                    break;
                case 0:
                    arbol->balance = -1;
                    break;
                case -1:
                    arbolCopia1 = arbol->izq;
                    if(arbolCopia1->balance == -1){
                        arbol->izq = arbolCopia1->der;
                        arbolCopia1->der = arbol;
                        arbol->balance = 0;
                        arbol = arbolCopia1;
                    }
                    else{
                        arbolCopia2 = arbolCopia1->der;
                        arbolCopia1->der = arbolCopia2->izq;
                        arbolCopia2->izq = arbolCopia1;
                        arbol->izq = arbolCopia2->der;
                        arbolCopia2->der = arbol;
                        arbol->balance = arbolCopia2->balance == -1 ? 1 : 0;
                        arbolCopia1->balance = arbolCopia2->balance == 1 ? -1 : 0;
                        arbol = arbolCopia2;
                    }
                    arbol->balance = 0;
                    vario_h = false;
            }
        }
    }
    else if(arbol->dato < dato){
        insertarEnArbol(arbol->der, dato);
        if(vario_h){
            switch(arbol->balance){
                case -1:
                    arbol->balance = 0;
                    vario_h = false;
                    break;
                case 0:
                    arbol->balance = 1;
                    break;
                case 1:
                    arbolCopia1 = arbol->der;
                    if(arbolCopia1->balance == 1){
                        arbol->der = arbolCopia1->izq;
                        arbolCopia1->izq = arbol;
                        arbol->balance = 0;
                        arbol = arbolCopia1;
                    }
                    else{
                        arbolCopia2 = arbolCopia1->izq;
                        arbolCopia1->izq = arbolCopia2->der;
                        arbolCopia2->der = arbolCopia1;
                        arbol->der = arbolCopia2->izq;
                        arbolCopia2->izq = arbol;
                        arbol->balance = arbolCopia2->balance == 1 ? -1 : 0;
                        arbolCopia1->balance = arbolCopia2->balance == -1 ? 1 : 0;
                        arbol = arbolCopia2;
                    }
                    arbol->balance = 0;
                    vario_h = false;
            }
        }
    }
    else{
        vario_h = false;
    }
}
void imprimirArbol (NodoIntAVL* &arbol);
void imprimirArbol (NodoIntAVL* &arbol){
    if(arbol != NULL){
        if(arbol->izq== NULL){
            cout << arbol->dato << endl;
            imprimirArbol(arbol->der);
        }else{
            imprimirArbol(arbol->izq);
            cout << arbol->dato << endl;
            imprimirArbol(arbol->der);
        }
    }
}

int main(){

    //freopen("1000.in.txt", "r", stdin);
    //freopen("1000.out.txt","w", stdout);

    int N;
    cin >> N;
    NodoIntAVL* arbol = NULL;
    for(int i=0; i<N; i++){
        int dato;
        cin >> dato;
        insertarEnArbol(arbol, dato);
    }
    
    imprimirArbol(arbol);
    return 0;
}

