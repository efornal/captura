/*
 * ejer2_3.cpp
 *
 *  Created on: 16/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib3/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen("../../imagenes/tablero.png");

	CImg<float> resultado_correlacion = imagen.get_correlate(generar_mascara3x3<float> ());
	CImg<float> resultado_convolucion = imagen.get_convolve(generar_mascara3x3<float> ());

	CImgDisplay disp1, disp2, disp3;
	imagen.display(disp1);
	disp1.set_title("imagen original");

	resultado_convolucion.display(disp2);
	disp2.set_title("imagen convolucion con la mascara");

	resultado_correlacion.display(disp3);
	disp3.set_title("imagen correlacionada con la mascara");

	generar_mascara3x3<float> ().normalize(0, 255).display("mascara");
	cout<<"Error cuadratico total: "<<resultado_convolucion.MSE(resultado_correlacion);
	/* El error cuadratico total es 0 porque hacer la convolucion o la correlacion con la mascara
	 * (simetrica) es lo mismo
	 * */
	while (!disp1.is_closed()) {
	}
	return 0;
return 0;
}
