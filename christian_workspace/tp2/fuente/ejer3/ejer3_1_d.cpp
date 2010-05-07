#include <iostream>
#include <CImg.h>
#include "../lib2/lut.h"
//#include "../lib2/op_aritmeticos.h"
using namespace std;
using namespace cimg_library;
// POSTA: al dividir la imagen por sigo misma daria 1 -> por tanto es casi negro (el ojo no diferencia entre 0 y 1 aca..

// FIXME: que pasa con lo que sale el pequenio borde? -> porque como esta dividiendo por cero sale eso?

int main() {

	CImg<unsigned char> im1, im2;

	im1.load("../../imagenes/letras1.tif"); //cargo imagenes
	im2.load("../../imagenes/img.tif");

	CImgList<unsigned char> lista1(im1, im2, dividir<unsigned char>(im1, im2, true)); //armo una lista con las imagenes y la multiplicar de las mismas
	CImgDisplay disp1(lista1,
			"divide las imagenes letras1 y letras 2 - normalizado"); //muestreo en un display

	CImgList<unsigned char> lista2(im1, im2, dividir<unsigned char>(im1, im2, false));
	CImgDisplay disp2(lista2,
			"divide las imagenes letras1 y letras 2 - NO normalizado"); //muestreo en un display


	CImgList<unsigned char> lista3(im1, negativo(im1), dividir<unsigned char>(im1, negativo(
			im1), true));
	CImgDisplay disp3(lista3,
			"divide las imagenes letras 1 y su negativo - normalizado"); //muestreo en un display

	CImgList<unsigned char> lista4(im1, negativo(im1), dividir<unsigned char>(im1, negativo(
			im1), false));
	CImgDisplay disp4(lista4,
			"divide las imagenes letras1 y su negativo - NO normalizado"); //muestreo en un display

	CImgList<unsigned char> lista5(im1, im1, dividir<unsigned char>(im1, im1, false));
	CImgDisplay disp5(lista5, "divide la imagen por si misma - NO normalizado"); //muestreo en un display

	CImgList<unsigned char> lista6(im1, im1, dividir<unsigned char>(im1, im1, false));
	CImgDisplay disp6(lista6, "divide la imagen por si misma - NO normalizado"); //muestreo en un display

	while (!disp1.is_closed()) {
	}
	return 0;
}
