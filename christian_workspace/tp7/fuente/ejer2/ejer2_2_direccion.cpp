/*
 * ejer1_1y2.cpp
 *
 *  Created on: 22/05/2010
 *      Author: christian
 */

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>
#include "../lib7/CPDSI_segmentacion.h"
#include "../lib7/segmentacion.h"
#include "../../../tp2/fuente/lib2/operadores_logicos.h"

using namespace std;
using namespace cimg_library;
/*
 * http://users.cs.cf.ac.uk/Paul.Rosin/CM0311/dual2/hough.html
 * */
int main(int argc, char **argv) {
	const char *filename = cimg_option("-f", "../../imagenes/snowman.png",
			"ruta archivo imagen");

	const float umbral = cimg_option("-umbral", 50.0, "umbral");
	const int
			direccion =
					cimg_option ("-direccionborde", -99, "direccion borde a buscar - -99 implica todas las direcciones");
	const int cant_maximos =
			cimg_option("-cantmaximos", 50, "cantidad de maximos a detectar");
	CImg<double> img(filename); //imagen original
	//img.rotate(90);

	//aplicar deteccion de bordes a la imagen
	CImg<double> img_bordes = aplicar_sobel<double> (img, umbral, true); //img_bordes es binaria y tiene valores entre 0 y 255...

	//aplico la transf de hough:
	CImg<double> HOUGH_IMG_BORDES = hough_directa(img_bordes); // aplico la transformada

	vector<double> posiciones_maximos = obtener_maximos(HOUGH_IMG_BORDES,
			cant_maximos, direccion);

	CImg<double> maxs(img); //imagen que voy a usar para dibujar maximos
	//luego se lehace la inversa de hough a maxs para ver las lineas
	maxs.normalize(0, 255);
	maxs.fill(0.0);
	for (unsigned int i = 0; i < (posiciones_maximos.size() - 1); i++) {
		maxs(posiciones_maximos[i], posiciones_maximos[i + 1]) = 255.0;
	}
	CImg<double> deteccion = hough_inversa(maxs);

	// si hago un AND entre la imagen con los bordes detectados y lo que me devolvio la inversa
	// de hough me voy a quedar co lo que realmente son bordes:

	CImg<double> deteccion_final = AND(img_bordes, deteccion);

	//muestro
	CImgList<double> lista(img, img_bordes, HOUGH_IMG_BORDES, maxs, deteccion,
			deteccion_final);
	CImgDisplay disp;
	lista.display(disp);
	disp.set_title(
			"imagen, segmentacion bordes, transformdad de bordes, maximos, inversa_hough",
			"and entre imagenes");

	CImg<> deteccion_final_coloreada = colorea_rojo(deteccion_final);
	CImgDisplay disppp(img);
	deteccion_final_coloreada.display();
	//todo: ver como sobreimprimir en la imagen los bordes.. por ahora uso compiz y listo :)
	/*todo: como corno hago lo que dice el ejercicio de ver solamente en un angulo y con long. fijadas por le usuario??
	 * tengo que detectar maximos solamente en esa direccion?? o sea? no se...*/

	/*	img.draw_grid(-50*100.0f/image.width(),-50*100.0f/256,0,0,false,true,black,0.2f,0xCCCCCCCC,0xCCCCCCCC).
	 draw_axes(0,image.width()-1.0f,255.0f,0.0f,black).
	 draw_graph(image.get_shared_line(y,0,0),red,1,1,0,255,1).
	 draw_graph(image.get_shared_line(y,0,1),green,1,1,0,255,1).
	 draw_graph(image.get_shared_line(y,0,2),blue,1,1,0,255,1).
	 draw_text(30,5,"Pixel (%d,%d)={%d %d %d}",black,0,1,13,
	 main_disp.mouse_x(),main_disp.mouse_y(),val_red,val_green,val_blue).
	 draw_line(xl,0,xl,draw_disp.height()-1,black,0.5f,hatch=cimg::rol(hatch)).*/

	while (!disp.is_closed()) {
		disp.wait();
		/*img .draw_text(30, 5, "Pixel (%d,%d)", black, 0, 1, 13, disp.mouse_x(),
		 disp.mouse_y());*/
	}
	return 0;
}
