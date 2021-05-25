#include "pch.h"
#include "../ReversiHex/TableroReversiHex.h"


class ReversiHexPruebas : public ::testing::Test {
protected:
	
	TableroReversiHex t_5;
	TableroReversiHex t_7;

};
/* DEFINICIÓN DE LOS MÉTODOS BÁSICOS DEL ACCESORIO */
ReversiHexPruebas::ReversiHexPruebas() :t_5(5), t_7(7) {



}
