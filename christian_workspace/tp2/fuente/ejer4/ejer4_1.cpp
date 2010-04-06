/*
 * ejer4_1.cpp
 *
 *  Created on: 01/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	/* Filtro emboss: relieve tipo repujado sobre una placa metalica, logra el realce de boredes
	 * para lograrlo
	 * sumar a la imagen su negativo desplazado
	 * (desplazar el negativo unos pixeles en alguna direccion obtenemos el efecto)
	 * segun se negativize una u otra imagen obtenemos efecto de relieve exterior o interior
	 * */
	//TODO: no funciona, consultar
	CImg <unsigned char > imagen;
	imagen.load("../../imagenes/letras1.tif");
	int c=4;
	CImgList <unsigned char> lista (imagen, negativo(imagen), emboss(imagen, c, false));
	lista.display("Imagen original, imagen con el negativo y un desplazamiento, filtro emboss aplicado");
	cout<<"El desplazamiento es de: "<<c<<endl;
	return 0;
}
