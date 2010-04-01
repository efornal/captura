#include <iostream>
#include <CImg.h>
#include "../ejer1/lib.h"

using namespace std;
using namespace cimg_library;
//FIXME: que onda con el normalizado?? el tema de los colores que quedan segun lo que sale aca..
int main() {

	CImg<unsigned char> im1, im2;

	im1.load("../../imagenes/letras1.tif"); //cargo imagenes
	im2.load("../../imagenes/letras2.tif");

	CImgList<unsigned char> lista1(im1, im2, restar<CImg<unsigned char> > (im1,
			im2, true)); //armo una lista con las imagenes y la resta de las mismas
	CImgDisplay disp1(lista1,
			"resta de imagenes letras1 y letras 2 - normalizado"); //muestreo en un display

	CImgList<unsigned char> lista2(im1, im2, restar<CImg<unsigned char> > (im1,
			im2, false));
	CImgDisplay disp2(lista2,
			"resta de imagenes letras1 y letras 2 - NO normalizado"); //muestreo en un display


	CImgList<unsigned char> lista3(im1, negativo(im1), restar<
			CImg<unsigned char> > (im1, negativo(im1), true));
	CImgDisplay disp3(lista3,
			"resta de imagenes letras 1 y su negativo - normalizado"); //muestreo en un display

	CImgList<unsigned char> lista4(im1, negativo(im1), restar<
			CImg<unsigned char> > (im1, negativo(im1), false));
	CImgDisplay disp4(lista4,
			"resta de imagenes letras1 y su negativo - NO normalizado"); //muestreo en un display

	while (!disp1.is_closed()) {
	}
	return 0;
}
