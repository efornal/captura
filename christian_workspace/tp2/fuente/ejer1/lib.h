#include<CImg.h>
using namespace std;
using namespace cimg_library;

int clipp(int valor) {
	if (valor > 255)
		return 255;
	else if (valor < 1)
		return 0;
	else
		return valor;
}

CImg<unsigned char> lut(CImg<unsigned char> original, int a=1, int c=0, bool clip=1) {
	/*	entrada_r imagen de entrada sobre la cual se aplica la transformacion
	 a: factor de ganancia
	 c: offset
	 clip=1 implica que corte en 0 y 255 los valores - por defecto clipea
	 retorna una imagen  modificada linealmente*/

	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);
	int valor;
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


CImg<unsigned char> negativo(CImg<unsigned char> & img1) { //retorna el negativo de una imagen
	int a = -1;
	unsigned char c = img1.max(); // maximo de la imagen
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

CImg<unsigned char> obtener_grafica_mapeo_tramos(int x0, int x1, int factor) {
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = lut_tramos(mapeo, x0,x1, 1, factor);
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}

/*FUNCIONES EJERCICIO2
 * */
CImg<unsigned char> logaritmo(CImg<unsigned char> original) {
	// transforacion logaritmica
	// por defecto clipea
	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);

	cimg_forXY(original,x,y){
		modificada(x,y)=clipp(log(1+original(x,y)));
	}

	return modificada;
}

CImg<unsigned char> potencia(CImg<unsigned char> original, int exp) {
	// transforacion de potencia
	// por defecto clipea
	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);
	cimg_forXY(original,x,y){
		modificada(x,y)=clipp(pow(original(x,y), exp));
	}
	return modificada;
}

CImg<unsigned char> obtener_grafica_mapeo_logaritmo() {
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = (logaritmo(mapeo));
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}

CImg<unsigned char> obtener_grafica_mapeo_potencia(int exponente) {
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = potencia(mapeo, exponente);
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}
