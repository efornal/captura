#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

/* POSTA:ver las graficas cuyos titulos son:
 * "suma de imagenes letras1 y su negativo - NO normalizado"
 * "suma de imagenes letras 1 y su negativo - normalizado"
 * Notar que cuando normalizo queda gris esto se debe a lo siguiente:
 * La suma de una imagen con su negativo da una figura blanca (255). Ahora, la implementación correcta
 * de la suma es (Img1(i,j)+Img2(i,j))/2 con lo que te debería dar el gris intermedio de la escala [0-255].
 *
 * No, siempre tenes que normalizar el negativo, porque los valores "negativos" ( < 0 ) no existen en una imagen.
 * Si el valor es blanco (255) el negativo es negro (0) y viceversa.
 */

int main() {

	CImg<unsigned char> im1, im2;
	CImg<unsigned char> imagenblanca(256, 256, 1, 1);
	CImg<unsigned char> imagennegra(256, 256, 1, 1);

	imagenblanca.fill(255);
	imagennegra.fill(0);
	CImgDisplay display1;
	imagenblanca.display(display1);
	display1.set_title("im1+");
	sleep(3);
	negativo(imagenblanca).display(display1);
	display1.set_title("+negativo (im1)");
	sleep(3);
	sumar(imagenblanca, negativo(imagenblanca), true).display(display1);
	display1.set_title("= (suma normalizada)");
	sleep(3);
	sumar(imagenblanca, negativo(imagenblanca), false).display(display1);
	display1.set_title("= (suma no normalizada)");
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
