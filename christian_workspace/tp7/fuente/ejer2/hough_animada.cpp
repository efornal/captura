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
	//cout<<"use teclas X y Y para fijar el sentido de X y Y respectivamente"<<endl;
	img(img.width() / 2, img.height() / 2, 0, 0) = 255.0; //punto blanco en el centro
	CImgDisplay disp(img, "plano rho (y), tita (x -90 a 90)");
	CImg<double> inversa = hough_inversa(img); //transofrmada inversa del punto
	CImgDisplay disp1(inversa, "transformada inversa de Hough de la imagen");
	int posx, posy;
	bool fija_x = false;
	bool fija_y = false;
	//todo: ojo hay unas indefinicinoes a arreglar no simpre funca bien esto...
	while (!disp.is_closed()) {
		disp.wait();
		if (disp.is_event()) {
			if (disp.is_keyX()) {
				fija_x = !fija_x;
				cout << "Fija_x: " << fija_x << endl;
			} else if (disp.is_keyY()) {
				fija_y = !fija_y;
				cout << "Fija_y: " << fija_y << endl;
			}
			if (!fija_x) { //si no esta fijada x
				posx=disp.mouse_x();
			}
			if (!fija_y) { // si no esta fijada y
				if (disp.mouse_y() == disp.width()-1) {
					posy = disp.mouse_y() - 1.0;
				} else if (disp.mouse_y() == 0) {
					posy = 1.0;
				} else {
					posy = disp.mouse_y();
				}
			}
			img.fill(0); //borro la imagen
			img(posx, posy) = 255; //dibujo el punto segun el mouse

			img.display(disp);
			disp.set_title("plano rho (y), tita (x -90 a 90)");
			inversa = hough_inversa(img);
			inversa.display(disp1);
			disp1.set_title("transformada inversa de Hough de la imagen");
		}

	}
	return 0;
}
