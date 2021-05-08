#pragma once

#include <memory>	// para usar los punteros inteligentes de tipo shared_ptr
#include <sstream>  // permite usar ostringstream en "toString()".

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
	struct Celda {
		int dir; // representa una dirección de adyacencia entre 0 a 5
		int c;	 // columna de la adyacente
		int p;	 // posicion de la adyacente
		std::shared_ptr< Celda > prx;	// puntero inteligente a la próxima celda
		Celda() : dir(0), c(0), p(0), prx(0) {};
		Celda(int d, int c, int p) : dir(d), c(c), p(p) {};
	};

	std::shared_ptr< Celda > inicio;
	std::shared_ptr< Celda > fin; // para agregar al final
};

LstAdys::LstAdys()
{
	inicio = 0;
	fin = 0;
}

void LstAdys::obtDatosAdy(DatosAdy& dady) const
{
	std::shared_ptr< Celda > cursor = inicio;
	int rsl = 0; // suponemos que la insercion es valida, si no, cambia a -1
	while ((cursor != 0) && (cursor->dir != dady.dir)) {
		 cursor = cursor->prx;
	}
	if (cursor == 0)
		dady.dir = -1; // no se pudo encontrar una adyacencia con la direccion en dady.dir
	else if (cursor->dir == dady.dir) {
		dady.c = cursor->c;
		dady.p = cursor->p;
	}
}

string LstAdys::toString() const
{
	ostringstream salida;
	salida << "{ ";
	std::shared_ptr< Celda > cursor = inicio;
	while (cursor != 0) {
		salida << cursor->dir << " ";
		salida << "[ " << cursor->c << "," << cursor->p << " ]";
		if (cursor->prx != 0)
			salida << ",";
		cursor = cursor->prx;
	}
	salida << " }" << endl;
	return salida.str();
}

void LstAdys::agrAdyacencia(DatosAdy& dady)
{
	std::shared_ptr< Celda > cursor = inicio;
	int rsl = 0; // suponemos que la insercion es valida, si no, cambia a -1
	while ((cursor != 0) && (rsl != -1)) {
		if (cursor->dir == dady.dir) {		// OJO: ya existe una adyacencia con la direccion dady.dir
			rsl = -1;
			dady.dir = -1;
		}
		cursor = cursor->prx;
	}
	if (rsl != -1) {
		std::shared_ptr< Celda > nueva_celda_p = std::shared_ptr< Celda >(new Celda(dady.dir, dady.c, dady.p));
		if (inicio == 0) {
			inicio = nueva_celda_p;
			fin = nueva_celda_p;
		}
		else {
			fin->prx = nueva_celda_p;
			fin = nueva_celda_p;
		}
	}
}