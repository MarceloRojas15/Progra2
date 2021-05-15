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


///////////////////////////
///// CASOS DE PRUEBA /////
///////////////////////////

/// Prueba del constructor///

// Caso �nico, se prueba el tablero t_5 con tama�o n=5, as� como el tablero T_7 de tama�o n=7
TEST_F(PruebasTableroReversiHex, InicializacionCorrecta)
{	
	ASSERT_EQ(t_5.verFichaEn(3, 2), TableroReversiHex::Ficha::negra);
	ASSERT_EQ(t_5.verFichaEn(1, 1), TableroReversiHex::Ficha::blanca);

	ASSERT_EQ(t_7.verFichaEn(2, 3), TableroReversiHex::Ficha::negra);
}

TEST_F(PruebasTableroReversiHex, ColocarYLuegoObservarFicha) {

	t_5.colocarSimple(1, 3, TableroReversiHex::Ficha::negra);
	EXPECT_EQ(t_5.verFichaEn(1, 3), TableroReversiHex::Ficha::negra);

}



// Pruebas del m�todo adysToString //


// El profesor nos dijo que no hicieramos todav�a esta prueba, la cual corresponde al punto 9 del enunciado.

////////////////////////////////////// AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH ///////////////////////////////////////////////////////

/* TEST_F(PruebasTableroReversiHex, Prueba_adysToString_1) {

	t_5.colocarSimple(0, 0, TableroReversiHex::Ficha::negra);
	t_5.colocarSimple(1, 0, TableroReversiHex::Ficha::blanca);
} */


TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izq) {

	t_7.colocarSimple(2, 2, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);

	EXPECT_EQ(t_7.verFlanqueaDir(4, 6, 2, TableroReversiHex::Ficha::blanca), true);

}//FALTA UNO

TEST_F(PruebasTableroReversiHex, testFlanqueaDir_der) {

	t_7.colocarSimple(4, 2, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(6, 2, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFlanqueaDir(1, 2, 2, TableroReversiHex::Ficha::blanca), true);

}//FALTA UNO


//Caso con esquina verFlanqueo direcci�n derecha descendente.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_derDesc_Esquina) {

	t_7.colocarSimple(5, 5, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(6, 6, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFlanqueaDir(2, 4, 5, TableroReversiHex::Ficha::blanca), true);

}

//Caso con fichas localizadas en la zona interna del tablero verFlanqueo direcci�n derecha descendente.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_derDesc_Interna){

	EXPECT_EQ(t_7.verFlanqueaDir(2, 2, 2, TableroReversiHex::Ficha::blanca), true);

}


// Caso con fichas localizadas al borde del tablero verFlanqueo direcci�n derecha ascendente.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_derAscBorde) {


	t_7.colocarSimple(3, 0, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(4, 0, TableroReversiHex::Ficha::blanca);

	EXPECT_EQ(t_7.verFlanqueaDir(0, 2, 1, TableroReversiHex::Ficha::blanca), true);

}
// Caso con fichas localizadas en la zona interna del tablero verFlanqueo direcci�n derecha ascendente.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_derAscInterna) {


	t_7.colocarSimple(2, 1, TableroReversiHex::Ficha::negra);
	t_7.colocarSimple(3, 0, TableroReversiHex::Ficha::blanca);

	ASSERT_TRUE(t_7.verFlanqueaDir(0, 1, 1, TableroReversiHex::Ficha::blanca));

}

//Caso con esquina verFlanqueo direcci�n izquierda descendente.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izqDesc_Esquina) {


	t_7.colocarSimple(0, 6, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(1, 5, TableroReversiHex::Ficha::negra);

	ASSERT_TRUE(t_7.verFlanqueaDir(5, 2, 5, TableroReversiHex::Ficha::blanca));

}
//FALTA UNO




//Caso con esquina verFlanqueo direcci�n izquierda ascendente.
TEST_F(PruebasTableroReversiHex, testFlanqueaDir_izqAsc_Esquina) {


	t_7.colocarSimple(0, 0, TableroReversiHex::Ficha::blanca);
	t_7.colocarSimple(1, 0, TableroReversiHex::Ficha::negra);

	ASSERT_TRUE(t_7.verFlanqueaDir(6, 2, 1, TableroReversiHex::Ficha::blanca));

}