/*
 * ejer6_1_imagen.cpp
 *
 *  Created on: 07/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"
#include "../lib/operadores_logicos.h"
#include "../lib/plano_bit.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	/** POSTA:
	 * 8 bits image = 2^8=256 colores 0 a 255....
	 Con la imagen en escala de grises se aprecia como interpreta los bits:
	 dec  | bin
	 0    | 0000 0000
	 1    | 0000 0001
	 2    | 0000 0010
	 4    | 0000 0100
	 8    | 0000 1000
	 16   | 0001 0000
	 32   | 0010 0000
	 64   | 0100 0000

	 127  | 0111 1111 -> hasta aqui el bit 7 =0
	 ----------------
	 128  | 1000 0010 -> a partir de aqui el bit 7=1
	 ...  | 1@@@ @@@@
	 255  | 1111 1111
	 ________________
	 pos  : 7654 3210

	 para la posicion 7 (bit7) - ver en tabla a lo vertical
	 de 0-127 son todos ceros
	 de 128-255 son todos unos
	 por tanto la imagen correspondiente a este plano es una
	 mitad blanca mitad negra. y asi con el resto.
	 Los bits mas significativos(planos 7, 6..) me dan mucho mas nivel de detalle que los menos significativos (plano0..1)
	 */

	CImg<unsigned char> imagen;
	imagen.load("../../imagenes/tablero.png");
	//CImg<unsigned char> gris = grises(); // me genera la imagen en tonos de grises

	CImgDisplay disp0(imagen, "imagen original", 1); // el 1 es para que normalice.
	CImgDisplay disp(plano_de_bit(imagen, 0), "plano 0 = 0000 0001", 1);
	CImgDisplay disp1(plano_de_bit(imagen, 1), "plano 1= 0000 0010 ", 1);
	CImgDisplay disp2(plano_de_bit(imagen, 2), "plano 2= 0000 0100", 1);
	CImgDisplay disp3(plano_de_bit(imagen, 3), "plano 3= 0000 1000", 1);
	CImgDisplay disp4(plano_de_bit(imagen, 4), "plano 4= 0001 0000", 1);
	CImgDisplay disp5(plano_de_bit(imagen, 5), "plano 5= 0010 0000", 1);
	CImgDisplay disp6(plano_de_bit(imagen, 6), "plano 6= 0100 0000", 1);
	CImgDisplay disp7(plano_de_bit(imagen, 7), "plano 7= 1000 0000", 1);

	while ((!disp.is_closed() && !disp.is_keyQ())) {
	}
	return 0;
}
