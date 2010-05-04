/*
 * prueba_HSI.cpp
 *
 *  Created on: 02/05/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg <float> imagen(255,255,1,3);
	float H=120; //verde
	float S=0.1; //saturacion 1
	float I=0.3; //intensidad 1
	//el color que da aca es por una indefinicion... I=1->indefinido S, con S=0 indefinido H, etc.
	cimg_forXY(imagen, x, y){
		imagen(x,y,0,0) = H;
		imagen(x,y,0,1) = S;
		imagen(x,y,0,2) = I;
	}
	CImgDisplay disp1(imagen.HSItoRGB());
	while (!disp1.is_closed()){}

return 0;
}
