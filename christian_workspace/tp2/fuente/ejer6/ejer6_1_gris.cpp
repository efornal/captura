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
	 FIXME: Los bits mas significativos(planos 7, 6..) me dan mucho mas nivel de detalle que los menos significativos (plano0..1)
	 */

	CImg<unsigned char> gris = grises(); // me genera la imagen en tonos de grises

	CImgDisplay disp0(gris, "imagen original", 1); // el 1 es para que normalice.
	int plano = 0;
	CImgDisplay disp(plano_de_bit(gris, plano), "plano 0 = 0000 0001", 1);
	cout << endl;
	while (!disp0.is_closed() && !disp0.is_keyQ()) {
		disp.wait();
		if (disp.is_keyARROWUP()) { //aumentar plano bits
			plano = clipp_plano(++plano);
		} else if (disp.is_keyARROWDOWN()) {
			plano = clipp_plano(--plano);
		}
		disp.display(plano_de_bit(gris, plano));
		disp.set_title("planos 0=>7");
		cout << "Plano: " << plano;
	}

	/*FIXME: es mi interpretacion correcta: es un umbral cdo aplico lo de los planos de bits??
	 * Plano 0 -> cuantizo en 256 niveles?
	 * Plano 1 -> cuantizo en 128 niveles
	 * Plano 2 -> quantizo en 64 niveles
	 * Plano 3 -> quantizo en 32 niveles
	 * Plano 4 -> quantizo en 16 niveles
	 * Plano 5 -> quantizo en 8 niveles
	 * Plano 6 -> quantizo en 4 niveles
	 * Plano 7 -> cuantizo en 2 niveles = umbral en 128/
	 *--------------------------------------------------------------------------------------------------------------
	 * si bien el plano 7 es como que lo estoy cuantizando en 2 niveles porque al
	 * reconstruir la imagen (ver ejercicio ejer6_1_imagen.cpp) es como el que me aporta o me deja mejor la imagen?
	 *--------------------------------------------------------------------------------------------------------------
	 *solo se pueden meter hasta 6 imagenes en una lista! no mas de eso!?
	 */

	while ((!disp.is_closed() && !disp.is_keyQ())) {
	}
	return 0;
}
