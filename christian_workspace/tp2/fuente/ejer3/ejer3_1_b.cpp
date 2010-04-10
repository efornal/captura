#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

int main() {

	CImg<unsigned char> im1, im2;
	CImg<unsigned char> imagenblanca(256, 256, 1, 1);
	CImg<unsigned char> imagennegra(256, 256, 1, 1);

	imagenblanca.fill(255);
	imagennegra.fill(0);

	CImgDisplay display1;
	imagennegra.display(display1);
	display1.set_title("im1+");
	sleep(3);
	imagenblanca.display(display1);
	display1.set_title("-negativo (im1)");
	sleep(3);
	sumar(imagennegra, imagenblanca, true).display(display1); //FIXME: seria lo mismo que poner en vez de imagenblanca negativo(imagen_negra) pero por eso mande a consulta para ver en qu ele estoy herrando
	display1.set_title("= (resta normalizada)");
	sleep(3);
	sumar(imagennegra, imagenblanca, false).display(display1);
	display1.set_title("= (resta no normalizada)");
	while (!display1.is_closed()) {
	}

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

	CImgList<unsigned char> lista5(im1, im1, restar<CImg<unsigned char> > (im1,
			im1, false));
	CImgDisplay disp5(lista5, "resta de imagen con si misma - NO normalizado"); //muestreo en un display

	CImgList<unsigned char> lista6(im1, im1, restar<CImg<unsigned char> > (im1,
			im1, false));
	CImgDisplay disp6(lista6, "resta de imagen con si misma - NO normalizado"); //muestreo en un display

	while (!disp1.is_closed()) {
	}
	return 0;
}
