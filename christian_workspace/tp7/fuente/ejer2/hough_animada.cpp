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

using namespace std;
using namespace cimg_library;
/*
 * http://users.cs.cf.ac.uk/Paul.Rosin/CM0311/dual2/hough.html
 * */
int main(int argc, char **argv) {
	CImg<double> img(500, 500, 1, 1, 0); //Creo imagen negro
	img.normalize(0, 255);
	img(img.width() / 2, img.height() / 2, 0, 0) = 255.0; //punto blanco en el centro
	CImgDisplay disp(img, "plano rho (y), tita (x -90 a 90)");
	/*cimg::dialog("Animada Hough", "Realiza la transformada inversa de Hough a partir de la imagen que se muestra \n"
			"se supone que la imagen que se muestra con el punto seria lo que dejaria luego de pasar un detector de \n"
			"bordes y un thresold para que quede solo ese punto", "Aceptar");*/
	CImg<double> inversa = hough_inversa(img); //transofrmada inversa del punto
	CImgDisplay disp1(inversa, "transformada inversa de Hough de la imagen");
	int posx, posy;
	while (!disp.is_closed()) {
		disp.wait();
		if (disp.is_event()){
			posx=disp.mouse_x();
			posy=disp.mouse_y();
			img.fill(0); //borro la imagen
			img(posx, posy)=255; //dibujo el punto segun el mouse

			img.display(disp);
			disp.set_title("plano rho (y), tita (x -90 a 90)");

			inversa=hough_inversa(img);
			inversa.display(disp1);
			disp1.set_title("transformada inversa de Hough de la imagen");
		}

	}
	return 0;
}
