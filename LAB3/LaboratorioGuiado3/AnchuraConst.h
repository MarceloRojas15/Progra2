#pragma once

#include "GrafoGnr.h"

template< typename T >
class AnchuraConst {

    // Representa un iterador sobre un GrafoGnr que realiza
    // un recorrido por anchura sobre el grafo asociado.
    // REF: https://es.wikipedia.org/wiki/B%C3%BAsqueda_en_anchura

    friend class GrafoGnr< T >;

public:
    AnchuraConst(const AnchuraConst& orig);
    virtual ~AnchuraConst();

    // EFE: avanza *this a la siguiente posición válida.
    AnchuraConst& operator++();

    // EFE: si *this != end(), retorna referencia de objeto de tipo T apuntado.
    const T& operator*();

    // EFE: si *this != end(), retorna puntero a objeto de tipo T apuntado.    
    const T* operator->();

    // EFE: retorna true si el estado de *this es idéntico al de o.
    bool operator==(const AnchuraConst< T >& o);

    // EFE: retorna true si el estado de *this es diferente al de o.
    bool operator!=(const AnchuraConst< T >& o);

    // EFE: copia o en *this.
    void operator=(const AnchuraConst< T >& o);

private:

    // EFE: construye una instancia asociada al grafo g.
    // El recorrido iniciará en un vértice escogido al azar.
    // Sólo puede ser invocado por GrafoGnr::begin() y por
    // GrafoGnr::end().
    AnchuraConst(const GrafoGnr< T >& g);

    // EFE: construye una instancia asociada al grafo g.
    // El recorrido iniciará en el vértice identificado por idVrtO.
    // Sólo puede ser invocado por GrafoGnr::begin(string).    
    AnchuraConst(const GrafoGnr< T >& G, int idVrtO);
};


template< typename T >
AnchuraConst< T >::AnchuraConst(const GrafoGnr< T >& g) {
}

template< typename T >
AnchuraConst< T >::AnchuraConst(const GrafoGnr< T >& g, int idVrtI) {
/*
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    */
}


template< typename T >
AnchuraConst< T >::AnchuraConst(const AnchuraConst& orig) {
}

template< typename T >
AnchuraConst< T >::~AnchuraConst() {
}

template< typename T >
AnchuraConst< T >& AnchuraConst< T >::operator++() {
}

template< typename T >
const T& AnchuraConst< T >::operator*() {
}

template< typename T >
const T* AnchuraConst< T >::operator->() {
}

template< typename T >
bool AnchuraConst< T >::operator==(const AnchuraConst< T >& o) {
	return true;
}

template< typename T >
bool AnchuraConst< T >::operator!=(const AnchuraConst< T >& o) {
	return true;
}

template< typename T >
void AnchuraConst< T >::operator=(const AnchuraConst< T >& o) {
}
