//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	int width=640;
	int heigth = 480;
	int depth =1;
	int spectrum = 3;

	CImg<float> img1 (width, heigth, depth, spectrum);
	float rojo[] = { 255, 0, 0 };
	float verde[] = { 0, 255, 0 };
	float azul[] = { 0, 0, 255 };

    img1.display("Imagen de intensidad");


    img1.draw_text(500, 500, "Hello World", rojo);
    img1.draw_rectangle(100,100,200,200, verde);
    img1.draw_text(200, 400, "Hello World", verde);
    img1.draw_text(400, 200, "Hello World", azul);

    cout<<"(200, 200): "<< img1(200,200)<<endl<<" (150,156): "<<img1(150,156); //porque no tira nada??
    img1.display("Imagen de intensidad");


	return 0;
}
