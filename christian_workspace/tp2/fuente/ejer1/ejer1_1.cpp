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

CImg<int> function_lut(CImg<int> &entrada_r, int a, int c) {
	//entrada_r imagen de entrada sobre la cual se aplica la transofrmacion
	//a: factor de ganancia
	//c: offset
	//retorna una imagen  modificada linealmente

	/*The \ref CImg<\c T> structure contains \a six fields :
	 - \ref width defines the number of \a columns of the image (size along the X-axis).
	 - \ref height defines the number of \a rows of the image (size along the Y-axis).
	 - \ref depth defines the number of \a slices of the image (size along the Z-axis).
	 - \ref spectrum defines the number of \a channels of the image (size along the C-axis).
	 - \ref data defines a \a pointer to the \a pixel \a data (of type \c T).
	 - \ref is_shared is a boolean that tells if the memory buffer \ref data is shared with
	 another image.*/

	//entrada_r.display();

	CImg<int> img1(entrada_r.width(), entrada_r.height(), 1, 1); //imagen a la que se le va a aplicar la transformacion
	cout<<"a: "<<a<< "       c: "<<c;
	cimg_forXY(img1, x,y)
		{
			img1(x, y, 0, 0) = a * entrada_r(x, y, 0, 0) + c;

		}
	cout<<"entro";
	img1.display();
	return img1;
}

int main() {
	CImg<int> imagen;
	imagen.load(
			"/home/christian/Documentos/universidad/2010/captura/imagenes/imagenD.tif"); //cargo la imagen
	imagen.channel(0);

	CImg<int> imagen_modificada = function_lut(imagen, 50, 1);
cout<<"asdfas";
	CImgDisplay vent1(imagen, "imagen original", 1), vent2(imagen_modificada,
			"imagen modificada", 1);
	imagen_modificada.print();
	while (!vent1.is_closed() && !vent2.is_closed()) {
	}
	return 0;
}
