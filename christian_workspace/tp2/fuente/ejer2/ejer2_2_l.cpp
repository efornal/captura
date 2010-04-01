//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>
#include "../ejer1/lib.h"

using namespace std;
using namespace cimg_library;

int main() {
	CImg<unsigned char> imagen, im_log;
	imagen.load("../../imagenes/rmn.jpg");
	CImgDisplay disp1, disp2;
	for (int i=0;i<100;i++) {
		im_log=logaritmo(imagen, i);
		disp1.set_title("grafica logaritmo variando el factor");
		im_log.display(disp1);
		cout<<"Factor: "<<i<<endl;
		obtener_grafica_mapeo_logaritmo(i).display(disp2);
		while (!disp1.button()){}
			sleep(1);
	}
	return 0;
}
