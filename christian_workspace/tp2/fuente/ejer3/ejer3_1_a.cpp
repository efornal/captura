#include <iostream>
#include <CImg.h>
#include "../ejer1/lib.h"

using namespace std;
using namespace cimg_library;

int main() {
	cout << "suma de int: " << suma<int> (3, 4) << endl;
	cout << "suma de float: " << suma<float> (3.3, 4.5) << endl;
	CImg <unsigned char> im1, im2;
	im1.load("../../imagenes/letras1.tif");
	im2.load("../../imagenes/letras2.tif");

	//CImgList <unsigned char> lista (im1, im2);
	suma< CImg <unsigned char > > (im1, im2, true).display("suma");
	return 0;
}
