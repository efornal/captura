/*
 * ejer6_1.cpp
 *
 *  Created on: 13/05/2010
 *      Author: christian
 */

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include "../lib6/restauracion.h"
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/placa_original.tif", "ruta archivo imagen" );
	CImg<double> img(filename); //imagen original

	int tam_mascara = 3;
	int d = 1.0;
	int sigma = 1.0;
	//contamino imagen con ruido impuslivo y gaussiano:
	CImg<double> img_ruidosa(img);

	gen_ruido_gaussiano(img_ruidosa, sigma);
	gen_ruido_sal_y_pimienta(img_ruidosa, sigma);

	CImgDisplay orig(img, "imagen original");

	CImgDisplay disp(img_ruidosa, "imagen con ruido gaussiano e impulsivo");

	CImg<double> filtrada_mediana_y_punto_medio = filtrado_punto_medio(
			filtrado_mediana(img_ruidosa, tam_mascara), tam_mascara);

	CImg<double> filtrada_media_alfa_recortado = filtrado_alfa_recortado(
			img_ruidosa, d, tam_mascara);

	CImgDisplay fil1(filtrada_mediana_y_punto_medio,
			"filtrada con mediana+punto medio");
	CImgDisplay fil2(filtrada_media_alfa_recortado,
			"filtrada con media alfa recortado");

	while (!disp.is_closed()) {
		disp.wait();
		if (disp.is_keyARROWUP()) {
			tam_mascara++;
		} else if (disp.is_keyARROWDOWN()) {
			tam_mascara--;
		} else if (disp.is_keyARROWLEFT()) {
			sigma--;
			img_ruidosa.clear();
			img_ruidosa.assign(img);
			gen_ruido_gaussiano(img_ruidosa, sigma);
			gen_ruido_sal_y_pimienta(img_ruidosa, sigma);
		} else if (disp.is_keyARROWRIGHT()) {
			sigma++;
			img_ruidosa.clear();
			img_ruidosa.assign(img);
			gen_ruido_gaussiano(img_ruidosa, sigma);
			gen_ruido_sal_y_pimienta(img_ruidosa, sigma);
		} else if (disp.is_keyD()) {
			d++;
		} else if (disp.is_keyC()) {
			d--;
		}
		filtrada_media_alfa_recortado = filtrado_alfa_recortado(img_ruidosa, d,
				tam_mascara);
		filtrada_mediana_y_punto_medio = filtrado_punto_medio(filtrado_mediana(
				img_ruidosa, tam_mascara), tam_mascara);

		filtrada_media_alfa_recortado.display(fil2);
		fil2.set_title("filtrada con media alfa recortado");

		filtrada_mediana_y_punto_medio.display(fil1);
		fil1.set_title("filtrada con mediana+punto medio");

		cout << "Tam Mascara: " << tam_mascara << "   d: " << d
				<< "   varianza: " << sigma << endl;
		//POSTA: con un d apropiado el alfa recortado se ve mejor no se borronea tanto como el otro
	}
	return 0;
}
