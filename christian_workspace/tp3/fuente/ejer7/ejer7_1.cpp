/*
 * ejer7_1.cpp
 *
 *  Created on: 08/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	/*TODO: calcular el histograma y solo aplicar al valor del centro...
	 * tomar imagen vecindad como una nueva imagen.. . cortamos ese pedazo le  hcemos la imagen ecualizada... tomamos le valor delo medio
	 * y reemplazamos la imagen por eso... y asi sucesivamente
	 * */
	CImg<unsigned char> imagen("../../imagenes/ej7a.tif");

	CImgDisplay disp1, disp2, disp3, disp4;
	int nlevels = 255;
	CImg<unsigned char> imagen_ecualizada = imagen.get_equalize(nlevels);

	CImg <unsigned char> aux1(imagen), aux2 (imagen);
	/*ecualizacion local:
	 * 0, 0    - 255,255
	 * 255,0   - aux1.width()-1, 255
	 * 0,255   - 255,aux.height()-1
	 * 255,255 - aux1.widht()-1, aux1.height()-1
	 * */

	for (int i=0; i<255;i++){
		for (int j=0;j<255;j++){
			aux2(i,j)=aux1.get_crop(0,0, 255,255).get_equalize(255)(i,j);
		}
	}
	for (int i=255; i<aux1.width()-1;i++){
			for (int j=0;j<255;j++){
				aux2(i,j)=aux1.get_crop(255,0, aux1.width()-1,255).get_equalize(255)(i,j);
			}
		}
	for (int i=0; i<255;i++){
			for (int j=255;j<aux1.height()-1;j++){
				aux2(i,j)=aux1.get_crop(0,255, 255,aux1.height()-1).get_equalize(255)(i,j);
			}
		}
	for (int i=255; i<aux1.width()-1;i++){
			for (int j=255;j<aux1.height()-1;j++){
				aux2(i,j)=aux1.get_crop(255,255, aux1.width()-1,aux1.height()-1).get_equalize(255)(i,j);
			}
		}
	aux2.display (disp4);
	aux1.get_crop(255,0, aux1.width()-1,255).get_equalize(255).display();
	aux1.get_crop(0, 255, 255, aux1.height()-1).get_equalize(255).display();
	aux1.get_crop(255, 255, aux1.width()-1, aux1.height()-1).get_equalize(255).display();

	CImgList<unsigned char> lista(imagen, imagen_ecualizada, aux1);
	lista.display(disp1);
	disp1.set_title(
			"imagen original - imagen ecualizada globalemnte - imagen ecualizada por zonas (localmente)");

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
