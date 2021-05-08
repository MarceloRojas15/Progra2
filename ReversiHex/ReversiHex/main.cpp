#include <iostream>
using namespace std;

#include "LstAdys.h"
#include "TableroReversiHex.h"

enum Ficha { nula, blanca, negra };

int main()
{
	int N = 5;
	TableroReversiHex trh(N);

	cout << "Contenido de la matriz hexagonal: " << endl;
	cout << trh.toString() << endl;
	cout << "Adyacencias de la matriz hexagonal: " << endl;
	cout << trh.adysToString() << endl;
	return 0;
}

