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

	float sigma = 1.0;
	int tam_mascara = 3;
	int q = 2;
	//contamino imagen con ruido impuslivo y gaussiano:
	CImg<double> img_ruidosa(img);
	gen_ruido_gaussiano(img_ruidosa, sigma);
	gen_ruido_sal_y_pimienta(img_ruidosa, sigma);
	CImgDisplay disp(img_ruidosa, "imagen con ruido gaussiano e impulsivo");
	CImgDisplay geom(filtrado_geometrica(img_ruidosa, tam_mascara),
			"Filtrado con media geometrica");
	CImgDisplay contraarmonica(filtrado_contra_armonica(img_ruidosa, q,
			tam_mascara), "Filtrado con contra armonica");

	CImg<double> filtrada_ambos = filtrado_geometrica(filtrado_contra_armonica(
			img_ruidosa, q, tam_mascara), tam_mascara);
	CImgDisplay ambos(filtrada_ambos, "filtrado contrarmonica y geometrico");
	while (!disp.is_closed()) {
		disp.wait();
		if (disp.is_keyARROWUP()) {
			tam_mascara++;
			filtrado_geometrica(img_ruidosa, tam_mascara).normalize(0, 255).display(
					geom);
			geom.set_title("Filtrado con media geometrica");
			filtrado_contra_armonica(img_ruidosa, q, tam_mascara).normalize(0,
					255).display(contraarmonica);
			contraarmonica.set_title("Filtrado con contra armonica");
			filtrada_ambos = filtrado_geometrica(filtrado_contra_armonica(
					img_ruidosa, q, tam_mascara), tam_mascara);
			filtrada_ambos.normalize(0, 255).display(ambos);
			ambos.set_title("filtrado contrarmonica y geometrico");
		} else if (disp.is_keyARROWDOWN()) {
			tam_mascara--;
			filtrado_geometrica(img_ruidosa, tam_mascara).normalize(0, 255).display(
					geom);
			geom.set_title("Filtrado con media geometrica");
			filtrado_contra_armonica(img_ruidosa, q, tam_mascara).normalize(0,
					255).display(contraarmonica);
			contraarmonica.set_title("Filtrado con contra armonica");
			filtrada_ambos = filtrado_geometrica(filtrado_contra_armonica(
					img_ruidosa, q, tam_mascara), tam_mascara);
			filtrada_ambos.normalize(0, 255).display(ambos);
			ambos.set_title("filtrado contrarmonica y geometrico");
		} else if (disp.is_keyARROWLEFT()) {
			sigma--;
			img_ruidosa.clear();
			img_ruidosa.assign(img);
			gen_ruido_gaussiano(img_ruidosa, sigma);
			gen_ruido_sal_y_pimienta(img_ruidosa, sigma);
			filtrado_geometrica(img_ruidosa, tam_mascara).normalize(0, 255).display(
					geom);
			geom.set_title("Filtrado con media geometrica");
			filtrado_contra_armonica(img_ruidosa, q, tam_mascara).normalize(0,
					255).display(contraarmonica);
			contraarmonica.set_title("Filtrado con contra armonica");
			filtrada_ambos = filtrado_geometrica(filtrado_contra_armonica(
					img_ruidosa, q, tam_mascara), tam_mascara);
			filtrada_ambos.normalize(0, 255).display(ambos);
			ambos.set_title("filtrado contrarmonica y geometrico");
		} else if (disp.is_keyARROWRIGHT()) {
			sigma++;
			img_ruidosa.clear();
			img_ruidosa.assign(img);
			gen_ruido_gaussiano(img_ruidosa, sigma);
			gen_ruido_sal_y_pimienta(img_ruidosa, sigma);
			filtrado_geometrica(img_ruidosa, tam_mascara).normalize(0, 255).display(
					geom);
			geom.set_title("Filtrado con media geometrica");
			filtrado_contra_armonica(img_ruidosa, q, tam_mascara).normalize(0,
					255).display(contraarmonica);
			contraarmonica.set_title("Filtrado con contra armonica");
			filtrada_ambos = filtrado_geometrica(filtrado_contra_armonica(
					img_ruidosa, q, tam_mascara), tam_mascara);
			filtrada_ambos.normalize(0, 255).display(ambos);
			ambos.set_title("filtrado contrarmonica y geometrico");
		} else if (disp.is_keyQ()) {
			q++;
			filtrado_contra_armonica(img_ruidosa, q, tam_mascara).normalize(0,
					255).display(contraarmonica);
			contraarmonica.set_title("Filtrado con contra armonica");
			filtrada_ambos = filtrado_geometrica(filtrado_contra_armonica(
					img_ruidosa, q, tam_mascara), tam_mascara);
			filtrada_ambos.normalize(0, 255).display(ambos);
			ambos.set_title("filtrado contrarmonica y geometrico");
		} else if (disp.is_keyA()) {
			q--;
			filtrado_contra_armonica(img_ruidosa, q, tam_mascara).normalize(0,
					255).display(contraarmonica);
			contraarmonica.set_title("Filtrado con contra armonica");
			filtrada_ambos = filtrado_geometrica(filtrado_contra_armonica(
					img_ruidosa, q, tam_mascara), tam_mascara);
			filtrada_ambos.normalize(0, 255).display(ambos);
			ambos.set_title("filtrado contrarmonica y geometrico");
		}
		cout << "Tam. mascara: " << tam_mascara << "   varianza: " << sigma
				<< "   q: " << q << endl;
		cout << "ECM entre imagen filtrada y limpia: " << img.MSE(
				filtrada_ambos) << endl; //fixme: porque me tira nan!
		cout << "ECM entre imagen degradada y limpia: " << img.MSE(img_ruidosa)
				<< endl;
	}
	return 0;
}
