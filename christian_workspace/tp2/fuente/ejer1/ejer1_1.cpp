//============================================================================
// Name        : tp2.cpp
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

// este ejercicio de mierda no anda.. no se porque!!!!

CImg<unsigned char> function_lut(CImg<unsigned char> original, int a, int c) {
	//entrada_r imagen de entrada sobre la cual se aplica la transofrmacion
	//a: factor de ganancia
	//c: offset
	//retorna una imagen  modificada linealmente

	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);
	CImg<unsigned char> rango(255,255,1,1);
	cimg_forXY(rango, x, y){
		rango(x,y)=y;
	}
	cimg_forXY( modificada, x, y )
		{
			modificada(x, y) = a * original(x, y) + c;
		}
	rango.display("rango");

	return modificada;
}

int main() {
	CImg<unsigned char> imagen;
	imagen.load(
			"../../imagenes/imagenD.tif"); //cargo la imagen

	CImg<unsigned char> imagen_modificada = function_lut(imagen, 5, 1);

	CImgDisplay vent1(imagen, "imagen original", 1), vent2(imagen_modificada,
			"imagen modificada", 1);
	imagen_modificada.print();
	while (!vent1.is_closed() && !vent2.is_closed()) {
	}
	return 0;
}
