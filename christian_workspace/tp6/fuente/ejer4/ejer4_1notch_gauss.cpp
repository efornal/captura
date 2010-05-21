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
#include "../../../tp5/fuente/lib5/lib5.h"
#include "../../../tp5/fuente/lib5/filtros.h"
//#include "../../../tp2/fuente/lib2/lut.h"
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f1", "../../imagenes/img_degradada.tif", "ruta archivo imagen sucia" );
	const char
			*filename1 =
					cimg_option( "-f2", "../../imagenes/img.tif", "ruta archivo imagen limpia" );
	const int
				x0 =
						cimg_option( "-x0", 58, "coord x donde aparece el notch" );
	const int
				y0 =
						cimg_option( "-y0", 38, "coord y donde aparece el notch" );

	CImg<double> img_degradada(filename); //imagen degradada
	CImg<double> img_limpia(filename1); //imagen degradada
	CImgDisplay disorigianl(img_limpia, "imagen original");

	/* img_degradada -> Espectro fourier centrado -> puntos de ruido: 58,38 y 198,218
	 *
	 * */

	float espesor = 20.0;

	CImgList<float> fft_imgdegra = img_degradada.get_FFT();
	CImg<double> img_degradada_magnitud = get_magnitud(img_degradada, true);
	CImg<double> img_degradada_fase = get_fase(img_degradada);

	CImgDisplay disp(img_degradada, "imagen degradada");
	CImgDisplay dispf(fft_imgdegra[0], "real(fft(img_deg))->ACA ANULAR FREC!");
	CImgDisplay fase(img_degradada_fase, "fase FFT (imagen degradada)");
	CImgDisplay magnitud(img_degradada_magnitud, "magn.FFT (imagen degradada)");
	//img_degradada_magnitud.display(); //descomentar para ver coordenadas de ruido
	CImgDisplay magnitudlog(img_degradada_magnitud.get_log(),
			"log(magn(fft(imagen degradada)))");
	img_degradada_magnitud.get_log().display();
	//imagen de solo ruido:
	CImg<double> R(img_degradada);
	R.fill(255.0);
	ab_gaussiano_notch(R, x0, y0, espesor);
	CImgDisplay DispHruido(R, "filtro pasa banda(pasa ruido)");
	CImg<double> ruido = filtrar(img_degradada, R);
	CImgDisplay Dispimgruido(ruido, "imagen solo ruido con filtro pasante");

	//implementacion de un filtro rechaza banda que elimine las componentes de ruido:
	CImg<double> H(img_degradada);
	H.fill(255.0);
	rb_gaussiano_notch(H, x0, y0, espesor);

	CImgDisplay dispcirc(H, "filtro rechaza banda");
	CImg<double> imagen_filtrada = filtrar(img_degradada, H);
	CImgDisplay dispfiltrada(imagen_filtrada, "imagen filtrada");

	while (!disp.is_closed()) {
		disp.wait();
		if (disp.is_keyARROWUP()) {
			ab_gaussiano_notch(R, x0, y0, espesor);
			ruido = filtrar(img_degradada, R);

			rb_gaussiano_notch(H, x0, y0, espesor);
			imagen_filtrada = filtrar(img_degradada, H);

		} else if (disp.is_keyARROWDOWN()) {
			ab_gaussiano_notch(R, x0, y0, espesor);
			ruido = filtrar(img_degradada, R);

			rb_gaussiano_notch(H, x0, y0, espesor);

			imagen_filtrada = filtrar(img_degradada, H);

		} else if (disp.is_keyARROWLEFT()) {
			espesor--;
			ab_gaussiano_notch(R, x0, y0, espesor);
			ruido = filtrar(img_degradada, R);

			rb_gaussiano_notch(H, x0, y0, espesor);
			imagen_filtrada = filtrar(img_degradada, H);
			cout << "espesor: " << espesor << endl;
		} else if (disp.is_keyARROWRIGHT()) {
			espesor++;
			ab_gaussiano_notch(R, x0, y0, espesor);
			ruido = filtrar(img_degradada, R);

			rb_gaussiano_notch(H, x0, y0, espesor);
			imagen_filtrada = filtrar(img_degradada, H);
			cout << "espesor: " << espesor << endl;
		}
		cout << "ECM entre imagen limpia e imagen filtrada: "
				<< img_limpia.MSE(imagen_filtrada) << endl;
		H.display(dispcirc);
		dispcirc.set_title("filtro que se aplica");

		imagen_filtrada.display(dispfiltrada);
		dispfiltrada.set_title("imagen filtrada");

		R.display(DispHruido);
		DispHruido.set_title("filtro pasa banda(pasa ruido)");
		ruido.display(Dispimgruido);
		Dispimgruido.set_title("imagen solo ruido con filtro pasante");
	}
	return 0;
}
