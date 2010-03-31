#include<CImg.h>
using namespace std;
using namespace cimg_library;


CImg<unsigned char> lut(CImg<unsigned char> original, int a, int c, bool clip) {
	/*	entrada_r imagen de entrada sobre la cual se aplica la transformacion
	 a: factor de ganancia
	 c: offset
	 clip=1 implica que corte en 0 y 255 los valores
	 retorna una imagen  modificada linealmente*/

	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);
	int valor;
	cimg_forXY( modificada, x, y )
		{
			valor = a * original(x, y) + c;
			if (clip) {
				if (valor > 255) {
					valor = 255;

				} else if (valor < 0) {
					valor = 0;
				}
			}
			modificada(x, y) = valor;
		}
	return modificada;
}

CImg<unsigned char> obtener_grafica_mapeo(int a, int c) {
	/*retorna en una imagen la grafica de la fucion de mapeo segun los
	 * coeficientes a y c que se pasan por paremtro
	 * */
	unsigned char rojo[] = { 255, 0, 0 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 3, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = lut(mapeo, a, c, false);
	return mapeo_disp.draw_graph(mapeado, rojo, 1, 1, 1, 255, 0);
}

CImg<unsigned char> negativo(CImg<unsigned char> & img1)
{	//retorna el negativo de una imagen
	int a=-1;
	unsigned char c=img1.max(); // maximo de la imagen
    return lut(img1, a, c, 1);
}

