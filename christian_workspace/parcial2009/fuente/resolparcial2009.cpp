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
#include "../../tp7/fuente/lib7/CPDSI_segmentacion.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option("-f1", "./CPDSI_Parcial_Practica_2009/corrientes_ruidogris.jpg",
							"ruta archivo imagen");
	int tam_mascara = cimg_option("-sizemask", 9, "Tam de la mascara");
	int d = cimg_option("-dfiltro", 1.0, "d del filtro media alfa recortado");
	float umbral = cimg_option("-umbral", 167.0, "umbral sobel");
	float tol_grados = cimg_option("-tol", 10.0, "tolerancia");
	int
			cant_max =
					cimg_option("-cantmax", 10, "cantidad de maximos a obtener de la transf de Hough");

	CImg<double> img(filename); //imagen original
	img.print();
	CImgDisplay disp(img, "imagen original1");
	CImg<double> img_filtrada = filtrado_alfa_recortado(img, d, tam_mascara);

	//filtro la imagen:
	CImgDisplay disp1(img_filtrada, "imagen filtrada");

	//detecto los bordes y dejo la imagen binaria
	CImg<double> segmentada = segmentar(img_filtrada, get_sobel_x<double> (),
			get_sobel_y<double> (), umbral, true);
	CImgDisplay disp2(segmentada, "imagen segmentada sobel");

	//aplico transformada de Hough...
	CImg<double> SEGMENTADA = hough_directa(segmentada);
	CImgDisplay disp3(SEGMENTADA, "T. Hough de imagen segmentada");
	int direccion = -99;//-99 implica todas las direcciones!
	vector<double> posiciones_maximos = obtener_maximos(SEGMENTADA, cant_max,
			direccion, tol_grados); //tengo los maximos de la Transformada

	//ver los maximos
	CImg<double> maxs = grafica_maximos<double> (posiciones_maximos,
			img.width(), img.height());
	CImgDisplay disp4(maxs, "maximos de la transf");

	CImg<double> img_hough_inversa = hough_inversa(maxs);
	CImgDisplay disp5(img_hough_inversa, "inversa Hough de maximos");

	img_filtrada.draw_image(colorea_rojo(img_hough_inversa), 0.5);
	img_filtrada.display();

	CImgDisplay disp6(colorea_rojo(img_hough_inversa));
	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyARROWUP()) {
			umbral++;
			cout << "umbral: " << umbral << endl;
		} else if (disp1.is_keyARROWDOWN()) {
			umbral--;
			cout << "umbral: " << umbral << endl;
		}
		segmentada = segmentar(img_filtrada, get_sobel_x<double> (),
				get_sobel_y<double> (), umbral, true);
		segmentada.display(disp2);

	}
	return 0;
}
