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
	CImg <float> original_image("../../imagenes/chairs.jpg"); //cargo imagen
	original_image.display("canal por defecto");



	CImg<float> image_ch0 (original_image);
	CImg<float> image_ch1 (original_image);
	CImg<float> image_ch2 (original_image);
	CImg<float> image_ch3 (original_image);


	image_ch0.channel(0);
	image_ch0.display("canal seteado en 0");

	image_ch1.channel(1);
	image_ch1.display("canal seteado en 1");

	image_ch2.channel(2);
	image_ch2.display("canal seteado en 2");

	image_ch3.channel(3);
	image_ch3.display("canal seteado en 3");

	CImgDisplay original_withid(original_image, "ventana con CimgDisplay", 0);
	while (!original_withid.is_closed()) { }

	return 0;
}
