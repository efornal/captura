/*
 * mask.h
 *
 *  Created on: 16/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include <math.h>

using namespace std;
using namespace cimg_library;

#define pi 4.0*atan(1.0)

template<class T>
CImg<T> generar_mascara3x3_todos1_promediadora(float coef = 9.0) {
	/*genera una mascara del tipo promediadora todos 1 (suaviza)
	 *    			| 1  1  1 |
	 *   (1/coef)*  | 1  1  1 |
	 *  			| 1  1  1 |
	 * */
	CImg<T> imagen(3, 3, 1, 1);
	imagen(0, 0) = 1 * (1 / coef);
	imagen(0, 1) = 1 * (1 / coef);
	imagen(0, 2) = 1 * (1 / coef);
	imagen(1, 0) = 1 * (1 / coef);
	imagen(1, 1) = 1 * (1 / coef);
	imagen(1, 2) = 1 * (1 / coef);
	imagen(2, 0) = 1 * (1 / coef);
	imagen(2, 1) = 1 * (1 / coef);
	imagen(2, 2) = 1 * (1 / coef);
	return imagen;
}

template<class T>
CImg<T> generar_mascara3x3_no_simetrica(float coef = 10.0) {
	/*genera una mascara no simetrica cualquiera!
	 *    			| 0  1  0 |
	 *   (1/coef)*  |-1  1 -1 | //suma 1 -> mantiene homogenos
	 *  			| 0  1  0 |
	 * */
	CImg<T> imagen(3, 3, 1, 1);
	imagen(0, 0) = 0 * (1 / coef);
	imagen(0, 1) = 1 * (1 / coef);
	imagen(0, 2) = 0 * (1 / coef);
	imagen(1, 0) = -1 * (1 / coef);
	imagen(1, 1) = 1 * (1 / coef);
	imagen(1, 2) = -1 * (1 / coef);
	imagen(2, 0) = 0 * (1 / coef);
	imagen(2, 1) = 1 * (1 / coef);
	imagen(2, 2) = 0 * (1 / coef);
	return imagen;
}
template<class T>
CImg<T> generar_mascara_promediadora(int dim = 3) {
	/* Genera una mascara de dimension dim x dim
	 * del tipo:
	 * 			|	1	1	1	...dim    |
	 * 			|	1	1	1	... 1     |  * 1/dim^2
	 * 			|	1	1	1   ... 1     |
	 * 			|	1   ........dim x dim |
	 **/
	CImg<T> imagen(dim, dim, 1, 1, 1);
	return imagen * (1.0 / pow(dim, 2.0));
}

template<class T>
T clipp(T valor) {
	if (valor > 255.0)
		return 255;
	else if (valor < 0)
		return 0;
	else
		return valor;
}

template<class T>
CImg<T> generar_mascara_gaussiana(int x = 3, int y = 3, double var = 1.0) {
	/**
	 retorna una mascara gausseana
	 *  formula: 1/sqrt(2pi) * e^-(x^2 + y^2)/2var^2
	 * dada la formula, con +-x = x^2 , e y+- = y^2
	 * por lo que siempre retorna una mascara tipo signo mas
	 *  0  a  0
	 *  a 255 a
	 *  0  a  0
	 * FIXME : no funciona para valores diferentes de 3x3 !
	 *
	 *-1,-1 	-1,0		-1,1
	 * 0,-1 	 0,0		 0,1		 => para 3x3    el for va desde -1 hasta 1
	 * 1,-1 	 1,0		 1,1
	 * 								=> para 5x5 el for va de -2 hasta 2
	 * 								=> para 7x7 va de -3 =valor
	 * la serie sera valor=((tam-1)/2)
	 */
	CImg<T> mask(x, y, 1, 1, 1);
	int xm = (x - 1) / 2;
	int ym = (y - 1) / 2;

	T c = 1.0 / sqrt(2.0 * pi);
	T den = 2.0 * pow(var, 2);
	cimg_forXY(mask, xm, ym)
		{
			mask(x+xm, y+ym) = exp(-(pow(x-xm, 2) + pow(y-ym, 2)) / den);
		}
	return (mask *= c);
}

template<class T>
CImg<T> generar_mascara_PA_suma1(int tipo) {
	/*########################################################################
	 * SUMA =1:
	 * tipo=1:					tipo=2:					tipo=3
	 *	 0	-1	 0				-1	-1	-1				1	-2	1
	 *	-1	 5	-1				-1	 9	-1			   -2	 5 -2
	 * 	 0	-1	 0				-1  -1  -1				1	-2	1
	 *########################################################################
	 * */
	CImg<T> imagen(3, 3, 1, 1);
	switch (tipo) {
	case 1:
		imagen(0, 0) = 0.0;
		imagen(0, 1) = -1.0;
		imagen(0, 2) = 0.0;
		imagen(1, 0) = -1.0;
		imagen(1, 1) = 5.0;
		imagen(1, 2) = -1.0;
		imagen(2, 0) = 0.0;
		imagen(2, 1) = -1.0;
		imagen(2, 2) = 0.0;
		break;
	case 2:
		imagen(0, 0) = -1.0;
		imagen(0, 1) = -1.0;
		imagen(0, 2) = -1.0;
		imagen(1, 0) = -1.0;
		imagen(1, 1) = 9.0;
		imagen(1, 2) = -1.0;
		imagen(2, 0) = -1.0;
		imagen(2, 1) = -1.0;
		imagen(2, 2) = -1.0;
		break;
	case 3:
		imagen(0, 0) = 1.0;
		imagen(0, 1) = -2.0;
		imagen(0, 2) = 1.0;
		imagen(1, 0) = -2.0;
		imagen(1, 1) = 5.0;
		imagen(1, 2) = -2.0;
		imagen(2, 0) = 1.0;
		imagen(2, 1) = -2.0;
		imagen(2, 2) = 1.0;
		break;
	default:
		break;

	}
	return imagen;
}
template<class T>
CImg<T> generar_mascara_PA_suma0(int tipo) {
	/*########################################################################
	 * SUMA =1:
	 * tipo=1:					tipo=2:
	 *	 0	-1	 0				-1	-1	-1
	 *	-1	 4	-1				-1	 8	-1
	 * 	 0	-1	 0				-1  -1  -1
	 *########################################################################
	 * */
	CImg<T> imagen(3, 3, 1, 1);
	switch (tipo) {
	case 1:
		imagen = generar_mascara_PA_suma1<T> (1);
		imagen(1, 1) = 4.0;
		break;
	case 2:
		imagen = generar_mascara_PA_suma1<T> (2);
		imagen(1, 1) = 8.0;
		break;
	default:
		break;

	}
	return imagen;
}

//no tiene mucho sentido hacer la mascara asi:
template<class T>
CImg<T> generar_mascara_PA(int nx, int ny, bool suma_1 = true) {
	/* Genera una mascara de tamanio @nx x @ny
	 * suma_1 indica si la suma de la mascara es 1, si es true la suma es 1, caso contrario es 0
	 * */
	CImg<T> mascara(nx, ny, 1, 1, 1);

	int fila_x = nx / 2.0;
	cout << fila_x << endl;
	int columna_y = ny / 2.0;
	cout << columna_y << endl;
	int cant = 0;
	cimg_forXY(mascara,X,Y)
		{
			mascara(X, Y) = 0;
		}
	for (int x = 0; x < nx; x++) {
		mascara(x, fila_x) = -1.0; //columna
		mascara(columna_y, x) = -1.0;
		cant += 2; //cantidad de unos que puse
	}

	if (suma_1) //la suma debe ser 1
		mascara(fila_x, columna_y) = cant - 2 + 1;
	else
		// la suma de la mascara debe ser 0
		mascara(fila_x, columna_y) = cant - 2;
	return mascara;
}

template<class T>
T restar(T primer_termino, T segundo_termino, bool normalizado = true) {
	//funcion que retorna la resta de 2 terminos... primer termino-segundo termino
	// para llamarla por ejemplo :restar<double>(l,m);

	T imagen = primer_termino - segundo_termino;
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

template<class T>
CImg<T> fil_masc_difusa(CImg<T> imagen, CImg<T> mascara) {
	//devuelve filtrado por masacara difusa
	// la imagen filtrada segun: f(x,y)-PB(f(x,y)) usando como mascara del PB la especificada
	return restar<CImg<T> > (imagen, imagen.get_convolve(mascara));
}

template<class T>
CImg<T> fil_high_boost(CImg<T> imagen, CImg<T> mascara, int coefA = 1) {
	//devuelve filtrado de alta potencia
	// la imagen filtrada segun: A*f(x,y)-PB(f(x,y)) usando como mascara del PB la especificada
	return restar<CImg<T> > (coefA * imagen, imagen.get_convolve(mascara));
}
template<class T>
T sumar(T primer_termino, T segundo_termino, bool normalizado = true) {
	//funcion que retorna la suma de 2 terminos...
	// para llamarla por ejemplo : sumar<double>(l,m);
	if (normalizado)
		return (primer_termino + segundo_termino) / 2;
	return (primer_termino + segundo_termino);
}
CImg<unsigned char> multiplicar(CImg<unsigned char> im1,
		CImg<unsigned char> im2, bool normalizar) {
	CImg<unsigned char> imagen(im1.width(), im1.height(), 1, 1);

	cimg_forXY(im1, x, y)
		{
			imagen(x, y) = im1(x, y) * im2(x, y);
		}
	if (normalizar)
		return imagen.normalize();
	else
		return imagen;
}
