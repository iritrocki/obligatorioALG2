#include <iostream>
using namespace std;

#define RAIZ 1

struct nodoLista{
    int dato;
    nodoLista* sig;
};


struct heap{
    nodoLista** array;
    int tope;
};

heap* inicializar (int cantListas){
	heap* miHeap= new heap;
    miHeap->array = new nodoLista*[cantListas+1];
    for(int i=0; i<=cantListas; i++){
        miHeap->array[i]=NULL;
    }
	miHeap->tope = 0;
    return miHeap;
}

int padre(int pos){
	return pos/2;
}

void intercambiar(int pos1, int pos2, heap*& miHeap){
	nodoLista* ptr = miHeap->array[pos1];
	miHeap->array[pos1] = miHeap->array[pos2];
	miHeap->array[pos2] = ptr;
}

void flotar (int pos, heap*& miHeap){
	if (pos != RAIZ){
		int posPadre = padre(pos);
		if ( miHeap->array[posPadre]->dato > miHeap->array[pos]->dato ){
			intercambiar(pos, posPadre, miHeap);
			flotar(posPadre, miHeap);
		}
	}
}

void insertarNuevaLista (nodoLista*& lista, heap*& miHeap){
    miHeap->tope +=1;
	miHeap->array[miHeap->tope] = lista;
	flotar(miHeap->tope, miHeap);
}

nodoLista* crearLista(int largoLista){
    nodoLista* retorno = NULL;
    int e;
    cin >> e;
    retorno = new nodoLista;
    retorno->dato=e;
    retorno->sig = NULL;
    nodoLista* recorredor = retorno;
    for (int i=1; i<largoLista; i++){
        int e;
        cin >> e;
        nodoLista* nodo = new nodoLista;
        nodo->dato = e;
        nodo->sig = NULL;
        recorredor->sig = nodo;
        recorredor=recorredor->sig;
        
    }
    return retorno;
}

int hijoIzq (int pos){
    return pos*2;
}

int hijoDer (int pos){
    return pos*2 + 1;
}

bool esHoja(int pos, int tope){
    return hijoIzq(pos) > tope;
}

bool esVacioHeap(heap* miHeap){
    return miHeap->tope ==0;
}

int obtenerPosHijoMenor(int pos, heap* miHeap){
    int posHijoIzq = hijoIzq(pos);
    int posHijoDer = hijoDer(pos);
    if(posHijoDer <= miHeap->tope && miHeap->array[posHijoDer]->dato < miHeap->array[posHijoIzq]->dato){
        return posHijoDer;
    }
    return posHijoIzq;
}

void hundir(int pos, heap*& miHeap){
    if(!esHoja(pos, miHeap->tope)){
        int posHijoMenor = obtenerPosHijoMenor(pos, miHeap);
        if(miHeap->array[posHijoMenor]->dato < miHeap->array[pos]->dato){
            intercambiar(pos, posHijoMenor, miHeap);
            hundir(posHijoMenor, miHeap);
        }
    }
}


int obtenerMenor (heap*& miHeap){
    return miHeap->array[RAIZ]->dato;
}

void eliminarRaiz (heap*& miHeap){
    miHeap->array[RAIZ] = miHeap->array[RAIZ]->sig;
    if(miHeap->array[RAIZ] == NULL){
        miHeap->array[RAIZ] = miHeap->array[miHeap->tope];
        miHeap->tope -= 1;
    }
    hundir(RAIZ, miHeap);

}

int main(){
    int K;
    cin >> K;
    heap* unHeap = inicializar(K);
    for(int i=0; i<K; i++){
        int N;
        cin >> N;
        nodoLista* lista = crearLista(N);
        insertarNuevaLista(lista, unHeap);
    }
    while(!esVacioHeap(unHeap)){
        cout << unHeap->array[RAIZ]->dato << endl;
        eliminarRaiz(unHeap);
    }
}