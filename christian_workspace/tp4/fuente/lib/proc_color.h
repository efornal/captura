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

template<class T>
CImg<float> aplicar_paleta(CImg<float> imagen, string nombre_paleta) {
	/* carga una paleta con nombre_paleta la aplica a la imagen pasada como parametro y
	 * devuelve la imagen con la paleta aplicada
	 * OJO SOLO FUNCIONA PARA IMAGENES DE UN SOLO CANAL
	 * */
	vector<vector<float> > paleta; //creo un vecotr de vecotres
	cargar_paleta(paleta, nombre_paleta);
	CImg<float> imagen_con_paleta_aplicada(imagen.width(), imagen.height(), 1, 3);
		cimg_forXY(imagen_con_paleta_aplicada, x, y)
			{ //es mas o menos una lut...
			imagen_con_paleta_aplicada(x, y, 1, 0) = paleta[imagen(x, y)][0]*255; //canal rojo
			imagen_con_paleta_aplicada(x, y, 1, 1) = paleta[imagen(x, y)][1]*255; //canal verde
			imagen_con_paleta_aplicada(x, y, 1, 2) = paleta[imagen(x, y)][2]*255; //canal azul
			}
	return imagen_con_paleta_aplicada;
}
