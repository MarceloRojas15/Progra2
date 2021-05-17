#include <iostream>
using namespace std;

#include "LstAdys.h"
#include "TableroReversiHex.h"

enum Ficha { nula, blanca, negra };

int main()
{
	TableroReversiHex* tablero;

	int tamanoN = 0;;
	string nombreJugador1, nombreJugador2;
	bool turnoJugador1 = true;
	int opcion = 0;
	int vecesPreguntado = 0;

	while(opcion != 3){

		std::cout << "\t\t REVERSI HEX\n\n\n\n\MENU PRINCIPAL\n" << endl;
		std::cout << "Bienvenido al menu principal, escoja una de las siguientes opciones.\nPara elegir, recuerde que debe poner el digito numeral que corresponde a la opcion deseada y luego dar enter." << endl;
		std::cout << "\nOpciones\n\n1. Jugar una partida.\n2. Instrucciones.\n3. Salir.\n" << endl;

		std::cin >> opcion;

		switch(opcion){

			case 1:
				std::cout << "\nIntroduzca el tamano del tablero deseado.\n\nRecuerde que solo se pueden crear tableros de tamano: numero impar mayor que 4. Por ejemplo tamano 5, 7, 9, etc.\nEl tablero estandar y recomendado es de tamano 7." << endl;
				std::cin >> tamanoN;

				while (tamanoN % 2 == 0 && vecesPreguntado < 10) {
					std::cout << "\nHa introducido un valor incorrecto, el tablero no puede ser de tamano: " << tamanoN << ".\nPor favor introduzca un numero impar, mayor que 4. Le recomendamos el tamano 7" << endl;
					std::cin >> tamanoN;
					vecesPreguntado++;
				}

				if (vecesPreguntado == 10){
					tamanoN = 7;
					std::cout << "Se ha creado un tablero de tamaño 7, puesto que los valores que se introdujeron han sido invalidos y ha agotado los intentos permitidos. Esperamos que no le moleste que le ayudemos." << endl;
				}

				tablero = new TableroReversiHex(tamanoN);

				std::cout << "\nIntroduzca el nombre del Jugador 1." << endl;
				std::cin >> nombreJugador1;
				std::cout << "\nIntroduzca el nombre del Jugador 2." << endl;
				std::cin >> nombreJugador2;

				std::cout << "\nSe jugara una partida de Reversi Hexagonal. Jugaran " << nombreJugador1 << " vs " << nombreJugador2 << " en un tablero de tamano " << tamanoN << " mucha suerte!\n" << endl;

				while(opcion != 3 && !tablero->verFin()){
					if(turnoJugador1){

						cout << tablero->toString();

						/*si dan opción 1: pedir lugar donde mover, usar blanca o negra (esto del color que usa el jugador que empiece.
						En caso que sea una jugada invalida hacer loop para volver a pedir.
						una vez que se mueve al lugar correcto, entonces turno jugador 1 = false;*/

						std::cout << "\nEs el turno de <<" << nombreJugador1 << ">>, escoja una de las siguientes opciones:" << endl;
						std::cout << "1. Colocar una ficha.\n2. Ver puntaje actual.\n3. Terminar partida (rendirse)\n" << endl;
						std::cin >> opcion;
						int vecesPreguntado = 0; 
						while (opcion < 1 || opcion > 3 && vecesPreguntado < 10) {
							std::cout << "Dicha opcion no exite, por favor introduzca una opcion nuevamente" << endl;
							std::cin >> opcion;
							vecesPreguntado++;
						}

						if (vecesPreguntado == 20) {
							std::cout << "Ha excedido el numero de intentos posibles, ahora es el turno de " << nombreJugador2  << endl;
							turnoJugador1 = false;
							opcion = -1;
						}

						//switch con las opciones
						int columna = 0;
						int posicion = 0;
						switch (opcion) {
							case 1: //Realizar jugada

								std::cout << "Elija la celda donde desee colocar una ficha negra\n" << endl;
								
									std::cout << "En cual columna esta la celda en la que desea poner la ficha negra?" << endl;
									std::cin >> columna;

								
									std::cout << "En cual fila esta la celda en la que desea poner la ficha negra?" << endl;
									std::cin >> posicion;

									while (tablero->verFichaEn(columna, posicion) != TableroReversiHex::Ficha::nula) {
										std::cout << "en esta posición ya hay una ficha, movimiento inválido" << endl;
										std::cout << "En cual columna esta la celda en la que desea poner la ficha negra?n" << endl;
										cin >> columna;
										std::cout << "En cual fila esta la celda en la que desea poner la ficha negra?" << endl;
										std::cin >> posicion;
									}
									if(tablero->validarJugada(columna, posicion, TableroReversiHex::Ficha::negra)) {

										//Este código tiene que ser adaptado para que permita colocar y flanquear una ficha, dado que validarJugada es true.
										//El problema está en que el códigode tableroHex no está completo, ver el ultimo punto del enunciado
										//tablero->colocarFlanqueando(columna, posicion, TableroReversiHex::Ficha::negra);
										tablero->colocarSimple(columna, posicion, TableroReversiHex::Ficha::negra);
									}
									else {
										tablero->colocarSimple(columna, posicion, TableroReversiHex::Ficha::negra);
									}

								break;

							case 2: //mostrar puntuaciones
								//Esto no es un método o algo que se pide en el enunciado, pero es para que se vea bonito o como una posible funcionalidad a futuro.
								break;

							case 3: //rendirse
								std::cout << nombreJugador1 << " se ha rendido. Felicidades al ganador: " << nombreJugador2 << endl;
								return 0;
								break;

							default:
								break;
						}

						turnoJugador1 = false;
					}

					else{
						cout << "\n" << tablero->toString();
						

						/*si dan opción 1: pedir lugar donde mover, usar blanca o negra (esto del color que usa el jugador que empezó de segundo).
						En caso que sea una jugada invalidad hacer loop para volver a pedir.
						una vez que se mueve al lugar correcto, entonces turno jugador 1 = true;*/

						std::cout << "\nEs el turno de <<" << nombreJugador2 << ">>, escoja una de las siguientes opciones:" << endl;
						std::cout << "1. Colocar una ficha.\n2. Ver puntaje actual.\n3. Terminar partida (rendirse)\n" << endl;
						std::cin >> opcion;
						int vecesPreguntado = 0;
						while (opcion < 1 || opcion > 3 && vecesPreguntado < 10) {
							std::cout << "Dicha opcion no exite, por favor introduzca una opcion nuevamente" << endl;
							std::cin >> opcion;
							vecesPreguntado++;
						}

						if (vecesPreguntado == 20) {
							std::cout << "Ha excedido el numero de intentos posibles, ahora es el turno de " << nombreJugador1 << endl;
							turnoJugador1 = true;
							opcion = -1;
						}

						//switch con las opciones

						int columna = 0;
						int posicion = 0;
						switch (opcion) {
						case 1: //Realizar jugada
							std::cout << "Elija la celda donde desee colocar una ficha blanca\n" << endl;

							std::cout << "En cual columna esta la celda en la que desea poner la ficha blanca?" << endl;
							std::cin >> columna;


							std::cout << "En cual fila esta la celda en la que desea poner la ficha blanca?" << endl;
							std::cin >> posicion;

							while (tablero->verFichaEn(columna, posicion) != TableroReversiHex::Ficha::nula) {
								std::cout << "en esta posición ya hay una ficha, movimiento inválido" << endl;
								std::cout << "En cual columna esta la celda en la que desea poner la ficha blanca?n" << endl;
								cin >> columna;
								std::cout << "En cual fila esta la celda en la que desea poner la ficha blanca?" << endl;
								std::cin >> posicion;
							}
							if (tablero->validarJugada(columna, posicion, TableroReversiHex::Ficha::blanca)) {
								//Este código tiene que ser adaptado para que permita colocar y flanquear una ficha, dado que validarJugada es true.
								//El problema está en que el códigode tableroHex no está completo, ver el ultimo punto del enunciado
								//tablero->colocarFlanqueando(columna, posicion, TableroReversiHex::Ficha::blanca);
								tablero->colocarSimple(columna, posicion, TableroReversiHex::Ficha::blanca);
							}
							else {
								tablero->colocarSimple(columna, posicion, TableroReversiHex::Ficha::blanca);
							}
							break;

						case 2: //mostrar puntuaciones

							//Esto no es un método o algo que se pide en el enunciado, pero es para que se vea bonito o como una posible funcionalidad a futuro.

							break;

						case 3: //rendirse
							std::cout << nombreJugador2 << " se ha rendido. Felicidades al ganador: " << nombreJugador1 << endl;
							return 0;
							break;

						default:
							break;
						}
						turnoJugador1 = true;
					}
				}

				break;

			case 2:
				std::cout << "\nEl objetivo en el juego Reversi_Hex es tener la mayor cantidad de fichas propias.\n\nPara ello," << 
				 "los jugadores emplean el flanqueo de una o varias fichas en una misma direccion,\n esto se logra poniendo una ficha de nuestro color en ambos extremos.\n\n"
					<< "Podria verse como convertir las fichas enemigas al rodearlas con nuestras fichas.\n"
					
					<< "Para flanquear estan las siguientes posibilidades: flanqueo diagonal y flanqueo en horizontal. Note que lo anterior es porque las celdas adyacentes estan en estas direcciones." <<endl;
				break;

			case 3:
				std::cout << "Gracias por jugar :D\n" << endl;
				break;

			default:
				std::cout << "El numero introducido no corresponde a ninguna de las opciones\n" << endl;
				break;
			}
	}

	return 0;
}