#include "pch.h"
#include "../ReversiHex/TableroReversiHex.h"

class PruebasTableroReversiHex : public ::testing::Test {
protected:
	TableroReversiHex t_5;
	TableroReversiHex t_7;


	PruebasTableroReversiHex();
};

PruebasTableroReversiHex::PruebasTableroReversiHex() :t_5(5), t_7(7) {
}


		//**************************************************//
		//													//
		//					Casos de Prueba					//
		//													//
		//**************************************************//

//REVISAR IMAGEN/SCREENSHOT en la carpeta de ReversiHex

//*************************//
// Pruebas del constructor //
//*************************//


// El siguiente código es la prueba que se realiza al constructor del tablero.
// Esta prueba corresponde a lo solicitado en el punto 7 del enunciado.

// Caso T_5, se prueba el tablero "t_5" con tamaño n=5
TEST_F(PruebasTableroReversiHex, InicializacionCorrecta_T_5)
{	
	ASSERT_EQ(t_5.verFichaEn(3, 2), TableroReversiHex::Ficha::negra);
	ASSERT_EQ(t_5.verFichaEn(1, 1), TableroReversiHex::Ficha::blanca);
}

// Caso T_7, se prueba el tablero T_7 de tamaño n = 7
TEST_F(PruebasTableroReversiHex, InicializacionCorrecta_T_7)
{
	ASSERT_EQ(t_7.verFichaEn(2, 3), TableroReversiHex::Ficha::negra);
}




//***********************************************//
// Pruebas al método de observación y asignación //
//***********************************************//


//Caso simple que corresponde al punto 8 del enunciado, se coloca una ficha y recupera/observa esta misma.
TEST_F(PruebasTableroReversiHex, ColocarYLuegoObservarFicha) {

	t_5.colocarSimple(1, 3, TableroReversiHex::Ficha::negra);
	EXPECT_EQ(t_5.verFichaEn(1, 3), TableroReversiHex::Ficha::negra);

}


//*********************************//
// Pruebas del método adysToString //
//*********************************//

//Esta prueba corresponde al punto 9 del enunciado, se intenta validar el método adysToString
//Se nos pide validar con las adyacencias de las celdas ubicadas en 0,0 y 2,2

 TEST_F(PruebasTableroReversiHex, Prueba_adysToString) {
/*
	 std::string subHileraCeroCero = "{ 1 [ 2,0 ],2 [ 1,0 ]"; // contiene las adyacencias para la celda [0,0]
	 std::string subHileraDosDos = "{ 0 [ 3,1 ],1 [ 4,2 ],2 [ 3,2 ],3 [ 1,2 ],4 [ 0,2 ],5 [ 1,1 ] }"; //corresponde a las adyancencias para la celda 2,2

 std:string AdyacenciasCompletas = t_5.adysToString();

	 std::string resultado1 = AdyacenciasCompletas.substr(22, 21);

	 

	 std::string resultado2 = AdyacenciasCompletas.substr(613, 63);

	 EXPECT_EQ(subHileraCeroCero, resultado1);
	 EXPECT_EQ(subHileraDosDos, resultado2);
	 */
} 



//*************************************//
// Pruebas al método de VerFlanqueaDir //
//*************************************//


// Estas pruebas corresponden a las 6 posibles adyacencias y direcciones de flanqueo.
// Estas pruebas son acorde a lo solicitado en el punto 10 del enunciado.







//Pruebas de Verflanqueo en la dirección: derecha - Ascendente.

// Caso 1: con fichas localizadas al borde del tablero.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_derAsc_Borde) {

	t_7.colocarSimple(3, 0, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFlanqueaDir(0, 2, 1, TableroReversiHex::Ficha::blanca), true);
}

// Caso 2: con fichas localizadas en la zona interna del tablero.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_derAsc_Interna) {

	t_7.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(3, 0, TableroReversiHex::Ficha::blanca);

	ASSERT_TRUE(t_7.verFlanqueaDir(0, 1, 1, TableroReversiHex::Ficha::blanca));
}


//Pruebas de flanqueo en la dirección: derecha.
 
//Caso 1: fichas colocadas en la parte interna o "central" del tablero.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_der_Interna) {

	t_7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(6, 2, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFlanqueaDir(1, 2, 2, TableroReversiHex::Ficha::blanca), true);
}

//Caso 2: fichas colocadas en el borde del tablero.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_der_Borde) {

	t_7.colocarSimple(2, 0, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFlanqueaDir(1, 0, 0, TableroReversiHex::Ficha::blanca), true);
}


//Pruebas de Verflanqueo en la dirección: derecha - Descendente.

//Caso 1: fichas colocadas en la esquina.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_derDesc_Esquina) {

	t_7.colocarSimple(5, 5, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(6, 6, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFlanqueaDir(2, 4, 5, TableroReversiHex::Ficha::blanca), true);
}

//Caso 2: con fichas localizadas en la zona interna del tablero.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_derDesc_Interna){

	EXPECT_EQ(t_7.verFlanqueaDir(2, 2, 2, TableroReversiHex::Ficha::blanca), true);
}



// Pruebas de Verflanqueo en la dirección: izquierda - Descendente.

// Caso 1: Caso donde no es posible un flanqueo
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_izqDesc_Esquina) {

	t_7.colocarSimple(0, 6, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(1, 5, TableroReversiHex::Ficha::negra);

	ASSERT_FALSE(t_7.verFlanqueaDir(3, 2, 5, TableroReversiHex::Ficha::blanca));
}

////////////////////////////Caso2


//Pruebas de flanqueo en la dirección: Izquierda.

//Caso 1: fichas colocadas en la parte interna o "central" del tablero.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_izq_Interna) {
	t_7.colocarSimple(2, 2, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);

	EXPECT_EQ(t_7.verFlanqueaDir(4, 6, 2, TableroReversiHex::Ficha::blanca), true);
}
//Caso 2: fichas colocadas en el borde del tablero.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_izq_Borde) {

	t_5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);

	ASSERT_TRUE(t_5.verFlanqueaDir(4, 4, 2, TableroReversiHex::Ficha::blanca));
}


//////////////////Caso 1:

// Caso 2: Con las Fichas ubicadas en la parte interna o central del tablero.
TEST_F(PruebasTableroReversiHex, testVerFlanqueaDir_izqDesc_Interna) {

	t_7.colocarSimple(2, 5, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(3, 4, TableroReversiHex::Ficha::negra);

	ASSERT_TRUE(t_7.verFlanqueaDir(5, 4, 4, TableroReversiHex::Ficha::blanca));
}



//**********************************//
// Pruebas al método de FlanqueaDir //
//**********************************//


//Pruebas de flanqueo en la dirección: Izquierda.

//Caso 1: fichas colocadas en la parte interna o "central" del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izq_Interna) {
	t_7.colocarSimple(2, 2, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
	t_7.flanqueaDir(4, 6, 2, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(4,2), TableroReversiHex::Ficha::blanca);
}

//Caso 2: fichas colocadas en el borde del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izq_Borde) {

	t_5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 2, TableroReversiHex::Ficha::negra);
	t_5.flanqueaDir(4, 4, 2, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_5.verFichaEn(2, 2), TableroReversiHex::Ficha::blanca);
}


//Pruebas de flanqueo en la dirección: derecha.

//Caso 1: fichas colocadas en la parte interna o "central" del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_der_Interna) {

	t_7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(6, 2, TableroReversiHex::Ficha::blanca);
	t_7.flanqueaDir(1, 2, 2, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(4,2), TableroReversiHex::Ficha::blanca);
}

//Caso 2: fichas colocadas en el borde del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_der_Borde) {

	t_7.colocarSimple(2, 0, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);
	t_7.flanqueaDir(1, 0, 0, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(2, 0), TableroReversiHex::Ficha::blanca);
}



//Pruebas de Verflanqueo en la dirección: derecha - Descendente.

//Caso 1: fichas colocadas en la esquina.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_derDesc_Esquina) {

	t_7.colocarSimple(5, 5, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(6, 6, TableroReversiHex::Ficha::blanca);
	t_7.flanqueaDir(2, 4, 5, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(5, 5), TableroReversiHex::Ficha::blanca);
}

//Caso 2: con fichas localizadas en la zona interna del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_derDesc_Interna) {

	t_7.flanqueaDir(2, 2, 2, TableroReversiHex::Ficha::blanca);
	
	EXPECT_EQ(t_7.verFichaEn(3, 2), TableroReversiHex::Ficha::blanca);
}



//Pruebas de Verflanqueo en la dirección: derecha - Ascendente.

// Caso 1: con fichas localizadas al borde del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_derAsc_Borde) {

	t_7.colocarSimple(3, 0, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);
	t_7.flanqueaDir(0, 2, 1, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(3,0), TableroReversiHex::Ficha::blanca);
}

// Caso 2: con fichas localizadas en la zona interna del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_derAsc_Interna) {

	t_7.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(3, 0, TableroReversiHex::Ficha::blanca);
	t_7.flanqueaDir(0, 1, 1, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(2, 1), TableroReversiHex::Ficha::blanca);
}



// Pruebas de Verflanqueo en la dirección: izquierda - Descendente.

// Caso 1: Con las Fichas ubicadas en una esquina del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izqDesc_Esquina) {

	t_7.colocarSimple(0, 6, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(1, 5, TableroReversiHex::Ficha::negra);
	t_7.flanqueaDir(3, 2, 5, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(1,5), TableroReversiHex::Ficha::blanca);
}

// Caso 2: Con las Fichas ubicadas en la parte interna o central del tablero.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izqDesc_Interna) {

	t_7.colocarSimple(2, 5, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(3, 4, TableroReversiHex::Ficha::negra);
	t_7.flanqueaDir(3, 4, 4, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(3,4), TableroReversiHex::Ficha::blanca);
}



// Pruebas de Verflanqueo en la dirección: izquierda - Ascendente.

// Caso 1: con flanqueo en una esquina.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izqAsc_Esquina) {

	t_7.colocarSimple(0, 0, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);
	t_7.flanqueaDir(5, 2, 1, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFichaEn(1, 0), TableroReversiHex::Ficha::blanca);
}

// Caso 2: con flanqueo en la parte interna del tablero.

TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izqAsc_Interna) {

	t_7.flanqueaDir(5, 5, 3, TableroReversiHex::Ficha::negra);
	EXPECT_EQ(t_7.verFichaEn(4, 3), TableroReversiHex::Ficha::negra);
}


//*********************************//
// Pruebas al método ValidarJugada //
//*********************************//

//Caso con flanqueo en dos direcciones (dos flanqueos diagonales incluyendo fichas en esquina)
TEST_F(PruebasTableroReversiHex, testValidarJugada_1) {

	t_7.colocarSimple(0, 0, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(3, 0, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);

	ASSERT_TRUE(t_7.validarJugada(2, 1, TableroReversiHex::Ficha::blanca));
}

//Caso con flanqueo en una dirección (incluyendo fichas en esquina)
TEST_F(PruebasTableroReversiHex, testValidarJugada_2) {

	t_7.colocarSimple(0, 0, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);

	ASSERT_TRUE(t_7.validarJugada(2, 1, TableroReversiHex::Ficha::blanca));
}


//Caso con flanqueo diagonal, una sola dirección (incluyendo fichas en el borde)
TEST_F(PruebasTableroReversiHex, testValidarJugada_3) {

	t_7.colocarSimple(3, 4, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(2, 5, TableroReversiHex::Ficha::blanca);
	ASSERT_TRUE(t_7.validarJugada(1, 5, TableroReversiHex::Ficha::negra));
}

//Caso con flanqueo diagonal con dos direcciones, incluyendo las fichas iniciales 
TEST_F(PruebasTableroReversiHex, testValidarJugada_4) {

	t_7.colocarSimple(3, 4, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(4, 5, TableroReversiHex::Ficha::negra);
	ASSERT_TRUE(t_7.validarJugada(2, 4, TableroReversiHex::Ficha::negra));
}

//Caso con flanqueo en una direccion utilizando las fichas iniciales
TEST_F(PruebasTableroReversiHex, testValidarJugada_5) {
	ASSERT_TRUE(t_7.validarJugada(2, 2, TableroReversiHex::Ficha::blanca));
}

//Caso flanqueo diagonal en una direccion, desde una esquina
TEST_F(PruebasTableroReversiHex, testValidarJugada_6) {

	t_7.colocarSimple(5, 5, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(6, 6, TableroReversiHex::Ficha::blanca);
	ASSERT_TRUE(t_7.validarJugada(4, 5, TableroReversiHex::Ficha::blanca));
}

//Caso flanqueo en dos direcciones utilizando las fichas iniciales y modificando una
TEST_F(PruebasTableroReversiHex, testValidarJugada_7) {
	t_7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(3, 4, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 5, TableroReversiHex::Ficha::blanca);
	ASSERT_TRUE(t_7.validarJugada(2, 4, TableroReversiHex::Ficha::blanca));
}
//Caso flanqueo en dos direcciones colocando una ficha en medio
TEST_F(PruebasTableroReversiHex, testValidarJugada_8) {
	t_7.colocarSimple(1, 0, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 2, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(5, 2, TableroReversiHex::Ficha::blanca);

	ASSERT_TRUE(t_7.validarJugada(3, 1, TableroReversiHex::Ficha::negra));
}

// Caso de flanqueo en dos direcciones con jugada en la esquina y con fa
TEST_F(PruebasTableroReversiHex, testValidarJugada_9) {
	t_7.colocarSimple(2, 1, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);
	
	t_7.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(3, 0, TableroReversiHex::Ficha::negra);
	ASSERT_TRUE(t_7.validarJugada(0, 0, TableroReversiHex::Ficha::blanca));
}

// Caso flanqueo en dos direcciones realizando el cambio de una ficha inicial
TEST_F(PruebasTableroReversiHex, testValidarJugada_10) {
	t_7.colocarSimple(4, 3, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(3, 4, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(4, 5, TableroReversiHex::Ficha::negra);
	ASSERT_TRUE(t_7.validarJugada(2, 4, TableroReversiHex::Ficha::blanca));
}

// Caso flanqueo en un a direccion utilizando dos fichas iniciales y modificando una
TEST_F(PruebasTableroReversiHex, testValidarJugada_11) {
	t_7.colocarSimple(3, 3, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 4, TableroReversiHex::Ficha::blanca);
	ASSERT_TRUE(t_7.validarJugada(1, 2, TableroReversiHex::Ficha::blanca));
}

//Caso flanqueo en una direccion, ignorando las fichas iniciales
TEST_F(PruebasTableroReversiHex, testValidarJugada_12) {
	t_7.colocarSimple(3, 4, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(4, 5, TableroReversiHex::Ficha::negra);
	ASSERT_TRUE(t_7.validarJugada(2, 4, TableroReversiHex::Ficha::blanca));
}



//***************************************//
//			Pruebas VerFin()			 //
//***************************************//

//Caso con tablero lleno, verFin == True
TEST_F(PruebasTableroReversiHex, testVerFin) {
	t_5.colocarSimple(0, 0, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(1, 0, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 0, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(3, 0, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);

	t_5.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(1, 1, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 1, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(3, 1, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 1, TableroReversiHex::Ficha::blanca);

	t_5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(1, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(3, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 2, TableroReversiHex::Ficha::blanca);

	t_5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(1, 3, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 3, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(3, 3, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);

	t_5.colocarSimple(0, 4, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 4, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 4, TableroReversiHex::Ficha::blanca);

	ASSERT_TRUE(t_5.verFin());
}


//Caso en que el tablero no está lleno.
TEST_F(PruebasTableroReversiHex, testVerFin_2) {
	t_7.colocarSimple(3, 4, TableroReversiHex::Ficha::blanca);
	ASSERT_FALSE(t_7.verFin());
}


//******************************************************/
//				Pruebas VerPasan()						/
//******************************************************/

//Caso donde el tablero se encuentra lleno y solo puede jugar una ficha
TEST_F(PruebasTableroReversiHex, testVerPasan) {
	t_5.colocarSimple(0, 0, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(1, 0, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 0, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(3, 0, TableroReversiHex::Ficha::negra);
	t_5.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);

	t_5.colocarSimple(0, 1, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(1, 1, TableroReversiHex::Ficha::blanca); //Este es el espacio donde se puede jugar,
	t_5.colocarSimple(2, 1, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(3, 1, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 1, TableroReversiHex::Ficha::blanca);

	t_5.colocarSimple(0, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(1, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(3, 2, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 2, TableroReversiHex::Ficha::blanca);

	t_5.colocarSimple(0, 3, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(1, 3, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 3, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(3, 3, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 3, TableroReversiHex::Ficha::blanca);

	t_5.colocarSimple(0, 4, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(2, 4, TableroReversiHex::Ficha::blanca);
	t_5.colocarSimple(4, 4, TableroReversiHex::Ficha::blanca);
	

	EXPECT_FALSE(t_5.verPasan(TableroReversiHex::Ficha::negra));
}