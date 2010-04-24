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

	CImg<float> imagen_HSI = imagen.get_RGBtoHSI();

	CImg<float> H = imagen_HSI.get_channel(0);
	CImg<float> S = imagen_HSI.get_channel(1);
	CImg<float> I = imagen_HSI.get_channel(2);
	visualizar_HSI<float> (H, S, I);
	CImgDisplay disp2(H, "componenete H");
	CImgDisplay disp3(S, "componenete S");
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
