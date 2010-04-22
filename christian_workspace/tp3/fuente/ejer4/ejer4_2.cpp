/*
 * ejer4_2.cpp
 *
 *  Created on: 17/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen("../../imagenes/hubble.tif");
	CImgDisplay disp1, disp2, disp3, disp4;
	imagen.display(disp1);
	disp1.set_title("imagen original");

	CImg<float> resultado = imagen.get_convolve(generar_mascara_promediadora<float> (7));
	resultado.display(disp2);
	disp2.set_title("imagen filtrada");
	float threshold=128.0;


	while (!disp1.is_closed()) {
		disp1.wait();
			if (disp1.is_keyARROWUP()){
				threshold+=1.0;
			} else if (disp1.is_keyARROWDOWN()){
				threshold-=1.0;
			}
			threshold=clipp <float>(threshold);
			resultado.get_threshold(threshold).display(disp3);
			disp3.set_title("imagen con objetos grandes");
			cout<<"Threshold: "<<threshold<<endl;
	}
	return 0;
}
