#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;
//FIXME: que pasa con las imagenes? sale cualqueri cosa ?? coincidera que todo es ruido porque no hay nada que coincide?
//al multiplicar la imagen por si misma da cualquier cosa ->??? o sea?
int main() {

	CImg<unsigned char> im1, im2;

	im1.load("../../imagenes/letras1.tif"); //cargo imagenes
	im2.load("../../imagenes/img.tif");

	CImgList<unsigned char> lista1(im1, im2, multiplicar(im1, im2, true)); //armo una lista con las imagenes y la multiplicar de las mismas
	CImgDisplay disp1(lista1,
			"multiplica la imagen letras1 y letras 2 - normalizado"); //muestreo en un display

	CImgList<unsigned char> lista2(im1, im2, multiplicar(im1, im2, false));
	CImgDisplay disp2(lista2,
			"multiplica la imagen letras1 y letras 2 - NO normalizado"); //muestreo en un display


	CImgList<unsigned char> lista3(im1, negativo(im1), multiplicar(im1,
			negativo(im1), true));
	CImgDisplay disp3(lista3,
			"multiplica la imagen letras 1 y su negativo - normalizado"); //muestreo en un display

	CImgList<unsigned char> lista4(im1, negativo(im1), multiplicar(im1,
			negativo(im1), false));
	CImgDisplay disp4(lista4,
			"multiplica la imagen letras1 y su negativo - NO normalizado"); //muestreo en un display

	CImgList<unsigned char> lista5(im1, im1, multiplicar(im1, im1, false));
	CImgDisplay disp5(lista5,
			"multiplica la imagen por si misma - NO normalizado"); //muestreo en un display

	CImgList<unsigned char> lista6(im1, im1, multiplicar(im1, im1, false));
	CImgDisplay disp6(lista6,
			"multiplica la imagen por si misma - NO normalizado"); //muestreo en un display

	while (!disp1.is_closed()) {
	}
	return 0;
}
