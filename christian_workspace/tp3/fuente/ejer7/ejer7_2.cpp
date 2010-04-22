/*
 * ejer7_2.cpp
 *
 *  Created on: 17/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> a("../../imagenes/ej7b.tif");
	CImgDisplay disp1, disp2, disp3;

	a.get_histogram(255).display_graph(disp2, 3);
	CImg<unsigned char> b(a);
	CImg<unsigned char> c(a);

	//TODO: hacer siguiendo los pasos del libro.... mucho tiempo!
	/* usamos el laplaciano para ver mejor los detalles
	 * La mascara del laplaciando viene dada por -1 -1 -1
	 * 											 -1  8 -1
	 * 											 -1 -1 -1
	 * */
	b=a.get_convolve(generar_mascara_PA_suma0 <unsigned char > (2));

	//como el coeficiente central de la mascara es positivo se suma el laplaciano con la imagen original
	c=sumar<CImg <unsigned char> >(a,b);

	//la imagen se ve con mucho ruido en c por tanto habria que aplicar un filtro de mediana,
	// pero eso no es recomendable por ser no lineal y es inaceptable en medicina...
	// una alternativa es usar una msacara formada por una version suavizada del gradiente de la
	// imagen original

	//smooth the gradient
	//multiply by the laplacian

	//eses resultado agregarselo a la original


	//usamos el gradiente para resaltar los bordes

	//una version disfuminada del gradiente de la imagen sera usada para enmascarar la imagen del laplaciano.

	//luego se incrementa el rango dinamico de los niveles de grises usando una transformacion de nivel de grises


	//filtrado con una mascara de 5x5

CImgList <unsigned char> lista(a, b, c);
lista.display(disp1);
	while (!disp1.is_closed()) {
		disp1 .wait();
	}
	return 0;
}
