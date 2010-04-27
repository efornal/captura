/*
 * ejer5_1_d.cpp
 *
 *  Created on: 23/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen_oscura("../../imagenes/chairs_oscura.jpg"); //cargo la imagen
	CImg<float> imagen_oscura_intensidad_ecualizada(imagen_oscura);
	imagen_oscura.resize(500,500);
	imagen_oscura_intensidad_ecualizada.resize(500,500);
	int dx = imagen_oscura.width();
	int dy = imagen_oscura.height();

	CImg<float> imagen_oscura_HSI(dx, dy, 1, 3), imagen_oscura_HSI_H(dx, dy, 1,
			1), imagen_oscura_HSI_S(dx, dy, 1, 1), imagen_oscura_HSI_I(dx, dy,
			1, 1);
	imagen_oscura_HSI = imagen_oscura.get_RGBtoHSI(); //obtengo la imagen en HSI

	cimg_forXY(imagen_oscura_HSI, x, y) //obtengo componenes HSI de la imagen oscura
		{ //obtengo componenes HSI
			imagen_oscura_HSI_H(x, y, 0, 0) = imagen_oscura_HSI(x, y, 0, 0);
			imagen_oscura_HSI_S(x, y, 0, 0) = imagen_oscura_HSI(x, y, 0, 1);
			imagen_oscura_HSI_I(x, y, 0, 0) = imagen_oscura_HSI(x, y, 0, 2);
		}

	imagen_oscura_HSI_I.equalize(255); //ecuaizo solo la compoennte de intensidad

	imagen_oscura_intensidad_ecualizada = componer_imagen_hsi<float> (
			imagen_oscura_HSI_H, imagen_oscura_HSI_S, imagen_oscura_HSI_I);
	CImgDisplay disp1(imagen_oscura, "Imagen original");
	imagen_oscura_intensidad_ecualizada
			= imagen_oscura_intensidad_ecualizada.HSItoRGB();

	CImgDisplay disp4;
	imagen_oscura.get_histogram(255).display_graph(disp4, 3);
	disp4.set_title("histograma de la original");

	CImgDisplay disp3;
	imagen_oscura_intensidad_ecualizada.get_histogram(255).display_graph(disp3,
			3);
	disp3.set_title("histograma de la que se equalizo la intensidad");

	/*FIXME: equalizando solo la intensidad de una imagen en HSI y recomeponiendo se logra un efecto bueno
	 sin  tocar los que corresponde a saturacion y brillo... pero... no se ve!?
	 ver el histograma d ela original y de la ecualizada solo de intesnidad.. com se entiendE?
	 */
	CImgDisplay disp2(imagen_oscura_intensidad_ecualizada,
			"Imagen con intensidad ecualizada");
	CImg<float> imagen_chairs("../../imagenes/chairs.jpg");
	imagen_chairs.resize(500,500);
	CImgDisplay dispp(imagen_chairs, "imagen chairs");
	CImgDisplay displ;

	displ.set_title("histograma de la que se equalizo la intensidad");

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
