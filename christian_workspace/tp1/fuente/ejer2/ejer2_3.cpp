//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	CImg<float>
			im0(
					"../../imagenes/camino.tif");
	CImg<float>
			im1(
					"../../imagenes/rostro0.png"); //cargo imagen
	CImg<float>
			im2(
					"../../imagenes/tablero.png"); //cargo imagen

	CImgList<float> listaimg(im0, im1, im2);

	listaimg.print();

	char parametros_axis[4] = { 'x', 'y', 'z', 'c' };
	char parametros_align[4] = { 'p', 'c', 'n'};

	for (int i = 0; i < 4; i++) {
		CImgDisplay dis1;
		listaimg.display(dis1, true, parametros_axis[i], 'p');
		while (!dis1.is_closed() && !dis1.is_keyQ()) {
		}
	}

	for (int i = 0; i < 3; i++) {
			CImgDisplay dis1;
			listaimg.display(dis1, true, 'x', parametros_align[i]);
			while (!dis1.is_closed() && !dis1.is_keyQ()) {
			}
	}
	return 0;
}
