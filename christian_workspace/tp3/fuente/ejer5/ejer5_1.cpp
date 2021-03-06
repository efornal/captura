/*
 * ejer5_1.cpp
 *
 *  Created on: 17/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib3/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	// filtros pasa altos
	CImg<double> imagen("../../imagenes/camaleon.tif");

	/* POSTA:
	 * * Si la suma de los elemnetos de la mascara es 1 no elimina zonas homogenas
	 * * El resultado de aplicar la convolucion o la correlacion con una mascara es el mismo solo si la
	 * mascara es simetrica.
	 * * En el caso de usar una mascara no simetrica -> se puede hacer correlate o sino se rota 90 grados la imagen
	 * y se hace convolve.. ambos en este caso y procediendo de dicha manera arrojaran los mismos resultados
	 * */
	CImgDisplay disp1, disp2, disp3, disp4, disp5;
	imagen.display(disp1);
	disp1.set_title("imagen original");
	CImg<double> mascara1 = generar_mascara_PA_suma1<double> (1);
	CImg<double> mascara2 = generar_mascara_PA_suma1<double> (2);
	CImg<double> mascara3 = generar_mascara_PA_suma1<double> (3);

	imagen.get_convolve(mascara1, 1).display(disp2);
	disp2.set_title("mascara tipo 1 con suma 1");

	imagen.get_convolve(mascara2, 1).display(disp3);
	disp3.set_title("mascara tipo 2 con suma 1");

	imagen.get_convolve(mascara3, 1).display(disp4);
	disp4.set_title("mascara tipo 3 con suma 1");

	CImg<double> aux(imagen);
	aux.convolve(mascara1);
	cimg_forXY(aux, x, y)
		{
			if (aux(x, y) < 0)
				aux(x, y) = 0;
		}
	aux.normalize(0, 255).display(disp5);
	disp5.set_title("sacando los valores negativos de imagen con mascara 1");
	while (!disp1.is_closed()) {
	}
	return 0;
}
