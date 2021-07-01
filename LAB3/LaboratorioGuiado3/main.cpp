#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoGnr.h"

int main()
{
	// construcción aleatoria:
	/*GrafoGnr< int > g_int(10, 0.5);
	cout << "g_int:" << endl;
	cout << g_int << endl;
	std::vector<int> path;

	g_int.obtIdVrtAdys(1, path);

	for (std::vector<int>::const_iterator i = path.begin(); i != path.end(); ++i)
		std::cout << *i << ' ';*/

		// construcción basada en archivo csv:
	ifstream d("grafo_p_z.txt", ios::in);
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