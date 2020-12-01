#include <iostream>
using namespace std;
#define RAIZ 1


struct NodoLista {
    int dato;
    NodoLista* sig;
};

struct ColaPrioridad {
    int* array;
    int tope;
};

struct nodoCola {
    ColaPrioridad* dato;
    nodoCola* sig;
};

struct colaFIFO {
    nodoCola* ppio;
    nodoCola* ultimo;
    int cantElem;
};

struct Grafo {
    NodoLista** listaAdy;
    int vertices;
    int aristas;
};

//TAD GRAFO

Grafo* inicializarGrafo(int cantV, int cantA) {
    Grafo* g = new Grafo;
    g->listaAdy = new NodoLista * [cantV + 1];
    for (int i = 0; i <= cantV; i++) {
        g->listaAdy[i] = NULL;
    }
    g->vertices = cantV;
    g->aristas = cantA;
    return g;
}

void cargarArista(int v, int w, Grafo*& g) {
    NodoLista* arista = new NodoLista;
    arista->dato = w;
    arista->sig = g->listaAdy[v];
    g->listaAdy[v] = arista;
}

//TAD COLA

ColaPrioridad* inicializarCola(int cantV) {
    ColaPrioridad* cola = new ColaPrioridad;
    cola->array = new int[cantV + 1];
    for (int i = 0; i <= cantV; i++) {
        cola->array[i] = 0;
    }
    cola->tope = 0;
    return cola;
}


bool esVacio(ColaPrioridad* cola) {
    return cola->tope == 0;
}

int padre(int pos) {
    return pos / 2;
}

void intercambiar(int pos1, int pos2, ColaPrioridad*& cola) {
    int dato = cola->array[pos1];
    cola->array[pos1] = cola->array[pos2];
    cola->array[pos2]= dato;
}

void flotar(int pos, ColaPrioridad*& cola) {
    if (pos != RAIZ) {
        int posPadre = padre(pos);
        if (cola->array[posPadre] > cola->array[pos]) {
            intercambiar(pos, posPadre, cola);
            flotar(posPadre, cola);
        }
    }
}

void encolar(ColaPrioridad*& cola, int dato) {
    cola->tope++;
    cola->array[cola->tope] = dato;
    flotar(cola->tope, cola);
}

int hijoIzq(int pos) {
    return pos * 2;
}

int hijoDer(int pos) {
    return pos * 2 + 1;
}

bool esHoja(int pos, int tope) {
    return hijoIzq(pos) > tope;
}

int obtenerPosHijoMenor(int pos, ColaPrioridad* cola) {
    int posHijoIzq = hijoIzq(pos);
    int posHijoDer = hijoDer(pos);
    if (posHijoDer <= cola->tope && cola->array[posHijoDer] < cola->array[posHijoIzq]) {
        return posHijoDer;
    }
    return posHijoIzq;
}

void hundir(int pos, ColaPrioridad*& cola) {
    if (!esHoja(pos, cola->tope)) {
        int posHijoMenor = obtenerPosHijoMenor(pos, cola);
        if (cola->array[posHijoMenor] < cola->array[pos]) {
            intercambiar(pos, posHijoMenor, cola);
            hundir(posHijoMenor, cola);
        }
    }
}

int desencolar(ColaPrioridad*& cola) {
    int retorno = cola->array[RAIZ];
    cola->array[RAIZ] = cola->array[cola->tope];
    cola->tope--;
    hundir(RAIZ, cola);
    return retorno;
}

//COLA FIFO
colaFIFO* inicializarColaFifo (){
    colaFIFO* c = new colaFIFO;
    c->ppio = NULL;
    c->ultimo = NULL;
    c->cantElem = 0;
    return c;
}

bool esVacia (colaFIFO* cola){
    return cola->cantElem == 0;
}

void encolar (colaFIFO*& cola, ColaPrioridad* elem){
    nodoCola* nodo = new nodoCola;
    nodo->dato = elem;
    nodo->sig = NULL;
    if(esVacia(cola)){
        cola->ppio = nodo;
        cola->ultimo = cola->ppio;
    }else{
        cola->ultimo->sig = nodo;
        cola->ultimo = cola->ultimo->sig;
    }
    cola->cantElem++;
}

ColaPrioridad* desencolar (colaFIFO*& cola){
    //assert(!esVacia(cola));
    ColaPrioridad* elem = cola->ppio->dato;
    if(cola->cantElem == 1){
        cola->ppio = NULL;
        cola->ultimo = NULL;   
    }else{
        cola->ppio = cola->ppio->sig;
    }
    cola->cantElem--;
    return elem;
}


//Algoritmo ordenacion topológica
void ordenacionTopologica(Grafo* g) {
    colaFIFO* cola = inicializarColaFifo();
    int* arrayEntradas = new int[g->vertices + 1];
    for (int i = 0; i <= g->vertices; i++) {
        arrayEntradas[i] = 0;
    }
    for (int i = 1; i <= g->vertices; i++) {
        NodoLista* recorredor = g->listaAdy[i];
        while (recorredor != NULL)
        {
            arrayEntradas[recorredor->dato]++;
            recorredor = recorredor->sig;
        }
    }
    ColaPrioridad* colaNivelCero = inicializarCola(g->vertices);
    for (int i = 1; i <= g->vertices; i++) {
        if (arrayEntradas[i] == 0) {
            encolar(colaNivelCero, i);
        }
    }
    encolar(cola, colaNivelCero);
    while (!esVacia(cola)) {
        ColaPrioridad* c = desencolar(cola);
        ColaPrioridad* e = inicializarCola(g->vertices);
        while(!esVacio(c)){
            int v = desencolar(c);
            cout << v << endl;
            NodoLista* w = g->listaAdy[v];
            while (w != NULL) {
                arrayEntradas[w->dato]--;
                if (arrayEntradas[w->dato] == 0) {
                    encolar(e, w->dato);
                }
                w = w->sig;
            }
        }
        encolar(cola, e);
    }
}

int main() {
    int Vertices;
    cin >> Vertices;
    int E;
    cin >> E;
    Grafo* g = inicializarGrafo(Vertices, E);
    //Cargo el grafo con las aristas que me pasan:
    for (int i = 0; i < E; i++) {
        int v;
        int w;
        cin >> v;
        cin >> w;
        cargarArista(v, w, g);
    } //O(E)
    ordenacionTopologica(g);
}
