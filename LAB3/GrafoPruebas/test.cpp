#include "pch.h"
#include "..\LaboratorioGuiado3\GrafoGnr.h"
#include <iostream>
#include <fstream>
using namespace std;

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

class GrafoPruebas : public ::testing::Test {
protected:
	/* DATOS COMUNES A CASOS DE PRUEBA */
	GrafoGnr< int > gg;
	GrafoGnr< int > gg2;
	ifstream entradaP;
	ifstream entradaM;
	shared_ptr<GrafoGnr<int>> grafoP;
	shared_ptr<GrafoGnr<int>> grafoM;

	// Constructor inicializador del suite de pruebas.
	GrafoPruebas();
	// Destructor del suite de pruebas.
	~GrafoPruebas() override;
};

/* DEFINICIÓN DE LOS MÉTODOS BÁSICOS DEL ACCESORIO */
GrafoPruebas::GrafoPruebas() : gg(10, 0.5), gg2(20, 0.5){
	ifstream entradaP("grafo_p.txt", ios::in);
	ifstream entradaM("grafo_m.txt", ios::in);
	grafoP = shared_ptr<GrafoGnr <int>> (new GrafoGnr<int>(entradaP));
	grafoM = shared_ptr<GrafoGnr <int>>(new GrafoGnr<int>(entradaM));

}
GrafoPruebas::~GrafoPruebas()
{
}


//**************************************************//
//													//
//					Casos de Prueba					//
//													//
//**************************************************//


/*********************************************************/
//				CONSTRUCTOR ALEATORIO
/*********************************************************/

//Verificar con N = 10, la cantidad de vertices creados
TEST_F(GrafoPruebas, InicializacionCorrectaN10) {
	EXPECT_EQ(gg.obtTotVrt(), 10);
}

//Verificar con N = 10, la cantidad de vertices creados
TEST_F(GrafoPruebas, InicializacionCorrectaN20) {
	EXPECT_EQ(gg2.obtTotVrt(), 20);
}

/*********************************************************/
//			PRUEBAS PARA CONSTRUCTOR POR ARCHIVO
/*********************************************************/


TEST_F(GrafoPruebas, porArchivoP) {

	EXPECT_EQ(grafoP->obtTotVrt(), 10);
	EXPECT_EQ(grafoP->obtTotAdys(), 22);
	EXPECT_TRUE(grafoP->xstAdy(2, 4));
	EXPECT_TRUE(grafoP->xstAdy(9, 2));//
	EXPECT_TRUE(grafoP->xstAdy(0, 3));
	EXPECT_FALSE(grafoP->xstAdy(0, 1));

	//Serialización 
}

TEST_F(GrafoPruebas, porArchivoM) {

	EXPECT_EQ(grafoM->obtTotVrt(), 12);
	EXPECT_EQ(grafoM->obtTotAdys(), 11);
	EXPECT_TRUE(grafoM->xstAdy(0, 1));
	EXPECT_TRUE(grafoM->xstAdy(2, 0));
	EXPECT_TRUE(grafoM->xstAdy(1, 4));
	EXPECT_FALSE(grafoM->xstAdy(2, 7));

	EXPECT_STREQ("hola", "hola");
}



/*********************************************************/
//			PRUEBAS PARA PRUEBAS DE OBTIDVRTADYS
/*********************************************************/

TEST_F(GrafoPruebas, adyacencias) {

	vector <int> cosa;

	grafoP->obtIdVrtAdys(2, cosa);

	EXPECT_TRUE(4, cosa[0]);
}




/*********************************************************/
//			PRUEBAS PARA OBTCNTVRTADYS
/*********************************************************/


TEST_F(GrafoPruebas, adyacenciasB) {


	EXPECT_EQ(4, grafoP->obtCntVrtAdys(2));
}


/*********************************************************/
//			PRUEBAS PARA OBTCAMINOSMINIMOS
/*********************************************************/


TEST_F(GrafoPruebas, caminosMinimosP) {

	vector<vector <int>> cosa2;
	grafoP->obtCaminosMinimos(2, cosa2);

	EXPECT_EQ(2, 2);
}

TEST_F(GrafoPruebas, caminosMinimosM) {


	vector<vector <int>> cosa2;
	grafoP->obtCaminosMinimos(2, cosa2);

	EXPECT_EQ(2, 2);
}

/*********************************************************/
//		   PRUEBAS PARA OBTRECORRIDOXANCHURA
/*********************************************************/


TEST_F(GrafoPruebas, anchuraP) {

	vector <int> cosa2;
	grafoP->obtRecorridoXanchura(0, cosa2);

	EXPECT_FALSE(!cosa2.empty());
}

TEST_F(GrafoPruebas, anchuraM) {

	vector <int> cosa2;
	grafoM->obtRecorridoXanchura(0, cosa2);

	EXPECT_FALSE(!cosa2.empty());
}

