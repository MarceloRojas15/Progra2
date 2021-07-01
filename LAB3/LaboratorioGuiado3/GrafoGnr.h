#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <assert.h>     /* assert */

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

template < typename T >
class GrafoGnr {

    // Representa un grafo genérico con vértices de tipo T.
    /* Supuestos sobre el tipo T:
    * T() está definido.
    * T(const T&) está definido.
    * T operator=(const T& t) está definido.
    * friend ostream& operator<<(ostream& o, const T& t) plantilla de operador sobrecargado.
    */

public:

    /* CONSTRUCTORES */

    // DADOS:
    // N la cantidad de vértices o nodos.

    // REQ: 0 < p < 1.
    // Construye un GrafoGnr con N vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos vértices es igual a p.
    GrafoGnr(int N, double p);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices se identifican con números de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con T().
    GrafoGnr(ifstream& archivo);

    // Construye una copia idéntica a orig.
    GrafoGnr(const GrafoGnr< T >& orig);

    // Destructor
    ~GrafoGnr();

    /* OBSERVADORES */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el GrafoGnr.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de vértices adyacentes a idVrt en el GrafoGnr.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    T operator[](int idVrt) const;

    // EFE: retorna el total de adyacencias en el GrafoGnr.
    int obtTotAdys() const;

    // EFE: retorna el total de vértices en el GrafoGnr.
    int obtTotVrt() const;

    // REQ: 0 <= idVrt < N.
    // EFE: Retorna por "caminosMinimos" los caminos más cortos entre idVrtO y todos los demás vértices.
    // REF1: https://es.wikipedia.org/wiki/Algoritmo_de_Dijkstra
    // REF2: https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
    // SUPUESTO#1: El grafo es conectado, por lo que caminosMinimos.size() == N - 1.
    // SUPUESTO#2: La distancia entre dos vértices directamente conectados es siempre uno.
    void obtCaminosMinimos(int idVrtO, vector< vector< int >>& caminosMinimos) const;

    // REQ: 0 <= idVrt < N.
    // EFE: Retorna por recorrido la secuencia de idVrt por anchura primero.
    // REF: https://es.wikipedia.org/wiki/B%C3%BAsqueda_en_anchura
    // SUPUESTO: que grafo es conectado, por lo que recorrido.size() == N.
    void obtRecorridoXanchura(int idVrtO, vector< int >& recorrido) const;

    // EFE: permite que el digrafo sea consumido por un flujo mediante el operator<<.
    // NOTA: es una función externa a la clase que por hacer acceso a los atributos privados
    //       del conjunto se debe declarar como friend. Sustituye a toString().
    template < typename V >
    friend ostream& operator<<(ostream& o, const GrafoGnr< V >& g);

    /* MODIFICADORES */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto invocador.
    T& operator[](int idVrt);

private:

    template < typename V >
    struct Nodo {
        V v;
        list< int > listaAdy;
        Nodo() : v() {}; // constructor estándar de Nodo
        Nodo(const V& vn) : v(vn) {}; // constructor con dato de vértice
        Nodo(const Nodo< V >& no) : v(no.v), listaAdy(no.listaAdy) {}; // constructor de copias de Nodo
    };

    vector< Nodo< T >> nodos; // nodos con vértices

};

template < typename T >
GrafoGnr< T >::GrafoGnr(int N, double p) {
    nodos.resize(N);
    // se genera una semilla para la secuencia de números al azar:
    srand(time(NULL));

    // se multiplica por 1.0 para obtener un double

    //Empezar con el vertice 0, hasta llegar al vertice N.
    //Agregar adyacencias aleatorias para cada vertice.
    //Si se agrega por ejemplo adyacencia entre 0 y 2, entonces agregar entre 2 y 0

    for (int vertice = 0; vertice < N; vertice++) {

        for (int i = 0; i < N; i++) {
            double p_ady = (rand() / (1.2 * RAND_MAX));
            if (i == vertice) {
                continue;
            }
            if (p < p_ady) {
                nodos[vertice].listaAdy.push_back(i);
                nodos[i].listaAdy.push_back(vertice);
            }
        }
    }


    for (int i = 0; i < N; i++) {
        nodos[i].listaAdy.sort();
        nodos[i].listaAdy.unique();
    }
}

template < typename T >
GrafoGnr< T >::GrafoGnr(ifstream& archivo) {
    string entrada = "";
    std::getline(archivo, entrada);
    nodos.resize(stoi(entrada));
    vector <string> tokens;
    
    for (int vertice = 0; vertice < nodos.size(); vertice++) {
        tokens.empty();
        entrada = "";
        std::getline(archivo, entrada);

        // stringstream class check1
        stringstream check1(entrada);
        stringstream check2(entrada);

        string intermediate;
        string intermediate2;
            while (getline(check2, intermediate, ',')) {
                nodos[vertice].listaAdy.push_back(stoi(intermediate));
            }

    }
 

    /*while (!archivo.eof()) {
        getline(archivo, entrada);
        cout << entrada <<  endl;
    }*/
}

template < typename T >
GrafoGnr< T >::GrafoGnr(const GrafoGnr< T >& orig) {

}

template < typename T >
GrafoGnr< T >::~GrafoGnr() {
}

//Si existe vertice, se devuelve true.
template < typename T >
bool GrafoGnr< T >::xstVrt(int idVrt) const {
    return (idVrt <= nodos.size()) ? true : false;
}


//Existe adyacencia entre vértice A y B (Existe un camino)
template < typename T >
bool GrafoGnr< T >::xstAdy(int idVrtO, int idVrtD) const {

    return ((std::find(nodos[idVrtO].listaAdy.begin(), nodos[idVrtO].listaAdy.end(), idVrtD)) != nodos[idVrtO].listaAdy.end());
}


//Retorna en el vector RSP, los identificadores de cada uno de los vectices que son adyacentes al Vertice indicado (vertice idVrt)
//OSEA COPIAR LA LISTA DE ADYACENCIA? de lista a vector?
template < typename T >
void GrafoGnr< T >::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
    
    for (std::list<int>::const_iterator it = nodos[idVrt].listaAdy.begin(); it != nodos[idVrt].listaAdy.end(); ++it) {
        rsp.push_back(*it);
    }
}

//Se retorna el número de vertices que son adyacentes al vertice parámetro. (con cuantos vertices tengo camino?)
template < typename T >
int GrafoGnr< T >::obtCntVrtAdys(int idVrt) const {
    return nodos[idVrt].listaAdy.size();
}

//retorna el vertice que se encuentra en el indice indicado por parámetro. Const
template < typename T >
T GrafoGnr< T >::operator[](int idVrt) const {
    T v;
    v = nodos[idVrt];
    return v;
}

//recorre todo el grafo y retorna el número total de adyacencias (suma de las adyacencias de los vertices 0+1+2+....+ N-1)
template < typename T >
int GrafoGnr< T >::obtTotAdys() const {
    int resultado = 0;

    for (int i = 0; i < nodos.size(); i++) {
        resultado += obtCntVrtAdys(i);
    }

    return resultado/2;
}

//retorna el total de vertices
template < typename T >
int GrafoGnr< T >::obtTotVrt() const {
    return nodos.size();
}

//Metodo del algoritmo de Dijkstra
template < typename T >
void GrafoGnr< T >::obtCaminosMinimos(int idVrtO, vector< vector< int >>& caminosMinimos) const {

}

template < typename T >
void GrafoGnr< T >::obtRecorridoXanchura(int idVrtO, vector< int >& recorrido) const {

}


//retorna el vertice que se encuentra en el indice indicado por parámetr... por referencia para que pueda modificarse
template < typename T >
T& GrafoGnr< T >::operator[](int idVrt) {
    T* v_p = new T();		// OJO: fuga de memoria! Too Bad! #Reparado, creo
    v_p = nodos[idVrt];
    return v_p;
}

template < typename V >
ostream& operator<<(ostream& o, const GrafoGnr< V >& g) {
    ostringstream fs;

    for (auto p : g.nodos) {
        int cnt = p.listaAdy.size();
        int i = 0;
        for (auto ady : p.listaAdy) {
            fs << ady;
            if (i < cnt - 1)
                fs << ',';
            i++;
        }
        fs << endl;
    }
    o << fs.str();
    return o;
}
