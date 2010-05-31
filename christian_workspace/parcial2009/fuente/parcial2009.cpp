//============================================================================
// Name        : parcial2009.cpp
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>
#include "../../tp6/fuente/lib6/restauracion.h"
#include "../../tp7/fuente/lib7/segmentacion.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option("-f1", "./CPDSI_Parcial_Practica_2009/iguazu_ruidogris.jpg",
							"ruta archivo imagen");
	const char
			*filename1 =
					cimg_option("-f2", "./CPDSI_Parcial_Practica_2009/corrientes_ruidogris.jpg",
							"ruta archivo imagen");
	int tam_mascara = cimg_option("-sizemask", 9, "Tam de la mascara");
	int d = cimg_option("-dfiltro", 1.0, "d del filtro media alfa recortado");
	float umbral = cimg_option("-umbral", 1.0, "umbral sobel");
	int x = cimg_option("-x", 200, "posicion en x del pixel a segemntar");
	int y = cimg_option("-y", 200, "posicion en y del pixel a segemntar");
	float tolerancia = cimg_option("-tol", 20.0, "tolerancia");
	int cantidad_vecinos = cimg_option("-vecinos", 4, "cant vecinos 4 u 8");

	CImg<double> img(filename); //imagen original
	CImgDisplay disp(img, "imagen original1");
	CImg<double> img2(filename1); //imagen original 2
	CImgDisplay disp2(img2, "imagen original2");

	CImg<double> img_filtrada = filtrado_alfa_recortado(img, d, tam_mascara);
	CImg<double> img_filtrada2 = filtrado_alfa_recortado(img2, d, tam_mascara);
	CImgDisplay disp1(img_filtrada, "imagen filtrada1");
	CImgDisplay disp3(img_filtrada2, "imagen filtrada2");
	//img_filtrada.display();
	//segmentacion:
	CImg<double> imagen_segmentada = segmentar(img_filtrada, x, y, tolerancia,
			cantidad_vecinos);
	CImgDisplay disp8(imagen_segmentada, "imagen segmentada");

	CImg<double> original_segmentada = binaria_a_original(imagen_segmentada,
			img_filtrada);
	CImgDisplay disp9(original_segmentada, "imagen orig. segmentada");

	while (!disp1.is_closed()) {
		disp1.wait();
		/*	if (disp1.is_keyARROWDOWN()) {
		 d--;
		 cout << "d: " << d << endl;
		 } else if (disp1.is_keyARROWUP()) {
		 d++;
		 cout << "d: " << d << endl;
		 } else if (disp1.is_keyARROWRIGHT()) {
		 tam_mascara++;
		 cout << "tam mascara: " << tam_mascara << endl;
		 } else if (disp1.is_keyARROWLEFT()) {
		 tam_mascara--;
		 cout << "tam mascara: " << tam_mascara << endl;
		 }
		 img_filtrada = filtrado_alfa_recortado(img, d, tam_mascara);
		 img_filtrada.display(disp1);
		 disp1.set_title("imagen filtrada");*/
	}
	return 0;
}
