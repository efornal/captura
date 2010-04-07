/*
 * ejer6_1.cpp
 *
 *  Created on: 06/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"
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

	CImgDisplay disp0(imagen, "imagen original", 1); // el 1 es para que normalice.
	int plano = 0;
	CImgDisplay disp(plano_de_bit(imagen, plano), "plano 0 = 0000 0001", 1);
	cout << endl;
	while (!disp0.is_closed() && !disp0.is_keyQ()) {
		disp.wait();
		if (disp.is_keyARROWUP()) { //aumentar plano bits
			plano = clipp_plano(++plano);
		} else if (disp.is_keyARROWDOWN()) {
			plano = clipp_plano(--plano);
		}
		disp.display(plano_de_bit(imagen, plano));
		disp.set_title("planos 0=>7");
		cout << "Plano: " << plano;
	}

	/*FIXME: es un umbral cdo aplico lo de los planos de bits..para el
	 * Plano 0 -> estoy aplicando un umbral que corta en 1 o sea deja pasar los valores de 0 hasta 1 inclusive y los demas
	 * 			  los hace 0
	 * Plano 1 -> deja pasar valores desde 2 en adelante -> estoy cuantizando en 128 niveles????
	 * Plano 2 -> deja pasar valores desde 4 en adelante
	 * Plano 3 -> deja pasar valores desde 8 en adelante
	 * ........
	 * Plano 7 -> estoy aplicando un umbral en 128 -> deja pasar valores de 128 a 255
	 * */
	/*FIXME: porque el plano 7 con la imagen de gris se ve como que estuviera cuantizado en 2->poco detalle
	 pero en la imagen con el plano 7 tengo mucho detalle!?que onda?
	 */

	//FIXME: solo se pueden meter hasta 6 imagenes en una lista! no mas de eso!?

	while ((!disp.is_closed() && !disp.is_keyQ())) {
	}
	return 0;
}
