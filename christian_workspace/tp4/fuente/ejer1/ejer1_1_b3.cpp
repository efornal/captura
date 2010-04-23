/*
 * ejer1_1_b3.cpp
 *
 *  Created on: 23/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> RGB("../../imagenes/patron.tif");
	CImgDisplay disp1(RGB, "imagen RGB", 0); //pongo el 0 para que no me normalice lo valores

	CImg<float> HSI(RGB.get_RGBtoHSI()); //imagen HSI
	CImgDisplay disp2(HSI, "imagen HSI", 0); //muestro la imagen HSI

	//ver componentes por separado
	CImg<float> HSI_H(HSI.get_channel(0));
	CImg<float> HSI_S(HSI.get_channel(1));
	CImg<float> HSI_I(HSI.get_channel(2));

	CImg<float> HSI_H_copia(HSI_H);
	CImg<float> HSI_S_copia(HSI_S);
	CImg<float> HSI_I_copia(HSI_I);

	cimg_forXY(HSI_H,x,y) //para mostrarlos...
		{
			HSI_H_copia(x, y) = HSI_H(x, y) / 360.0 * 255.0; //recordar que H esta entre 0 y 360
			HSI_S_copia(x, y) = HSI_S(x, y) * 255.0; //recordar que S va de 0 a 1.0
			HSI_I_copia(x, y) = HSI_I(x, y) * 255.0; //recordar que I esta entre 0 y 1.0
		}

	CImgDisplay disp3(HSI_S_copia, "Canal S original", 0);

	//variacion de saturacion por filas de 0 a 1(maxima saturacion-color puro)
	int dx = HSI_H.width();
	cimg_forXY(HSI_H,x,y)
		{
			HSI_I_copia(x, y) = 1.0; // brillo maximo
		}

	//rearmo HSI
	CImg<float> HSI2(dx, HSI_H.height(), 1, 3); //imagen HSI
	cimg_forXY(HSI_H_copia, x, y)
		{
			HSI2(x, y, 0, 0) = HSI_H(x, y);
			HSI2(x, y, 0, 1) = HSI_S(x, y);
			HSI2(x, y, 0, 2) = HSI_I_copia(x, y);
		}
	cimg_forXY(HSI_I_copia,x,y) //solo lo hago para mostrar el canal este..
		{
			HSI_I_copia(x, y) *= 255.0;
		}
	CImgDisplay disp4(HSI_I_copia, "Canal I con brillo maximo", 0);
	CImgDisplay disp5(HSI2,
			"imagen HSI con brillo maximo en HSI", 0);
	CImgDisplay disp6(HSI2.get_HSItoRGB(),
			"imagen HSI con birllo maximo en RGB", 0);

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
