/*
 * ejer1_1y2.cpp
 *
 *  Created on: 22/05/2010
 *      Author: christian
 */

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>
#include "../lib7/CPDSI_segmentacion.h"
#include "../lib7/segmentacion.h"
#include "../../../tp2/fuente/lib2/operadores_logicos.h"

using namespace std;
using namespace cimg_library;
/*
 * http://users.cs.cf.ac.uk/Paul.Rosin/CM0311/dual2/hough.html
 * */
int main(int argc, char **argv) {
	const char *filename = cimg_option("-f", "../../imagenes/letras1.tif",
			"ruta archivo imagen");

	const float umbral = cimg_option("-umbral", 20.0, "umbral");
	const int
			direccion =
					cimg_option ("-direccionborde", -99, "direccion borde a buscar - -99 implica todas las direcciones");
	const int cant_maximos =
			cimg_option("-cantmaximos", 50, "cantidad de maximos a detectar");
	int tol_grados = cimg_option ("-tolgrados", 0, "tolerancia en grados");
	CImg<double> img(filename); //imagen original

	//aplicar deteccion de bordes a la imagen
	CImg<double> img_bordes = aplicar_sobel<double> (img, umbral, true); //img_bordes es binaria y tiene valores entre 0 y 255...

	//aplico la transf de hough:
	CImg<double> HOUGH_IMG_BORDES = hough_directa(img_bordes); // aplico la transformada

	vector<double> posiciones_maximos = obtener_maximos(HOUGH_IMG_BORDES,
			cant_maximos, direccion, tol_grados);

	CImg<double> maxs = grafica_maximos <double> (posiciones_maximos,
			HOUGH_IMG_BORDES.width(), HOUGH_IMG_BORDES.height());

	CImg<double> deteccion = hough_inversa(maxs);
	deteccion.print();

	// si hago un AND entre la imagen con los bordes detectados y lo que me devolvio la inversa
	// de hough me voy a quedar co lo que realmente son bordes:

	CImg<double> deteccion_final = AND(img_bordes, deteccion);

	//muestro
	CImgDisplay d1(img, "imagen original");
	CImgDisplay d2(img_bordes, "deteccion bordes");
	CImgDisplay d3(HOUGH_IMG_BORDES, "Transf. Hough");
	CImgDisplay d4(maxs, "maximos detectados");
	CImgDisplay disp(deteccion, "inversaHough(maximos)");
	CImgDisplay d5(deteccion_final, "and entre imagen y bordes");
	CImg<> deteccion_final_coloreada = colorea_rojo(deteccion);
	CImgDisplay disppp(img);
	deteccion_final_coloreada.display();

	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
