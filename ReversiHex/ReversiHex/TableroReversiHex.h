#pragma once

#define DEBUG
#include <assert.h>     /* para usar assert */
#include <string>
#include <sstream> // permite usar ostringstream en "toString()".
using namespace std;

#include "LstAdys.h"

class TableroReversiHex
{
public:
	enum Ficha { nula, blanca, negra };

	// REQ: (N % 2 == 1) && (N > 4).
	// EFE: Construye un tablero de ReversiHex con N columnas.
	//		Las columnas tendr�n longitud N y N - 1 intercaladamente.
	//		El tablero hexagonal queda en posici�n inicial.
	TableroReversiHex(int N);

	// EFE: libera la memoria din�mica asignada al tablero hexagonal.
	// NOTA: es imprescindible, de lo contrario no se liberar�a la memoria dinamica asignada.
	~TableroReversiHex();

	/* M�todos observadores p�blicos */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// EFE: retorna true si la jugada en [c,p] es v�lida para la fichas del color,
	//		retorna false en caso contrario.
	bool validarJugada(int c, int p, Ficha color) const;

	// EFE: retorna true si el estado actual es un estado final del juego,
	//		retorna false en caso contrario.
	bool verFin() const;

	// REQ: color == blanca || color == negra.
	// EFE: retorna true si las de color no tienen opci�n para jugar,
	//	 false en caso contrario.
	bool verPasan(Ficha color) const;

	// REQ:(0 <= c < N) && (0 <= p < N).
	// EFE: retorna el valor en [c,p].
	Ficha verFichaEn(int c, int p) const;

	// EFE: retorna una hilera con las adyacencias de cada [c,p].
	string adysToString() const;

	// REQ: (0 <= c < N) && (0 <= p < N).
	// MOD: *this.
	// EFE: coloca en [c,p] la ficha de color.
	void colocarSimple(int c, int p, Ficha color);

	/* M�todos modificadores*/
	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// MOD: *this.
	// EFE: coloca en [c,p] la ficha de color lo que implica realizar todos los flanqueos correspondientes.
	void colocarFlanqueando(int c, int p, Ficha color);

	// EFE: retorna una hilera apropiada para desplegar el estado del juego por consola.
	string toString() const;

//private:

	/* M�todos observadores de flanqueo privados, se invocar�n desde "validarJugada()" */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// EFE: retorna true si color s� flanquea la direcci�n dir desde [c,p]; false en caso contrario.
	bool verFlanqueaDir(int dir, int c, int p, Ficha color) const;

	/* M�todos modificadores de flanqueo privados, se invocar�n desde "colocar()" */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra) && verFlanqueaDir(c,p).
	// MOD: *this.
	// EFE: flanquea la direccion dir, desde [c,p].
	void flanqueaDir(int dir, int c, int p, Ficha color);

	// REQ: (0 <= c < N) && (0 <= p < N).
	// EFE: retorna lst por referencia con la lista de adyacencias que le corresponde a la casilla [c,p]
	void generarLstAdys(int c, int p, LstAdys& lst);
	
	/* REPRESENTACI�N DEL TABLERO */

	/* Estructura de la celda de cada tablero */
	struct Celda {
		int c;		// columna en que se ubica la celda
		int p;		// posicion en que se ubica la celda
		Ficha cf;	// color de la ficha ubicada en la celda.
		LstAdys lista_adys; // lista de adyacencias de una casilla del tablero hexagonal
		Celda():c(0), p(0), cf(Ficha::nula) {}; // declaraci�n y definci�n del constructor est�ndar de la estructura
		Celda(int c, int p, Ficha color) : c(c), p(p), cf(color) {}; // constructor no est�ndar
	};

	/* Variables del tablero*/
	int N;			// guarda la cantidad maxima de columnas que debe ser impar.
	
	/* puntero a puntero */
	// Representa la cantidad variable de N columnas, cada una, intercaladamente, con N o N - 1 posiciones.
	// Puntero a un arreglo simple de punteros por eso "**".
	Celda** columnas;
};

/* CODIGO DE LOS METODOS */

TableroReversiHex::TableroReversiHex(int N)
{
	this->N = N;
	assert((N % 2 == 1)&&(N > 4));		// durante la depuraci�n nos ayuda a encontrar errores
	// se asigna memoria al arreglo principal
	columnas = new Celda*[N];			// se crea un arreglo con N punteros a arreglos de tipo Celda.
	
	// se asigna memoria a los arreglos que representan las columnas
	for (int i = 0; i < N; i++)
		columnas[i] = new Celda[N - i % 2]; // se crea un arreglo en cada posici�n de columnas, con N o N - 1 posiciones.

	// se crean las adyacencias de cada [columna, posicion]
	for (int c = 0; c < N; c++) {
		int p_max = (c % 2 == 0) ? N : N - 1;
		for (int p = 0; p < p_max; p++)
			 generarLstAdys(c, p, columnas[c][p].lista_adys);
	}

	if ((N-5) % 4 == 0) {

		int indicador = (N - 5) / 4;
		colocarSimple(2 * indicador, (2 * indicador)+2, negra);
		colocarSimple(2 * indicador + 1, (2 * indicador) + 2 - 1, blanca);
		colocarSimple(2 * indicador + 3, (2 * indicador) + 2 - 1, negra);
		colocarSimple(2 * indicador + 4, (2 * indicador) + 2, blanca);
		colocarSimple(2 * indicador + 1, (2 * indicador) + 2, blanca);
		colocarSimple(2 * indicador + 3, (2 * indicador) + 2, negra);
	}

	if ((N - 7) % 4 == 0) {

		int indicador = (N - 7) / 4;

		colocarSimple(2 * indicador +2, (2 * indicador) +3, negra);
		colocarSimple(2 * indicador +3, (2 * indicador) +2, negra);
		colocarSimple(2 * indicador +4, (2 * indicador) +3, blanca);
		colocarSimple(2 * indicador +3, (2 * indicador) +3, blanca);
	}
}

TableroReversiHex::~TableroReversiHex()
{
	// primero se libera la memoria de cada columna
	for (int i = 0; i < N; i++) {
		delete[] columnas[i];
	}
	// luego se libera la memoria del arreglo que guarda las columnas
	delete[] columnas;
}

bool TableroReversiHex::validarJugada(int c, int p, TableroReversiHex::Ficha color) const
{
	return true;
}

bool TableroReversiHex::verFin() const
{
	return false;
}

bool TableroReversiHex::verPasan(Ficha color) const
{
	return false;
}

TableroReversiHex::Ficha TableroReversiHex::verFichaEn(int c, int p) const
{
	assert((0 <= c) && (c < N));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	return columnas[c][p].cf;
}

string TableroReversiHex::adysToString() const
{
	ostringstream salida;
	// se generan las hileras con las adyacencias de cada [columna,posicion]
	for (int c = 0; c < N; c++) {
		int posicion_max = (c % 2 == 0) ? N : N - 1;
		for (int p = 0; p < posicion_max; p++) {
			salida << "Adyacencias de [" << c << "," << p << "]: ";
			salida << columnas[c][p].lista_adys.toString();
		}
		salida << endl;
	}
	return salida.str();
}

void TableroReversiHex::colocarSimple(int c, int p, Ficha color)
{
	assert((0 <= c) && (c < N));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	Celda cld;
	cld.c = c;
	cld.p = p;
	cld.cf = color;
	columnas[c][p] = cld; // OJO: las celdas ya existen por eso es posible la asignaci�n
}

void TableroReversiHex::colocarFlanqueando(int f, int c, Ficha color)
{

}

string TableroReversiHex::toString() const
{
	string sepr_ext_arriba_base = string(" /-\\");
	string sepr_ext_abajo_base = string(" \\-/");
	string sepr_ext_arriba = "   ";
	string sepr_ext_abajo = "   ";
	string sepr_int_arriba_base_1 = string("-\\");
	string sepr_int_arriba_base_2 = string("-/");
	string sepr_int_arriba = string(" /");
	string sepr_int_abajo_base_1 = string("-/");
	string sepr_int_abajo_base_2 = string("-\\");
	string sepr_int_abajo = string(" \\");
	string indices = "     0 1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d e f g h i j k l m n o p q r s t u v w x y z";
	string nums_columnas = "";
	ostringstream salida; // es un buffer de memoria con caracteres listos para ser desplegados por consola

	/* se preparan todas las hileras */
	for (int i = 0; i < (N + 1) / 2; i++) {
		sepr_ext_arriba = sepr_ext_arriba + sepr_ext_arriba_base;
		sepr_ext_abajo = sepr_ext_abajo + sepr_ext_abajo_base;
	}
	for (int i = 0; i < (N + 1) / 2; i++) {
		sepr_int_arriba = sepr_int_arriba + ((i % 2 == 0) ? sepr_int_arriba_base_1 : sepr_int_arriba_base_2);
	}
	for (int i = 0; i < (N + 1) / 2; i++) {
		sepr_int_abajo = sepr_int_abajo + ((i % 2 == 0) ? sepr_int_abajo_base_1 : sepr_int_abajo_base_2);
	}
	nums_columnas = indices.substr(0, (5 + 2 * (N)));

	/* se construye la salida */
	salida << nums_columnas << endl;
	for (int p = 0; p < N; p++)
	{
		salida << sepr_ext_arriba << endl;
		salida << "  ";
		salida << indices[5 + 2 * p] << "|";
		for (int c = 0; c < N; c = c + 2)
		{
			salida << " ";
			if (columnas[c][p].cf != nula)
				salida << ((columnas[c][p].cf == negra) ? "N" : "B");
			else salida << " ";
			salida << " |";
		}
		salida << endl;
		salida << sepr_ext_abajo;
		if (p < N - 1) {
			salida << endl;
			salida << "  ";
			salida << indices[5 + 2 * p] << "  |";
			for (int c = 1; c < N - 1; c = c + 2)
			{
				salida << " ";
				if (columnas[c][p].cf != nula)
					salida << ((columnas[c][p].cf == negra) ? "N" : "B");
				else salida << " ";
				salida << " |";
			}
		}
		salida << endl;
	}
	return salida.str(); // se accede el contenido del buffer y se retorna como hilera
}

bool TableroReversiHex::verFlanqueaDir(int dir, int c, int p, Ficha color) const
{
	assert((0 <= c) && (c < N));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	assert(color != nula);
	bool resultado = false;

	// c�digo para determinar si hay flanqueo o no

	return resultado;
}

void TableroReversiHex::flanqueaDir(int dir, int c, int p, TableroReversiHex::Ficha color)
{
	assert((0 <= c) && (c < N + 1));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	assert(color != nula);
	assert(verFlanqueaDir(dir, c, p, color));

	Ficha otro_color;

	// determina cu�l es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;

	// c�digo para flanquear en la direcci�n dir:

}

void TableroReversiHex::generarLstAdys(int c, int p, LstAdys& lst)
{
	// En vez de logica condicional compleja se abarcan todos los casos con la matriz deltas.
	int deltas[6][3] = { {+1, -1, 0},{2, 0, 0}, {+1, 0, +1}, {-1, 0, +1}, {-2, 0, 0}, {-1, -1, 0} };
	int p_max = (c % 2 == 0) ? N : N - 1;
	int delta_c = 0;	// cambio en columna para obtener una nueva direccion
	int delta_p = 0;	// cambio en posicion para obtener una nueva direccion
	LstAdys::DatosAdy datos_ady; // OJO: se puede acceder porque un tipo p�blico en LstAdys, pero siempre respeta su encapsulamiento.

	// se consideran todas las direcciones posibles:
	for (int dir = 0; dir < 6; dir++) {
		delta_c = deltas[dir][0];
		delta_p = deltas[dir][1 + (c % 2)];
		if ((p == N - 1) && ((dir == 2) || (dir == 3)))		// identifica posiciones altas de cada columna
			delta_p++;
		if ((0 <= (c + delta_c)) && ((c + delta_c) < N) && (0 <= (p + delta_p)) && ((p + delta_p) < N)) {
			datos_ady.dir = dir;
			datos_ady.c = c + delta_c;
			datos_ady.p = p + delta_p;
			lst.agrAdyacencia(datos_ady);
		}
	}
}
