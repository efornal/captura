/*
 * parcial2010.cpp
 *
 *  Created on: 03/06/2010
 *      Author: Christian Pfarher
 */

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>

#include "../../../tp7/fuente/lib7/CPDSI_segmentacion.h"
#include "../../../tp7/fuente/lib7/segmentacion.h"
#include "../libparcial2010/comunes.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename =
			cimg_option("-f", "../../imagenes/imgstrain/blanco_5.jpg",
					"ruta archivo imagen");
	CImg<float> imagen_color(filename);
	CImg<float> imagen(filename);
	imagen = imagen.channel(0);
	CImgDisplay disp1(imagen, "imagen");
	int x = 0;
	int y = 0;
	float tolerancia = 2.0;
	int cantidad_vecinos = 4;

	CImg<float> imagen_segmentada = region_growing(imagen, x, y, tolerancia,
			cantidad_vecinos);
	CImgDisplay ds(imagen_segmentada,
			"imagen segmentada por crecimiento de regiones");

	//imagen segmetnada es una imagen binaria.... ahora me fijo cuanto hay de blanco...
	int cantidad = contar_blancos<float> (imagen_segmentada);
	cout << "cant blancos: " << cantidad << endl;
	cout << "es copa alta: " << es_copa_alta(cantidad) << endl;

	//corto un pedazo de la imagen hasta y=236 para hacer la det. con hough de donde empieza el vino
	//me aseguro que para 236 no estoy cortando mal la copa
	CImg<float> imagen_cortada = imagen.get_crop(0, 0, imagen.width(), 236);
	imagen_cortada.display();
	CImgDisplay dc(imagen_cortada);

	CImgDisplay disp2(imagen_segmentada, "imagen segmentada");

	CImg<float> original_segmentada = binaria_a_original(imagen_segmentada,
			imagen);

	//CImgDisplay disp3(original_segmentada, "imagen orig. segmentada");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//det. hough
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CImg<float> imagen_para_houge(imagen_cortada); //solo para claridad despues arreglar es un desastre...

	const float umbral = cimg_option("-umbral", 4.0, "umbral");
	const int
			direccion =
					cimg_option ("-direccionborde", 90, "direccion borde a buscar - -99 implica todas las direcciones");
	const int cant_maximos =
			cimg_option("-cantmaximos", 20, "cantidad de maximos a detectar");
	int tol_grados = cimg_option ("-tolgrados", 0, "tolerancia en grados");

	CImg<double> img_bordes = aplicar_sobel<double> (imagen_para_houge, umbral,
			true); //img_bordes es binaria y tiene valores entre 0 y 255...

	//aplico la transf de hough:
	CImg<double> HOUGH_IMG_BORDES = hough_directa(img_bordes); // aplico la transformada

	vector<double> posiciones_maximos = obtener_maximos(HOUGH_IMG_BORDES,
			cant_maximos, direccion, tol_grados);

	CImg<double> maxs(imagen_para_houge); //imagen que voy a usar para dibujar maximos
	//luego se lehace la inversa de hough a maxs para ver las lineas
	maxs.normalize(0, 255);
	maxs.fill(0.0);

	for (unsigned int i = 0; i < (posiciones_maximos.size() - 1); i += 2) {
		//cout << "i: " << i << "   i+1: " << i + 1 << endl;
		maxs(posiciones_maximos[i], posiciones_maximos[i + 1]) = 255.0;
		/*cout << "maximos (x,y)= (" << posiciones_maximos[i] << ", "
		 << posiciones_maximos[i + 1] << ")" << endl;*/
	}
	CImg<double> deteccion = hough_inversa(maxs);

	//muestro
	//CImgDisplay d4(maxs, "maximos detectados");
	CImgDisplay disp211(deteccion, "inversaHough(maximos)");

	////////////////////////////////////////////////////////////////////////////////////////////
	//luego de hough: TOMO LA LINEA QUE ESTA MAS CERCA DEL Y=0 Y LA QUE ESTA MAS LEJOS DE Y=0
	//pasandole deteccion  a las fucnioens de obtener ysuperior ei nferior
	////////////////////////////////////////////////////////////////////////////////////////////
	deteccion.display("deteccion");
	int superior = obtener_Y_superior(deteccion);
	int inferior = obtener_Y_inferior(deteccion);
	cout << endl << "Superior: " << superior << "   inferior: " << inferior
			<< endl; //ya tengo los limites de la copa en la imagen recortada ojo!!!

	//ahora hallar el nivel del vino...
	//deteccion de color para discriminar blanco y tinto!! falta

	//agarro ese pedazo ahora entre superior e inferior lo corto y detecto bordes nuevamente para detectar el nivel del vino.
	CImg<float> parte_vino = imagen_color.get_crop(0, superior, imagen.width(),
			inferior).display();
	//detecto el nivel de vino nuevamente en la imagen recortdaa
	CImgDisplay ddddd(parte_vino, "parte vino ver");
	//**************************************************************************************
	//**************************************************************************************
	//hago crecimineto de region a partir del medio de la imagen....
	int uu = 30.0;
	CImg<float> parte_vino_seg = aplicar_sobel(parte_vino, uu, true);
	CImgDisplay disparte_vino(parte_vino_seg);

	/*aplicarle houg a parte_vino_seg
	 */

	while (!disp1.is_closed()) {
		disp1.wait();

	}
	return 0;
}
