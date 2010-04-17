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

#define e 2.71828182845904523536028747

template<class T>
CImg<T> generar_mascara3x3() { //filtro promediador pasa bajos
	CImg<T> imagen(3, 3, 1, 1);
	imagen(0, 0) = 1 * (1 / 9.0);
	imagen(0, 1) = 1 * (1 / 9.0);
	imagen(0, 2) = 1 * (1 / 9.0);
	imagen(1, 0) = 1 * (1 / 9.0);
	imagen(1, 1) = 1 * (1 / 9.0);
	imagen(1, 2) = 1 * (1 / 9.0);
	imagen(2, 0) = 1 * (1 / 9.0);
	imagen(2, 1) = 1 * (1 / 9.0);
	imagen(2, 2) = 1 * (1 / 9.0);
	return imagen;
}

template<class T>
CImg<T> generar_mascara3x3_no_simetrica() {
	CImg<T> imagen(3, 3, 1, 1);
	imagen(0, 0) = 1 * (1 / 10.0);
	imagen(0, 1) = 2 * (1 / 10.0);
	imagen(0, 2) = 1 * (1 / 10.0);
	imagen(1, 0) = 1 * (1 / 10.0);
	imagen(1, 1) = 1 * (1 / 10.0);
	imagen(1, 2) = 1 * (1 / 10.0);
	imagen(2, 0) = 1 * (1 / 10.0);
	imagen(2, 1) = 1 * (1 / 10.0);
	imagen(2, 2) = 1 * (1 / 10.0);
	return imagen;
}
template<class T>
CImg<T> generar_mascara(int tamanio) {
	CImg<T> imagen(tamanio, tamanio, 1, 1, 1);
	return imagen * (1.0 / pow(tamanio, 2.0));
}

//FIXME: corregir para ejercicio 4_1 de la guia 3.. no da...
template<class T>
CImg<T> generar_mascara(int x0, int y0, int nx, int ny, double varianzax = 1.0,
		double varianzay = 1.0, double A = 1.0) {
	/* Genera una mascara gaussiana centrada en @x0, @y0
	 * de tamanio @nx x @ny
	 * de varianza varianzax y varianzay
	 * */
	CImg<T> imagen(nx, ny, 1, 1, 1);
	cimg_forXY(imagen, x, y)
		{
			imagen(x, y) = A * pow(e, -(pow((x - x0), 2.0) / (2.0 * pow(
					varianzax, 2.0))) + (pow((x - y0), 2.0) / (2.0 * pow(
					varianzay, 2.0))));
			imagen(x, y) = imagen(x, y) * (1.0 / (nx * ny));
		}
	return imagen;
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
	 * tipo=1:					tipo=2:					tipo=3
	 *	 0	-1	 0				-1	-1	-1				1	-2	1
	 *	-1	 4	-1				-1	 8	-1			   -2	 4 -2
	 * 	 0	-1	 0				-1  -1  -1				1	-2	1
	 *########################################################################
	 * */
	CImg<T> imagen(3, 3, 1, 1);
	switch (tipo) {
	case 1:
		imagen=generar_mascara_PA_suma1 <T> (1);
		imagen(1, 1) = 4.0;
		break;
	case 2:
		imagen=generar_mascara_PA_suma1 <T> (2);
		imagen(1, 1) = 8.0;
		break;
	case 3:
		imagen=generar_mascara_PA_suma1 <T> (3);
		imagen(1, 1) = 4.0;
		break;
	default:
		break;
		return imagen;
	}
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

template <class T>
CImg <T> fil_masc_difusa (CImg <T> imagen, CImg <T> mascara){
	//devuelve filtrado por masacara difusa
	// la imagen filtrada segun: f(x,y)-PB(f(x,y)) usando como mascara del PB la especificada
	return restar <CImg <T> > (imagen, imagen.get_convolve(mascara));
}

template <class T>
CImg <T> fil_high_boost (CImg <T> imagen, CImg <T> mascara, int coefA=1){
	//devuelve filtrado de alta potencia
	// la imagen filtrada segun: A*f(x,y)-PB(f(x,y)) usando como mascara del PB la especificada
	return restar <CImg <T> > (coefA*imagen, imagen.get_convolve(mascara));
}
