#include <iostream>
#include <CImg.h>
#include "../lib2/lut.h"
//#include "../lib2/op_aritmeticos.h"

using namespace std;
using namespace cimg_library;

int main() {

	CImg<unsigned char> im1, im2;
	CImg<unsigned char> imagenblanca(256, 256, 1, 1);
	CImg<unsigned char> imagennegra(256, 256, 1, 1);

	imagenblanca.fill(255);
	imagennegra.fill(0);
	CImgList<unsigned char> lista(imagennegra, imagenblanca, restar<CImg<
			unsigned char> > (imagenblanca, imagennegra, true));
	CImgDisplay dis(lista, "resta de imagen - imagen blanca-imagen negra");

	CImgList<unsigned char> listai(imagennegra, imagenblanca, restar<CImg<
				unsigned char> > (imagenblanca, imagennegra, true));
		CImgDisplay disi(listai, "resta de imagen - imagen negra-imagen blanca");

	im1.load("../../imagenes/letras1.tif"); //cargo imagenes
	im2.load("../../imagenes/letras2.tif");

	CImgList<unsigned char> lista1(im1, im2, restar<unsigned char> (im1,
			im2, true)); //armo una lista con las imagenes y la resta de las mismas
	CImgDisplay disp1(lista1,
			"resta de imagenes letras1 y letras 2 - normalizado"); //muestreo en un display

	CImgList<unsigned char> lista2(im1, im2, restar<unsigned char> (im1,
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

	CImgList<unsigned char> lista5(im1, im1, restar<unsigned char> (im1,
			im1, false));
	CImgDisplay disp5(lista5, "resta de imagen con si misma - NO normalizado"); //muestreo en un display

	CImgList<unsigned char> lista6(im1, im1, restar<unsigned char> (im1,
			im1, false));
	CImgDisplay disp6(lista6, "resta de imagen con si misma - NO normalizado"); //muestreo en un display

	while (!disp1.is_closed()) {
	}
	return 0;
}
