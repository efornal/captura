/*
 * ejer5_1_b.cpp
 *
 *  Created on: 22/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib4/proc_color.h"
using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen_oscura("../../imagenes/chairs_oscura.jpg"); //cargo la imagen

	imagen_oscura.resize(500, 500);
	int dx = imagen_oscura.width();
	int dy = imagen_oscura.height();

	CImg<float> imagen_oscura_R(dx, dy, 1, 3, 0), imagen_oscura_G(dx, dy, 1, 3,
			0), imagen_oscura_B(dx, dy, 1, 3, 0);

	descomponer_rgb <float> (imagen_oscura, imagen_oscura_R, imagen_oscura_G,
			imagen_oscura_B, false); //descompongo la imagen en 3 canales

	CImgList<float> lista(imagen_oscura_R, imagen_oscura_G,
			imagen_oscura_B);
	CImgDisplay disp1(lista, "canal R, canal G, canal B");
	CImgDisplay dispaux1(imagen_oscura);
	dispaux1.set_title("imagen oscura original");

	CImgDisplay dispaux3(imagen_oscura.get_equalize(255)); //imagen ecualizada con los 3 canales juntos
	dispaux3.set_title("imagen ecualizada con los 3 canales juntos");
	//------------------------------------------------------------
	//ecualizar cada componente por separado y mostrar:
	CImg<float> imagen_oscura_R_eq(dx, dy, 1, 3), imagen_oscura_G_eq(dx, dy, 1,
			3), imagen_oscura_B_eq(dx, dy, 1, 3);

	descomponer_rgb<float> (imagen_oscura, imagen_oscura_R_eq,
			imagen_oscura_G_eq, imagen_oscura_B_eq, true); // me devuelve los 3 canales ecualizados...

	// compongo la imagen para mostrarla:
	/*CImgList<float> lista1(, imagen_oscura_R_eq,
			imagen_oscura_G_eq, imagen_oscura_B_eq);*/ //esto lo coment porque en tendria que generar la imagen RGB ya que la funcion me la normaliza y me devuelve un solo canal... y si lo muestreo asi se va a ver _todo en rojo y va dar lugar a confusion

	CImgDisplay dispaux2(componer_imagen<float> (imagen_oscura_R_eq,
			imagen_oscura_G_eq, imagen_oscura_B_eq));
	//FIXME: en la imagen ecualizada con los canales RGB por serparado quizas esta mas nitida que en la que ecualize sin separarlos..? la sombrilla, el edificio... pero es poca la dif.

	dispaux2.set_title("imagen ecualizada por canales RGB");
	while (!disp1.is_closed()) {
	};
	return 0;
}
