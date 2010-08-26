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
	/* Forma de llamarlo...
	 * ./huevos -f ruta_de_la_imagen -umbral float_que_indica_el_umbral_de_limpieza
	 * */
	//archivo de imagen que quiero analizar:
	const char *filename =
			cimg_option("-f", "../../imagenes/huevos/orig30.bmp",
					"ruta archivo imagen");

	// los valores de pixeles que esten por debajo de 70 lo tomo como ruido:
	const float umbral_limpieza =
			cimg_option("-umbral", 70.0, "umbral para limpieza de imagen");

	// armo el vector fila para convolucionar la imagen y sauvizar dos pixeles vecinos separados por un pixel
	CImg<float> vector(4, 1, 1);
	vector(0, 0, 0) = 18.0;
	vector(1, 0, 0) = 255.0;
	vector(2, 0, 0) = 255.0;
	vector(3, 0, 0) = 18.0;

	CImg<float> imagen(filename); //cargo imagen original
	CImg<float> imagen_tratada(filename); // esta es la imagen corregida

	imagen_tratada.channel(0); // obtengo un solo canal.
	//imagen.display(); //muestro imagen original
	//imagen_tratada.display();
	imagen_tratada.normalize(0, 255.0); //normalizo la imagen entre 0 y 255.0
	//imagen_tratada.display();
	limpiar_imagen<float> (imagen_tratada, umbral_limpieza); //limpio el ruido de acuerdo al umbral que puse

	imagen_tratada.convolve(vector); //aplico la convolucion de la imagen sin ruido con el vector

	imagen_tratada.normalize(0.0, 255.0); //normalizo ya que despues de convolucionar los valores se fueron al carajo
	//imagen_tratada.display();

	CImg_3x3(I, float); //defino una vecindad de 3x3 -> propio del lenguaje
	float maximo = 0.0; //variable auxiliar
	//	cout << "Media imagen tratada: " << imagen_tratada.mean() << endl;
	//	cout << "Mediana imagen tratada: " << imagen_tratada.median() << endl;
	//	cout << "Varianza imagen tratada: " << imagen_tratada.variance() << endl;
	//	cout << "Maximo imagen tratada: " << imagen_tratada.max() << endl;
	//	cout << "Minimo imagen tratada: " << imagen_tratada.min() << endl;
	//imagen_tratada.display();

	int cant_huevos = 0; //variable que me indica la cantidad de huevos

	cimg_for3x3(imagen_tratada,x,y,0,0,I,float)
		{//recorro una vecindad de 3x3
			maximo = max(max(max(max(max(max(max(Ipp, Ipc), Ipn), Icp), Icn),
					Inp), Inc), Inn);//saco el maximo de los vecinos
			if (Icc > maximo) { //me fijo si el pixel en el que estoy parado es menor que todos los vecinos
				cant_huevos++; //si es asi entonces es un huevo
				imagen_tratada(x, y) = 255.0; //le asigno el valor máximo para que no me cuente el pixel de alado por si es maximo
											  //como otro huevo
			}
		}
	cout << "*****************************" << endl << "Cantidad de huevos: "
			<< cant_huevos << endl;


	CImgDisplay disp1;
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
