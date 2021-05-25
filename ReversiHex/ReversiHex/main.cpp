#include <iostream>
using namespace std;

#include "TableroReversiHex.h"
#include "LstAdys.h"

// REQ: que en nombre se guarde alguno de los nombres de los jugadores.
// MOD: c y p
// EFE: retorna por referencia la (c,p) de la jugada nueva del jugador correspondiente a nombre.
void pideJugada(const TableroReversiHex& tr, int N, string nombre, TableroReversiHex::Ficha color, int& c, int& p);

int main()
{
	string nombre_negras = "";
	string nombre_blancas = "";
	int N = -1;

	while ((N % 2 == 0) || (N < 5))
	{
		cout << "Digite la cantidad mAxima de posiciones que debe ser impar y mayor que cuatro: ";
		cin >> N;
		cout << endl;
	}

	TableroReversiHex trh(N); 

	while (nombre_negras == "")
	{
		cout << "Digite el nombre de quien juega las NEGRAS: ";
		cin >> nombre_negras;
	}

	while (nombre_blancas == "")
	{
		cout << "Digite el nombre de quien juega las BLANCAS: ";
		cin >> nombre_blancas;
	}

	cout << trh.toString() << endl << endl;
	while (!trh.verFin())
	{
		int f, c = 0;
		pideJugada(trh, N, nombre_negras, TableroReversiHex::negra, f, c);
		trh.colocarFlanqueando(f, c, TableroReversiHex::negra);
		cout << trh.toString() << endl << endl;
		pideJugada(trh, N, nombre_blancas, TableroReversiHex::blanca, f, c);
		trh.colocarFlanqueando(f, c, TableroReversiHex::blanca);
		cout << trh.toString() << endl << endl;
	}
	return 0;
}

void pideJugada(const TableroReversiHex& tr, int N, string nombre, TableroReversiHex::Ficha color, int& c, int& p)
{
	bool validez = false;
	while ((c < 0) || (p < 0) || !validez || ((c % 2 == 0) && ((c > N + 1) || (p >= N)))  || (c % 2 == 1) && ((c > N) || (p >= N - 1)) )
	{
		cout << nombre << " por favor digite la columna de su jugada: "; cin >> c;
		cout << nombre << " por favor digite la posicion de su jugada: "; cin >> p;
		cout << endl;
		validez = tr.validarJugada(c, p, color);
		if (!validez)
			cout << nombre << ": SU JUGADA NO ES VALIDA!" << endl;
	}
}
