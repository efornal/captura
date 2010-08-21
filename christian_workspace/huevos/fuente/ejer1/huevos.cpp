/*
 * huevos.cpp
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

using namespace std;
using namespace cimg_library;

template<class T>
void limpiar_imagen(CImg<T> &imagen, float valor = 50.0) {
	cimg_forXY(imagen, x, y)
		{
			if (imagen(x, y) <= valor) {
				imagen(x, y) = 0.0;
			}
		}
}

int main(int argc, char **argv) {
	const char *filename =
			cimg_option("-f", "../../imagenes/huevos/orig22.bmp",
					"ruta archivo imagen");
	const float umbral_limpieza =
			cimg_option("-umbral", 100.0, "umbral para limpieza de imagen");

	CImg<float> imagen(filename);
	CImg<float> imagen_tratada(filename);
	imagen_tratada.channel(0); // obtengo un solo canal.
	imagen_tratada.normalize(0, 255.0); //normalizo
	//imagen_tratada.display();
	limpiar_imagen<float> (imagen_tratada, umbral_limpieza); //limpio el ruido
	//imagen_tratada.display();
	CImg_3x3(I, float);
	float maximo = 0.0;
	cout << "Media imagen tratada: " << imagen_tratada.mean() << endl;
	cout << "Mediana imagen tratada: " << imagen_tratada.median() << endl;
	cout << "Varianza imagen tratada: " << imagen_tratada.variance() << endl;
	cout << "Maximo imagen tratada: " << imagen_tratada.max() << endl;
	cout << "Minimo imagen tratada: " << imagen_tratada.min() << endl;

	int cant_huevos = 0;
	cimg_for3x3(imagen_tratada,x,y,0,0,I,float)
		{
			maximo = max(max(max(max(max(max(max(Ipp, Ipc), Ipn), Icp), Icn),
					Inp), Inc), Inn);//saco el maximo de los vecinos
			if (Icc > maximo) {
				cant_huevos++;
				imagen_tratada(x,y) = 255.0;
			}
		}
	cout << "*****************************" <<endl<<"Cantidad de huevos: "<< cant_huevos << endl;
	CImgDisplay disp1;
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
