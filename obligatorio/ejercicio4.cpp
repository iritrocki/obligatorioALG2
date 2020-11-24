#include <iostream>
using namespace std;
#define RAIZ 1


struct NodoLista{
    int dato;
    NodoLista* sig;
};

struct ColaPrioridad{
    NodoLista ** array;
    int tope;
};

struct Grafo{
    NodoLista** listaAdy;
    int vertices;
    int aristas;
};

//TAD GRAFO

Grafo* inicializarGrafo (int cantV, int cantA){
    Grafo* g = new Grafo;
    g->listaAdy = new NodoLista*[cantV+1];
    for(int i=0; i<=cantV; i++){
        g->listaAdy[i]=NULL;
    }
    g->vertices=cantV;
    g->aristas=cantA;
    return g;
}

void cargarArista (int v, int w, Grafo*& g){
    NodoLista* arista = new NodoLista;
    arista->dato=w;
    arista->sig = g->listaAdy[v];
    g->listaAdy[v] = arista;
}

//TAD COLA

ColaPrioridad* inicializarCola (int cantV){
	ColaPrioridad* cola= new ColaPrioridad;
    cola->array = new NodoLista*[cantV+1];
    for(int i=0; i<=cantV; i++){
        cola->array[i] = NULL;
    }
	cola->tope = 0;
    return cola;
}


bool esVacio(ColaPrioridad* cola){
    return cola->tope == 0;
}

int padre(int pos){
	return pos/2;
}

void intercambiar(int pos1, int pos2, ColaPrioridad*& cola){
	int dato = cola->array[pos1]->dato;
	cola->array[pos1]->dato = cola->array[pos2]->dato;
	cola->array[pos2]->dato = dato;
}

void flotar (int pos, ColaPrioridad*& cola){
	if (pos != RAIZ){
		int posPadre = padre(pos);
		if ( cola->array[posPadre]->dato > cola->array[pos]->dato ){
			intercambiar(pos, posPadre, cola);
			flotar(posPadre, cola);
		}
	}
}

void encolar (ColaPrioridad*& cola, int dato){
    cola->tope++;
    cola->array[cola->tope]->dato = dato;
    flotar(cola->tope, cola);
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

int obtenerPosHijoMenor(int pos, ColaPrioridad* cola){
    int posHijoIzq = hijoIzq(pos);
    int posHijoDer = hijoDer(pos);
    if(posHijoDer <= cola->tope && cola->array[posHijoDer]->dato < cola->array[posHijoIzq]->dato){
        return posHijoDer;
    }
    return posHijoIzq;
}

void hundir(int pos, ColaPrioridad*& cola){
    if(!esHoja(pos, cola->tope)){
        int posHijoMenor = obtenerPosHijoMenor(pos, cola);
        if(cola->array[posHijoMenor]->dato < cola->array[pos]->dato){
            intercambiar(pos, posHijoMenor, cola);
            hundir(posHijoMenor, cola);
        }
    }
}

int desencolar (ColaPrioridad*& cola){
    int retorno = cola->array[RAIZ]->dato;
    cola->array[RAIZ]->dato = cola->array[cola->tope]->dato;
    cola->tope--;
    hundir(RAIZ, cola);
    return retorno;
}

void ordenacionTopologica(Grafo*& g){
    ColaPrioridad* cola = inicializarCola(g->vertices);
    int* arrayEntradas = new int[g->vertices+1];
    for(int i = 0; i<=g->vertices; i++){
        arrayEntradas[i] = 0;
    }
    for(int i =1; i<=g->vertices; i++){
        NodoLista* recorredor = g->listaAdy[i];
        while (recorredor !=NULL )
        {
            arrayEntradas[i]++;
            recorredor = recorredor->sig;
        }
    }
    for(int i =1; i<=g->vertices; i++){
        if(arrayEntradas[i]==0){
            encolar(cola, i);
        }
    }
    while(!esVacio(cola)){
        int v = desencolar(cola);
        cout << v << endl;
        NodoLista* w = g->listaAdy[v];
        while(w != NULL){
            arrayEntradas[w->dato]--;
            if(arrayEntradas[w->dato] == 0){
                encolar(cola, w->dato);
            }
            w = w->sig;
        }
    }
}

int main (){
    int Vertices;
    cin >> Vertices;
    int E;
    cin >> E;
    Grafo* g = inicializarGrafo(Vertices, E);
    for(int i=0; i<E; i++){
        int v;
        int w;
        cin >> v;
        cin >> w;
        cargarArista(v, w, g);
    }
    ordenacionTopologica(g);
}