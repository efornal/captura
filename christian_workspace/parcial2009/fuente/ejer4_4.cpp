/*
 * ejer4_1y2.cpp
 *
 *  Created on: 29/05/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../../tp4/fuente/lib4/proc_color.h"
#include "../../tp3/fuente/lib3/mask.h"
#include "../../tp6/fuente/lib6/restauracion.h"
#include "../../tp7/fuente/lib7/segmentacion.h"
#include "../../tp7/fuente/lib7/CPDSI_segmentacion.h"


using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	const char
			*filename =
					cimg_option("-f", "./CPDSI_Parcial_Practica_2009/corrientes_ruidogris.jpg",
							"ruta archivo imagen");
	int tam_mascara = cimg_option("-sizemask", 9, "Tam de la mascara");
	int d = cimg_option("-dfiltro", 1.0, "d del filtro media alfa recortado");

	float threshold = cimg_option("-umbral", 5.0, "threshold");
	float tol = cimg_option("-tolerancia", 0.3, "tolerancia");
	int tam_mask_prom =
			cimg_option("-masksize", 10, "tamanio mascara promediado");
	CImg<float> imagen(filename);

	//restaurarla:
	imagen = filtrado_alfa_recortado(imagen, d, tam_mascara);

	CImgDisplay disp1(imagen, "rosas", 0);
	CImgDisplay disp2, dish1, dish2, dish3;

	// tome una muestra representativa del color a segmentar y calcule el centro de la esfera
	// (valor medio de cada compoennete)
	int posx = 149, posy = 135;

	float color_original[] = { imagen(posx, posy, 0, 0), imagen(posx, posy, 0,
			1), imagen(posx, posy, 0, 2) };

	CImg<float> img_segmentada = segmentaRGB<float> (imagen, tol, imagen(posx,
			posy, 0, 0), imagen(posx, posy, 0, 1), imagen(posx, posy, 0, 2),
			color_original);
	img_segmentada.display(disp2);
	CImg<float> resultado = img_segmentada.get_convolve(
			generar_mascara_promediadora<float> (tam_mask_prom));
	CImg<float> imagen_thresoldeada(imagen.width(), imagen.height(), 1, 1, 0);
	imagen_thresoldeada = resultado.get_threshold(threshold);
	CImgDisplay disp4(imagen_thresoldeada, "resultado thresoldeada");
	CImgDisplay dispbaja(resultado, "imagen con pasa bajos");
	CImg<float> binarizada = binarizar(imagen_thresoldeada);
	CImgDisplay dispbin(binarizada, "imagen binarizada");
	CImg<float> etiquetada = label_cc(binarizada, 1); // me va a etiquetar las regiones
	etiquetada.display();
	cout << endl << "cantidad de rosas: " << contar_diferentes(etiquetada)
			<< endl;
	disp1.set_title(
			"use la ruedita del raton y el click - C para alternar entre color verdadero y color seteado");
	bool color_verd = false;

	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyC()) {//cambia a color verdadero
			color_verd = !color_verd;
		} else if (disp1.is_keyARROWUP()) {
			threshold += 5.0;
			threshold = clipp<float> (threshold);
			cout << "Threshold: " << threshold << endl;
		} else if (disp1.is_keyARROWDOWN()) {
			threshold -= 5.0;
			threshold = clipp<float> (threshold);
			cout << "Threshold: " << threshold << endl;
		}
		if (disp1.button()) {
			posx = disp1.mouse_x();
			posy = disp1.mouse_y();
			color_original[0] = imagen(posx, posy, 0, 0);
			color_original[1] = imagen(posx, posy, 0, 1);
			color_original[2] = imagen(posx, posy, 0, 2);
		}
		img_segmentada = segmentaRGB<float> (imagen, tol + (disp1.wheel()
				* 0.01), imagen(posx, posy, 0, 0), imagen(posx, posy, 0, 1),
				imagen(posx, posy, 0, 2), color_original, color_verd);
		resultado = img_segmentada.get_convolve(generar_mascara_promediadora<
				float> (20));
		resultado.display(dispbaja);
		dispbaja.set_title("imagen con pasa bajos");
		img_segmentada.display(disp2);
		cout << "Tolerancia: " << tol + (disp1.wheel() * 0.01) << endl;
		disp2.set_title("imagen segmentada");
		imagen_thresoldeada = resultado.get_threshold(threshold);
		imagen_thresoldeada.display(disp4);
		disp4.set_title("imagen con objetos grandes");
		binarizada = binarizar(imagen_thresoldeada).display();
		binarizada.display(dispbin);
		dispbin.set_title("imagen binarizada");
		cout << endl << "cantidad de rosas: " << contar_diferentes(etiquetada)
				<< endl;
	}
	return 0;
}
