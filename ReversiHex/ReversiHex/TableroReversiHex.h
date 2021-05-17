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
	//		Las columnas tendrán longitud N y N - 1 intercaladamente.
	//		El tablero hexagonal queda en posición inicial.
	TableroReversiHex(int N);

	// EFE: libera la memoria dinámica asignada al tablero hexagonal.
	// NOTA: es imprescindible, de lo contrario no se liberaría la memoria dinamica asignada.
	~TableroReversiHex();

	/* Métodos observadores públicos */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// EFE: retorna true si la jugada en [c,p] es válida para la fichas del color,
	//		retorna false en caso contrario.
	bool validarJugada(int c, int p, Ficha color) const;

	// EFE: retorna true si el estado actual es un estado final del juego,
	//		retorna false en caso contrario.
	bool verFin() const;

	// REQ: color == blanca || color == negra.
	// EFE: retorna true si las de color no tienen opción para jugar,
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

	/* Métodos modificadores*/
	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// MOD: *this.
	// EFE: coloca en [c,p] la ficha de color lo que implica realizar todos los flanqueos correspondientes.
	void colocarFlanqueando(int c, int p, Ficha color);

	// EFE: retorna una hilera apropiada para desplegar el estado del juego por consola.
	string toString() const;

private:

	/* Métodos observadores de flanqueo privados, se invocarán desde "validarJugada()" */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra).
	// EFE: retorna true si color sí flanquea la dirección dir desde [c,p]; false en caso contrario.
	bool verFlanqueaDir(int dir, int c, int p, Ficha color) const;

	/* Métodos modificadores de flanqueo privados, se invocarán desde "colocar()" */

	// REQ: (0 <= c < N) && (0 <= p < N) && (color == blanca || color == negra) && verFlanqueaDir(c,p).
	// MOD: *this.
	// EFE: flanquea la direccion dir, desde [c,p].
	void flanqueaDir(int dir, int c, int p, Ficha color);

	// REQ: (0 <= c < N) && (0 <= p < N).
	// EFE: retorna lst por referencia con la lista de adyacencias que le corresponde a la casilla [c,p]
	void generarLstAdys(int c, int p, LstAdys& lst);
	
	/* REPRESENTACIÓN DEL TABLERO */

	/* Estructura de la celda de cada tablero */
	struct Celda {
		int c;		// columna en que se ubica la celda
		int p;		// posicion en que se ubica la celda
		Ficha cf;	// color de la ficha ubicada en la celda.
		LstAdys lista_adys; // lista de adyacencias de una casilla del tablero hexagonal
		Celda():c(0), p(0), cf(Ficha::nula) {}; // declaración y definción del constructor estándar de la estructura
		Celda(int c, int p, Ficha color) : c(c), p(p), cf(color) {}; // constructor no estándar
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
	assert((N % 2 == 1)&&(N > 4));		// durante la depuración nos ayuda a encontrar errores
	// se asigna memoria al arreglo principal
	columnas = new Celda*[N];			// se crea un arreglo con N punteros a arreglos de tipo Celda.
	
	// se asigna memoria a los arreglos que representan las columnas
	for (int i = 0; i < N; i++)
		columnas[i] = new Celda[N - i % 2]; // se crea un arreglo en cada posición de columnas, con N o N - 1 posiciones.

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

	if (verFlanqueaDir(0, c, p, color) || verFlanqueaDir(1, c, p, color) || verFlanqueaDir(2, c, p, color) || verFlanqueaDir(3, c, p, color) || verFlanqueaDir(4, c, p, color) || verFlanqueaDir(5, c, p, color)) {
		return true;
	}
	else {
		return false;
	}
}

bool TableroReversiHex::verFin() const
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (columnas[j][i].cf == nula) {
				return false;
			}

			if (i == N - 1 && j % 2 == 0) {
				i++;
			}
		}
	}

	return true;
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
	columnas[c][p] = cld; // OJO: las celdas ya existen por eso es posible la asignación
}

void TableroReversiHex::colocarFlanqueando(int c, int p, Ficha color)
{
	flanqueaDir(0, c, p, color);
	flanqueaDir(1, c, p, color);
	flanqueaDir(2, c, p, color);
	flanqueaDir(3, c, p, color);
	flanqueaDir(4, c, p, color);
	flanqueaDir(5, c, p, color);

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
	bool encuentra_color = false;
	bool encuentra_otro_color = false;
	Ficha otro_color;

	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;


	int i = c;
	int j = p;

	switch (dir) {
	
	case 0: // diagonal ascendente_Der
		

		while (i < N && j >= 0) {

			if(i % 2 == 0) {
				
				if (columnas[i + 1][j - 1].cf == otro_color) {
					encuentra_otro_color = true;
					i++;
					j--;
				}
				else {
					break;
				}
			}
			else {
				if (columnas[i + 1][j].cf == otro_color) {
					encuentra_otro_color = true;
					i += 1;
				}
				else {
					break;
				}
			}
		}


		if (i == N) {
			if (columnas[i][j].cf == color && encuentra_otro_color) {
				return true;
			}
		}else if (i < N) {
			if (columnas[i + 1][j].cf == color && encuentra_otro_color) {
				return true;
			}
		} else {
			return false;
		}
		break;
	
	case 1: // derecha


		while (i < N && (columnas[i + 2][p].cf == otro_color)) {
			encuentra_otro_color = true;
			i += 2;
		}
		if (i == N) {
			if (columnas[i][p].cf == color && encuentra_otro_color) {
				return true;
			}
		}
		if (i < N) {
			if (columnas[i + 2][p].cf == color && encuentra_otro_color) {
				return true;
			}
		}
		else {
			return false;
		}
		break;



	case 2: // diagonal descendente_Der

		while (i < N && j < N && (columnas[i + 1][j].cf == otro_color)) {
			encuentra_otro_color = true;
			i += 1;

			if (i % 2 != 0) {
				j += 1;
			}
		}

		if (i == N) {
			if (columnas[i][j].cf == color && encuentra_otro_color) {
				return true;
			}
		}

		if (i < N) {
			if (columnas[i+1][j].cf == color && encuentra_otro_color) {
				return true;
			}
		}
		else {
			return false;
		}
		break;

	case 3: // diagonal ascendente_Izq


		while (i > 0 && j >= 0) {

			if (i % 2 == 0) {

				if (columnas[i - 1][j - 1].cf == otro_color) {
					encuentra_otro_color = true;
					i--;
					j--;
				}
				else {
					break;
				}
			}
			else {
				if (columnas[i - 1][j].cf == otro_color) {
					encuentra_otro_color = true;
					i--;
				}
				else {
					break;
				}
			}
		}


		if (i == N) {
			if (columnas[i][j].cf == color && encuentra_otro_color) {
				return true;
			}
		}
		else if (i > 0) {
			if (columnas[i - 1][j].cf == color && encuentra_otro_color) {
				return true;
			}
		}
		else {
			return false;
		}
		break;
	
	case 4: // izquierda

		while (i > 0 && (columnas[i - 2][p].cf == otro_color)) {
			encuentra_otro_color = true;
			i -= 2;
		}
		if (i == 0) {
			if (columnas[i][p].cf == color && encuentra_otro_color) {
				return true;
			}
		}
		if (i > 0) {
			if (columnas[i - 2][p].cf == color && encuentra_otro_color) {
				return true;
			}
		}
		else {
			return false;
		}
		break;


	case 5: // diagonal descendente_Izq
		while (i > 0 && j < N && (columnas[i - 1][j].cf == otro_color)) {
			encuentra_otro_color = true;
			i--;

			if (i % 2 != 0) {
				j++;
			}
		}

		if (i == 0) {
			if (columnas[i][j].cf == color && encuentra_otro_color) {
				return true;
			}
		}

		if (i > 0) {
			if (columnas[i - 1][j].cf == color && encuentra_otro_color) {
				return true;
			}
		}
		else {
			return false;
		}
		break;
	
	default:
		break;
	}
}


void TableroReversiHex::flanqueaDir(int dir, int c, int p, TableroReversiHex::Ficha color)
{
	assert((0 <= c) && (c < N + 1));
	assert((0 <= p) && ((c % 2 == 0) && (p < N) || (c % 2 == 1) && (p < N - 1)));
	assert(color != nula);
	assert(verFlanqueaDir(dir, c, p, color));

	Ficha otro_color;
	int cc = 0;
	int pp = 0;

	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;

	// código para flanquear en la dirección dir:

	switch (dir) {
		case 0: // diagonal ascendente_Der

			pp = 0;

			if (c % 2 == 0) {
				pp = p - 1;
				cc = c + 1;
			}
			else {
				pp = p;
				cc = c + 1;
			}


			
			while ((pp >= 0) && (cc < N-1) && (columnas[cc][pp].cf == otro_color))
			{
				columnas[cc][pp].cf = color;
				if (cc % 2 == 0) {
					pp--;
				}
				cc = cc + 2;
			}



			break;
		case 1: // derecha
			cc = c + 2;
			while ((cc < N) && columnas[cc][p].cf == otro_color) {
				columnas[cc][p].cf = color;
				cc = cc + 1;
			}
			break;
		
		
		case 2: // diagonal descendente_Der

			if (c % 2 == 0) {
				pp = p;
				cc = c + 1;
			}
			else {
				cc = c + 1;
			}


			while ((pp < N-1) && (cc < N-1) && (columnas[cc][pp].cf == otro_color))
			{
				columnas[cc][pp].cf = color;
				if (cc % 2 != 0) {
					pp++;
				}
				cc++;
			}
			break;
		
		case 3: // diagonal descendente_Izq


			if (c % 2 == 0) {
				pp = p;
				cc = c - 1;
			}
			else {
				cc = c - 1;
			}


			while ((pp < N) && (cc >= 0) && (columnas[cc][pp].cf == otro_color))
			{
				columnas[cc][pp].cf = color;
				if (cc % 2 != 0) {
					pp++;
				}
				cc = cc -2;
			}

			break;
		
		case 4:// izquierda
			cc = c - 2;
			while ((cc > 0) && columnas[cc][p].cf == otro_color) {
				columnas[cc][p].cf = color;
				cc = cc - 2;
			}
			break;


		case 5: //diagonal ascendente_Izq
			
			pp = 0;

			if (c % 2 == 0) {
				pp = p - 1;
				cc = c - 1;
			}
			else {
				pp = p;
				cc = c - 1;
			}
			
			while ((pp >= 0) && (cc >= 0) && (columnas[cc][pp].cf == otro_color))
			{
				columnas[cc][pp].cf = color;
				if (cc % 2 == 0) {
					pp--;
				}
				cc = cc - 1;
			}
			break;
	}
}

void TableroReversiHex::generarLstAdys(int c, int p, LstAdys& lst)
{
	// En vez de logica condicional compleja se abarcan todos los casos con la matriz deltas.
	int deltas[6][3] = { {+1, -1, 0},{2, 0, 0}, {+1, 0, +1}, {-1, 0, +1}, {-2, 0, 0}, {-1, -1, 0} };
	int p_max = (c % 2 == 0) ? N : N - 1;
	int delta_c = 0;	// cambio en columna para obtener una nueva direccion
	int delta_p = 0;	// cambio en posicion para obtener una nueva direccion
	LstAdys::DatosAdy datos_ady; // OJO: se puede acceder porque un tipo público en LstAdys, pero siempre respeta su encapsulamiento.

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