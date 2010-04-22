/*
 * canales.h
 *
 *  Created on: 15/04/2010
 *      Author: christian
 */
#include<CImg.h>
#include <string>
#include <vector>
#include "../lib/CPDSI_functions.h"

using namespace std;
using namespace cimg_library;

template<class T>
CImg<T> componer_imagen(CImg<T> canal_rojo, CImg<T> canal_verde,
		CImg<T> canal_azul) {
	CImg<T> imagen(canal_rojo.width(), canal_rojo.height(), canal_rojo.depth(),
			3);
	cimg_forXY(imagen, x, y)
		{
			imagen(x, y, 0, 0) = canal_rojo(x, y);
			imagen(x, y, 0, 1) = canal_verde(x, y);
			imagen(x, y, 0, 2) = canal_azul(x, y);
		}
	return imagen;
}
template<class T>
CImg<T> invertir_HSI(CImg<T> imagen) {
	/* si era rojo tiene que ser azul....
	 * para ello modifico el canal H
	 * */
	CImg<T> imm(imagen);
	cimg_forXY(imagen, x, y)
		{
			imm(x, y, 0, 0) = ((imagen(x, y, 0, 0) / 360) * 255) + 240;

			//imm(x,y,0,0)=imagen(imagen.width()-x-1,y,0,0);

		}
	return imm;
}

CImg <float> aplicar_paleta(CImg <float> imagen, int numero_paleta = 1) {
	/* carga una paleta con nombre_paleta la aplica a la imagen pasada como parametro y
	 * devuelve la imagen con la paleta aplicada
	 * @numeropaleta=1 -> ../../paletas/bone.pal
	 * @numeropaleta=2 -> ../../paletas/cool.pal
	 * @numeropaleta=3 -> ../../paletas/copper.pal
	 * @numeropaleta=4 -> ../../paletas/gray.pal
	 * @numeropaleta=5 -> ../../paletas/hot.pal
	 * @numeropaleta=6 -> ../../paletas/hsv.pal
	 * @numeropaleta=7 -> ../../paletas/jet.pal
	 * @numeropaleta=8 -> ../../paletas/pink.pal
	 * */
	vector< vector<float> > paleta; //creo un vecotr de vecotres
	switch (numero_paleta) {
	case 1:
		cargar_paleta(paleta, "../../paletas/bone.pal");
		break;
	case 2:
		cargar_paleta(paleta, "../../paletas/cool.pal");
		break;
	case 3:
		cargar_paleta(paleta, "../../paletas/copper.pal");
		break;
	case 4:
		cargar_paleta(paleta, "../../paletas/gray.pal");
		break;
	case 5:
		cargar_paleta(paleta, "../../paletas/hot.pal");
		break;
	case 6:
		cargar_paleta(paleta, "../../paletas/hsv.pal");
		break;
	case 7:
		cargar_paleta(paleta, "../../paletas/jet.pal");
		break;
	case 8:
		cargar_paleta(paleta, "../../paletas/pink.pal");
		break;
	default:
		break;
	}

	CImg<float> imagen_con_paleta_aplicada(imagen.width(), imagen.height(), 1,
			3);
	cimg_forXY(imagen_con_paleta_aplicada, x, y)
		{ //es mas o menos una lut...
			imagen_con_paleta_aplicada(x, y, 0, 0) = paleta[imagen(x, y)][0]
					* 255.0; //canal rojo
			imagen_con_paleta_aplicada(x, y, 0, 1) = paleta[imagen(x, y)][1]
					* 255.0; //canal verde
			imagen_con_paleta_aplicada(x, y, 0, 2) = paleta[imagen(x, y)][2]
					* 255.0; //canal azul
		}
	return imagen_con_paleta_aplicada;
}
template<class T>
CImg<T> get_binary(CImg<T> imagen) {
	//convierte una imagen en escala de grises a binaria
	/** by chaco:
	 CImg<T>& threshold( T value,
	 bool soft_threshold = false,
	 bool strict_threshold = false )

	 binariza la imagen segun un valor de umbral, sea valor de umbral=100
	 para valores menores a 100 toma 0
	 para valores mayores a 100 toma 1
	 */
	return imagen.threshold(imagen.max() / 2);
}
