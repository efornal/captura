/*
 * op_aritmeticos.h
 *
 *  Created on: 06/05/2010
 *      Author: christian
 */
#include<CImg.h>
using namespace std;
using namespace cimg_library;

//libreria con operadores aritmeticos para usar sobre imagenes....
//multiplicacion
//*****************************************************************************
template <class T>
CImg <T> multiplicar(CImg <T> im1, CImg <T> im2, bool normalizar=true) {
	CImg <T> imagen(im1.width(), im1.height(), 1, 1);

	cimg_forXY(im1, x, y)
		{
			imagen(x, y) = im1(x, y) * im2(x, y);
		}
	if (normalizar)
		return imagen.normalize();
	else
		return imagen;
}
//*****************************************************************************
//divicion
template <class T>
CImg <T> dividir(CImg <T> im1, CImg <T> im2,
		bool normalizar=true) {
	/*
	 * Division. Se implementa como la multiplicacion de una imagen por la reciproca de la otra
	 * */
	CImg <T> imagen = multiplicar(im1, negativo(im2), true);

	if (normalizar)
		return imagen.normalize();
	else
		return imagen;
}
//suma
template <class T>
CImg <T> sumar(CImg <T> primer_termino, CImg <T> segundo_termino, bool normalizado = true) {
	//funcion que retorna la suma de 2 terminos... si normalizao=false no divide x 2
	// para llamarla por ejemplo : sumar<CImg <double>> (l,m);
	CImg <T> imagen(primer_termino);
	if (normalizado) {
		cimg_forXY(primer_termino, x, y)
			{
				imagen(x, y) = (primer_termino(x, y) + segundo_termino(
						x, y)) / 2.0;
			}
	} else {
		cimg_forXY(primer_termino, x, y)
			{
				imagen(x, y) = (primer_termino(x, y) + segundo_termino(
						x, y));
			}
	}
	return imagen;
}
//resta
template <class T>
CImg <T> restar(CImg <T> primer_termino, CImg <T> segundo_termino, bool normalizado = true) {
	//funcion que retorna la resta de 2 terminos... primer termino-segundo termino
	// para llamarla por ejemplo :restar<double>(l,m);

	CImg <T> imagen = primer_termino - segundo_termino;
	if (normalizado) {
		cimg_forXY(imagen, x,y)
			{
				imagen(x, y) = (imagen(x, y) + 255) / 2;
				/* observar que en la linea de arriba estoy normalizando, los valores de intensidad van de 0 a 255:
				 * 0-255 = -255 -> (-255+255)/2=0
				 * 255-0=  255 -> (255+255)/2=255
				 * 255-255= 0 -> (0+255)/2 = 127
				 * 0-0= 0+255 -> 255/2 =127
				 * */
			}
		return imagen;
	}
	return (primer_termino - segundo_termino);
}
