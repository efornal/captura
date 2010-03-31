//============================================================================
// Name        : tutorial.cpp
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
int main(int argc, char *argv[]) {
	cimg_usage("Ejemplo basico.");
	const char
			* filename =
					cimg_option("-i","../../imagenes/huang2_corrida.tif","Image file\n");
	//Imagen color, 8 bits de profundidad por componente.
	CImg<unsigned char> img(640, 400, 1, 3);
	img.fill(0); //Asigna 0 a todos los p ́xeles
	unsigned char rojo[] = { 255, 0, 0 }; //Define color rojo
	img.draw_text(100, 100, "Hello World", rojo); //Escribe en (100,100).
	img.display("Hola..."); //Visualiza
	/*std::cout<<"depth: "<<img._depth<<std::endl;
	std::cout<<"hight: "<<img._height<<std::endl;
	std::cout<<"spectrum: "<<img._spectrum<<std::endl;
	std::cout<<"data: "<<img._data<<std::endl;*/
	//std::cout<<"data: "<<std::endl;

	//cout<<endl<<"img_depth: "<<img._depth<<endl;

	CImg<unsigned char> img1(filename); //Carga de disco
	//Copia lo que hay en img1 pero como valores de punto flotante
	CImg<float> img2(img1);
	img2.normalize(0, 1); //Normaliza en [0,1]
	img2.sqrt(); //Aplica ra ́z cuadrada a cada pixel
	img2.resize(250, 150); //Redimensiona a 250x150
	//Visualiza ambas im ́genes a la vez
	CImgDisplay vent1(img1, "original"), vent2(img2, "procesada");
	while (!vent1.is_closed()) {
	}
	return 0;
}
