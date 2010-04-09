#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

/*FIXME:
 * ver las graficas cuyos titulos son:
 * "suma de imagenes letras1 y su negativo - NO normalizado"
 * "suma de imagenes letras 1 y su negativo - normalizado"
 * porque el resultado en una y otra sale de diferentes colores? no deberia dar negro?
 *
 * Se puede mostrar informacion de la imagen en la lista similar a display? (coordenada y valores de intensidad)
 * ya que si despliego las imagenes con display no me muestra nada
 */

/*POSTA :Al sumar la imagen con su negativo queda negra porque si valor de imagen vale 255, el negativo del mismo seria "-255"
 * y al sumar 255-255=0 ->negro (idem para cualquier otro valor)
 * */
int main() {

	CImg<unsigned char> im1, im2;
	CImg<unsigned char> imagenblanca(256, 256, 1, 1);
	CImg<unsigned char> imagennegra(256, 256, 1, 1);

	imagenblanca.fill(255);
	imagennegra.fill(0);
	CImgDisplay display1;
	imagenblanca.display(display1);
	display1.set_title("primera imagen a sumar");
	sleep(5);
	imagennegra.display(display1);
	display1.set_title("segunda imagen a sumar");
	sleep(5);
	sumar(imagenblanca, imagennegra, true).display(display1);
	display1.set_title("suma normalizada");
	sleep(5);
	sumar(imagenblanca, imagennegra, false).display(display1);
	display1.set_title("suma no normalizada");
	while (!display1.is_closed()) {
	}

	im1.load("../../imagenes/letras1.tif"); //cargo imagenes
	im2.load("../../imagenes/letras2.tif");

	CImgList<float> lista1(im1, im2, sumar<CImg<float> > (im1, im2, true)); //armo una lista con las imagenes y la suma de las mismas
	cout << "lista 1 (normalizada la suma): " << lista1.print() << endl;
	CImgDisplay disp1(lista1,
			"suma de imagenes letras1 y letras 2 - normalizado"); //muestreo en un display


	CImgList<float> lista2(im1, im2, sumar<CImg<float> > (im1, im2, false));
	CImgDisplay disp2(lista2,
			"suma de imagenes letras1 y letras 2 - NO normalizado"); //muestreo en un display
	cout << "lista 2: (NO normalizada la suma)" << lista2.print() << endl;

	CImgList<float> lista3(im1, negativo(im1), sumar<CImg<float> > (im1,
			negativo(im1), true));
	CImgDisplay disp3(lista3,
			"suma de imagenes letras 1 y su negativo - normalizado"); //muestreo en un display
	cout << "lista 3: (Normalizada la suma) " << lista3.print() << endl;

	CImgList<float> lista4(im1, negativo(im1), sumar<CImg<float> > (im1,
			negativo(im1), false));
	CImgDisplay disp4(lista4,
			"suma de imagenes letras1 y su negativo - NO normalizado"); //muestreo en un display
	cout << "lista 4: (no normalizada la suma" << lista4.print() << endl;

	CImgList<float> lista5(im1, im1, sumar<CImg<float> > (im1, im1, false));
	CImgDisplay disp5(lista5, "suma de imagenes con si misma - NO normalizado"); //muestreo en un display

	CImgList<float> lista6(im1, im1, sumar<CImg<float> > (im1, im1, false));
	CImgDisplay disp6(lista6, "suma de imagenes con si misma - NO normalizado"); //muestreo en un display

	while (!disp1.is_closed()) {
	}
	return 0;
}
