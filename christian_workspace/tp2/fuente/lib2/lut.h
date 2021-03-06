#include<CImg.h>
#include "op_aritmeticos.h"

using namespace std;
using namespace cimg_library;

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
T promedio(T img, int n = 2) {
	for (int i = 0; i < n; i++) {
		img += img;
	}
	return img / n;
}

template<class T>
CImg<T> desplazar(CImg<T> imagen, int des_x, int des_y) {
	/* des_x : desplazamiento en x
	 * des_y : desplazamiento en y
	 * imagen: imagen a desplazar
	 * retorna la imagen desplazada
	 * */
	CImg<T> im(imagen.width(), imagen.height(), 1, 1, 0);
	for (int x = 0; x < imagen.width() - des_x; x++)
		for (int y = 0; y < imagen.height() - des_y; y++)
			im(x + des_x, y + des_y) = imagen(x, y);
	return im;
}
template <class T>
CImg<T> lut(CImg<T> original, float a = 1, float c = 0.0,
		bool clip = 1) {
	/*	entrada_r imagen de entrada sobre la cual se aplica la transformacion
	 a: factor de ganancia
	 c: offset
	 clip=1 implica que corte en 0 y 255 los valores - por defecto clipea
	 retorna una imagen  modificada linealmente*/

	CImg<T> modificada(original.width(), original.height(), 1, 1);
	T valor;
	cimg_forXY( modificada, x, y )
		{
			valor = a * original(x, y) + c;
			if (clip) {
				valor = clipp(valor);
			}

			modificada(x, y) = valor;
		}
	return modificada;
}

CImg<unsigned char> obtener_grafica_mapeo(int a, int c) {
	/* retorna en una imagen la grafica de la fucion de mapeo segun los
	 * coeficientes a y c que se pasan por paremtro
	 * */
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = lut(mapeo, a, c, false);
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}
template <class T>
CImg<T> negativo(CImg<T> img1) { //retorna el negativo de una imagen
	//ojo solo anda para imagenes en tonos de grises
	double a = -1;
	double c = 255; // maximo de la "escala"
	return lut(img1, a, c, 1);
}

CImg<unsigned char> lut_tramos(CImg<unsigned char> original, int x0, int x1,
		bool clip, int factor) {
	/* compresion lineal por tramos
	 * factor = factore de compresion o estiramiento segun su valor
	 *
	 * */
	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);
	cimg_forXY(original, x, y)
		{
			switch (1 + (x > x0) + (x > x1)) {
			case 1: // esta entre 0 y x1
				modificada(x, y) = original(x, y);
				break;
			case 2: //es mayor que x1 y menor que x2
				modificada(x, y) = original(x, y) * factor;
				break;
			case 3: //es mayor que x2
				modificada(x, y) = original(x, y);
				break;
			}
		}
	return modificada;
}

template<class T>
T lut_tramos2dimensiones(T original, int x0, int y0, int x1, int y1, bool clip,
		float factor) {
	/* aplica un mapeo en la zona comprendida por los puntso x0, y0, x1, y1
	 * el resto de la imagen no es modificado
	 * */
	T modificada(original.width(), original.height(), 1, 1);
	cimg_forXY(original, x, y)
		{
			if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1))
				modificada(x, y) = original(x, y) * factor;
			else
				modificada(x, y) = original(x, y);
		}
	return modificada;
}

CImg<unsigned char> obtener_grafica_mapeo_tramos(int x0, int x1, int factor) {
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = lut_tramos(mapeo, x0, x1, 1, factor);
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}

/*FUNCIONES EJERCICIO2
 * */
CImg<unsigned char> logaritmo(CImg<unsigned char> original, int factor = 1) {
	// transforacion logaritmica
	// por defecto clipea
	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);

	cimg_forXY(original,x,y)
		{
			modificada(x, y) = clipp(log(1 + abs(original(x, y))) * factor);
		}

	return modificada;
}

//operaciones con una sola imagen: clipping
//operaciones con 2 imagenes: normalizacion

template<class T>
T potencia(T original, float exp, float factor = 1) {
	// transforacion de potencia
	// por defecto clipea
	T modificada(original.width(), original.height(), 1, 1);
	cimg_forXY(original,x,y)
		{
			modificada(x, y) = clipp(pow(original(x, y), exp)) * factor;
		}
	return modificada;
}

CImg<unsigned char> obtener_grafica_mapeo_logaritmo(int factor) {
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = (logaritmo(mapeo, factor));
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}
template<class T>
T obtener_grafica_mapeo_potencia(float exponente) {
	float blanco[] = { 255, 255, 255 };
	T mapeo(255, 1, 1, 1, 0);
	T mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	T mapeado = potencia(mapeo, exponente);
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}

//ejercicio 3:
//1a-


template<class T>
T clipp_im(T imagen) {
	cimg_forXY(imagen, x, y)
		{
			if ((imagen(x, y)) > 255)
				imagen(x, y) = 255;
			if (imagen(x, y) < 0)
				imagen(x, y) = 0;
		}
	return imagen;
}


CImg<unsigned char> emboss(CImg<unsigned char> imagen, int des_x, int des_y,
		bool normalizado = true) {
	/* normalizado: true (por defecto) -> la imagen se corta si el valor del pixel es menor que 0 o mayor que 255
	 * LA FUNCION RETORNA LA IMAGEN CON EL FILTRO APLICADO*/

	if (normalizado)
		return sumar<unsigned char> (desplazar<unsigned char> (negativo(
				imagen), des_x, des_y), imagen).normalize();
	return sumar<unsigned char> (desplazar<unsigned char> (negativo(
			imagen), des_x, des_y), imagen);

}

CImg<unsigned char> grises() {
	//retorna una imagen con un degrade de grises de 0 a 255
	CImg<unsigned char> imagen(256, 256, 1, 1);
	cimg_forXY(imagen, x,y)
		{
			imagen(x, y) = y;
		}
	return imagen;
}

CImg<unsigned char> get_binary(CImg<unsigned char> imagen) {
	//convierte una imagen en escala de grises a binaria
	/** by chaco:
	 CImg<T>& threshold( T value,
	 bool soft_threshold = false,
	 bool strict_threshold = false )

	 binariza la imagen segun un valor de umbral, sea valor de umbral=100
	 para valores menores a 100 toma 0
	 para valores mayores a 100 toma 1
	 */
	return imagen.threshold(imagen.max() / 2);
}

template<class T>
bool intensidades_iguales(T imagen1, T imagen2) {
	//si las imagenes BINARIAS son iguales devuelve true en otro caso false
	cimg_forXY(imagen1, x, y)
		{
			if (imagen1(x, y) != imagen2(x, y)) {
				return false;
			}
		}
	return true;
}
