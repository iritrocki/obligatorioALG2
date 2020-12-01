#include <iostream>
using namespace std;
#define RAIZ 1


struct NodoLista {
    int dato;
    NodoLista* sig;
};

struct nodoDobleDato {
    int nivel;
    int dato;
};

struct ColaPrioridad {
    nodoDobleDato** array;
    int tope;
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
    cola->array = new nodoDobleDato*[cantV + 1];
    for (int i = 0; i <= cantV; i++) {
        cola->array[i] = NULL;
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
    nodoDobleDato* aux = cola->array[pos1];
    cola->array[pos1] = cola->array[pos2];
    cola->array[pos2]= aux;
}

void flotar(int pos, ColaPrioridad*& cola) {
    if (pos != RAIZ) {
        int posPadre = padre(pos);
        if (cola->array[posPadre]->nivel > cola->array[pos]->nivel || (cola->array[posPadre]->nivel == cola->array[pos]->nivel && cola->array[posPadre]->dato > cola->array[pos]->dato)) {
            intercambiar(pos, posPadre, cola);
            flotar(posPadre, cola);
        
        }
    }
}

void encolar(ColaPrioridad*& cola, int dato, int nivel) {
    cola->tope++;
    nodoDobleDato* nodo = new nodoDobleDato;
    nodo->dato = dato;
    nodo->nivel = nivel;
    cola->array[cola->tope] = nodo;
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
    if (posHijoDer <= cola->tope && (cola->array[posHijoDer]->nivel < cola->array[posHijoIzq]->nivel || (cola->array[posHijoDer]->nivel == cola->array[posHijoIzq]->nivel && cola->array[posHijoDer]->dato < cola->array[posHijoIzq]->dato))) {
        return posHijoDer;
    }
    return posHijoIzq;
}

void hundir(int pos, ColaPrioridad*& cola) {
    if (!esHoja(pos, cola->tope)) {
        int posHijoMenor = obtenerPosHijoMenor(pos, cola);
        if (cola->array[posHijoMenor]->nivel < cola->array[pos]->nivel || (cola->array[posHijoMenor]->nivel == cola->array[pos]->nivel && cola->array[posHijoMenor]->dato < cola->array[pos]->dato)) {
            intercambiar(pos, posHijoMenor, cola);
            hundir(posHijoMenor, cola);
        }
    }
}

nodoDobleDato* desencolar(ColaPrioridad*& cola) {
    nodoDobleDato* retorno = cola->array[RAIZ];
    cola->array[RAIZ] = cola->array[cola->tope];
    cola->tope--;
    hundir(RAIZ, cola);
    return retorno;
}


//Algoritmo ordenacion topológica
void ordenacionTopologica(Grafo* g) {
    ColaPrioridad* cola = inicializarCola(g->vertices);
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
    for (int i = 1; i <= g->vertices; i++) {
        if(arrayEntradas[i] == 0){
            encolar(cola, i, 0);
        }
    }
    while(!esVacio(cola)){
        nodoDobleDato* v = desencolar(cola);
        cout<< v->dato << endl;
        NodoLista* w = g->listaAdy[v->dato];
        while(w!=NULL){
            arrayEntradas[w->dato]--;
            if(arrayEntradas[w->dato] == 0){
                encolar(cola, w->dato, v->nivel+1);
            }
            w = w->sig;
        }
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
