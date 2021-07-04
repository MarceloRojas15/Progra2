#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoGnr.h"

int main()
{
	// construcción aleatoria:
	GrafoGnr< int > g_int(10, 0.5);
	std::cout << "g_int:" << endl;
	std::cout << g_int << endl;
	

	
	// construcción basada en archivo csv:
	ifstream d("grafo_p.txt", ios::in);
	if (!d) {
		cout << "problemas para abrir el archivo grafo_p.txt" << endl;
		exit(1);
	}

	GrafoGnr< int > g_int1(d);
	cout << "g_int1:" << endl;
	cout << g_int1 << endl;
	
	/*vector< vector< int >> caminosMinimos;
	g_int1.obtCaminosMinimos(0, caminosMinimos);

	vector< int > recorrido;
	g_int1.obtRecorridoXanchura(0, recorrido);*/
	return 0;
}