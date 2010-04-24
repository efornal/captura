/*
 * ejer6_1.cpp
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
	 2 - Pensá en (R,G,B) como las coordenadas (x,y,z) de un punto dentro del cubo unitario. Si segmentas estrictamente ese color entonces preguntas si cada pixel es igual al      color a segmentar o no. Para darle más flexibilidad hay q dejar pasar los colores que son "parecidos" a (R,G,B), es decir a los puntos que están cerca a (R,G,B) en el         cubo unitario; es decir, los puntos que están dentro de la esfera con centro (R,G,B) y un radio de tolerancia.
	 3 - Por cada pixel leído con componentes (r,g,b) calculas la distancia a (R,G,B)
	 4 - Ahí va el cógido:

	 CImg<tipo> segmentaRGB(CImg<tipo>img, float radio_tol, float R, float G, float B,float *color){
	 radio_tol*=radio_tol;
	 float distancia2,r,g,b;
	 R/=256.f, G/=256.f, B/=256.f; // centro de la esfera
	 CImg<tipo> img_seg=img.normalize(0,1);
	 cimg_forXY(img,x,y){
	 r=img(x,y,0,0), g=img(x,y,0,1), b=img(x,y,0,2);
	 distancia2=(r-R)*(r-R)+(g-G)*(g-G)+(b-B)*(b-B);
	 if(distancia2>radio_tol){
	 img_seg(x,y,0,0)=color[0];
	 img_seg(x,y,0,1)=color[1];
	 img_seg(x,y,0,2)=color[2];
	 }
	 }
	 return img_seg;
	 }

	 En HSI: en vez de unn cubo unitario a tenes un plano, y en vez de una esfera tenes un rectángulo.
	 Si alguien sabe como corno usar el histograma para q ayud en estos casos q me diga!
	 Salu2
	 *
	 * */
	//a---------------------------------------------------------------------------------------
	//cargue la imagen futbol.jpg
	CImg<float> imagen("../../imagenes/futbol.jpg");
	CImgDisplay disp1(imagen, "imagen de futbol", 0);
	//b---------------------------------------------------------------------------------------
	// tome una muestra representativa del color a segmentar y calcule el centro de la esfera
	// (valor medio de cada compoennete)
	while (!disp1.is_closed()) {
		disp1.wait();
	}

	return 0;
}
