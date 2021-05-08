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


TEST(PruebasTableroReversiHex, InicializacionCorrecta)
{	
	//ASSERT_EQ(t_5.verFichaEn(3, 3), TableroReversiHex::Ficha::blanca);

}