/*
 * ejer6_2.cpp
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
	/* La segmentacion es un proceso que divide la imagen en regiones. Este ejercicio tiene por
	 * objetivo segmentar algun color en particular en una imagen en el modelo RGB
	 * Segmentacion en RGB. En este modelo se segmenta por el metodo de las rodajas de color con un
	 * modelo esferico. .*/

	/*en RGB:
	 1 - Tomas el color de un pixel (R,G,B) el cual queres segmentar.
	 2 - Pensá en (R,G,B) como las coordenadas (x,y,z) de un punto dentro del cubo unitario. Si segmentas estrictamente ese color
	 entonces preguntas si cada pixel es igual al      color a segmentar o no.
	 Para darle más flexibilidad hay q dejar pasar los colores que son "parecidos" a (R,G,B), es decir a los puntos que están cerca
	 a (R,G,B) en el         cubo unitario; es decir, los puntos que están dentro de la esfera con centro (R,G,B)
	 y un radio de tolerancia.
	 3 - Por cada pixel leído con componentes (r,g,b) calculas la distancia a (R,G,B)

	 En HSI: en vez de unn cubo unitario a tenes un plano, y en vez de una esfera tenes un rectángulo.
	 Si alguien sabe como corno usar el histograma para q ayud en estos casos q me diga!
	 Salu2
	 *
	 * */
	//a---------------------------------------------------------------------------------------
	//cargue la imagen futbol.jpg


	CImg<float> imagen("../../imagenes/futbol.jpg");
	CImgDisplay disp1(imagen, "imagen de futbol", 0);
	CImgDisplay dish1, dish2, dish3, disp_seg;
	CImg<float> imagen_HSI = imagen.get_RGBtoHSI(); //obtengo componenes HSI

	CImg<float> H = imagen_HSI.get_channel(0);
	CImg<float> S = imagen_HSI.get_channel(1);
	CImg<float> I = imagen_HSI.get_channel(2);
	H.print();
	S.print();
	visualizar_HSI<float> (H, S, I); //visualizo las componenest HSI, HSI estan modificads ahora

	CImg<float> Ho = imagen_HSI.get_channel(0); // ESTAS COMPONENTES nose van  a moddificar
	CImg<float> So = imagen_HSI.get_channel(1); // son las originales
	CImg<float> Io = imagen_HSI.get_channel(2);

	CImgDisplay disp2(H, "componenete H");
	CImgDisplay disp3(S, "componenete S");

	int posx = 149, posy = 135;
	float color_original[] = { imagen(posx, posy, 0, 0), imagen(posx, posy, 0,
			1), imagen(posx, posy, 0, 2) };

/*	Ho.get_histogram(360).display_graph(dish1, 3); //muestro los histogramas de H, S e I respectivamente
	dish1.set_title("canal H");
	So.get_histogram(1, 0, 1).display_graph(dish2, 3);
	dish2.set_title("canal S");
	Io.get_histogram(1, 0, 1).get_histogram(255).display_graph(dish3, 3);
	dish3.set_title("canal I");*/

	float tol = 0.5; //toleracnia
	segmentaHSI<float> (imagen, tol, Ho(posx, posy, 0, 0),
			So(posx, posy, 0, 0), color_original).display(disp_seg);

	disp1.set_title(
			"use la ruedita del raton y el click - C para alternar entre color verdadero y color seteado");
	bool color_verd = false;

	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyC()) {//cambia a color verdadero
			color_verd = !color_verd;
		}
		if (disp1.button()) {
			posx = disp1.mouse_x();
			posy = disp1.mouse_y();
			color_original[0] = imagen(posx, posy, 0, 0);
			color_original[1] = imagen(posx, posy, 0, 1);
			color_original[2] = imagen(posx, posy, 0, 2);
		}
		/*segmentaHSI<float> (imagen, tol + (disp1.wheel() * 0.01), Ho(posx,
				posy, 0, 0), So(posx, posy, 0, 0), color_original, color_verd).display(
				disp_seg);*/
		cout << "Tolerancia: " << tol + (disp1.wheel() * 0.01) << endl;
		disp_seg.set_title("imagen segmentada");
	}

	return 0;
}
