#pragma once

#include <sstream>  // permite usar ostringstream en "toString()".
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class LstAdys
{
public:

	// se usa para pasar y recibir datos de adyacencias contenidas en la lista.
	struct DatosAdy {
		int dir;
		int c;
		int p;
		DatosAdy() : dir(0), c(0), p(0) {};
		DatosAdy(int d, int c, int p) : dir(d), c(c), p(p) {};
		bool operator==(const DatosAdy& ady) const { return dir == ady.dir; };
	};

	// EFE: construye una lista de adyacencias vacia. El destructor no es necesario porque se usan shared_ptr
	LstAdys();
	
	// REQ: dady.dir exista como dir en alguna de las adyacencias de la lista.
	// EFE: retorna por referencia los datos de una adyacencia cuya direccion es dir.
	//		retorna dady.dir == -1 si la direccion dady.dir no existe en la lista.
	void obtDatosAdy(DatosAdy& dady) const;

	// EFE: retorna una hilera con las coordenadas de cada dirección: {#d [p,c],...}
	string toString() const;

	// REQ: (0 <= dady.dir) && (dady.dir < 6) && () && (dady.c < N) && (dady.p < N - 1)
	// MOD: *this
	// EFE: agrega una nueva adyacencia al final de la lista con los datos en dady.
	// NOTA: retorna dady.dir == 0 si la insercion es valida y dady.dir = -1 si no es valida y ha sido omitida.
	void agrAdyacencia(DatosAdy& dady);

private:

	list< DatosAdy > lista;
};

LstAdys::LstAdys()
{
}



void LstAdys::obtDatosAdy(DatosAdy& dady) const
{
	bool encontrado = 0;

	for (auto iter : lista) {
		if (iter.dir == dady.dir) {
			dady.c = iter.c;
			dady.p = iter.p;
			encontrado = 1;
		}
		if (encontrado) {
			dady.dir = -1;
			break;
		}
	}
}

string LstAdys::toString() const
{
	ostringstream salida;
	salida << "{ ";

	for (auto iter1 : lista) {
		salida << iter1.dir << " ";
		salida << "[ " << iter1.c << "," << iter1.p << " ]";
		salida << ",";
	}
	salida << " }" << endl;
	return salida.str();
}

void LstAdys::agrAdyacencia(DatosAdy& dady)
{

	int debeAgregar = 0; // suponemos que la insercion es valida, si no, cambia a -1
	
	for (auto iter2 : lista) {
		if (iter2.dir == dady.dir) {
			debeAgregar = -1;
			dady.dir = -1;
		}
	}

	if (debeAgregar != -1) {
		lista.push_back(dady);
	}
}