#include <CImg.h>
#include <vector>
#include <list>

using namespace std;
using namespace cimg_library;
template<class T>

int contar_blancos(CImg<T> imagen) {
	cimg_forY(imagen, y) {
		cimg_forX(imagen, x) {
			if (imagen(x, y) != 1) {
				return y;
				break;
			}
		}
	}
}

bool es_copa_alta(int cantidad) {
	if (cantidad >= 7) { //entonces es copa baja
		return false;
	} else
		return true;
}
template<class T>
int obtener_Y_superior(CImg<T> imagen) {
	//recorre la imagen y devuelve
	cimg_forY(imagen, y) {
		cimg_forX(imagen, x) {
			if (imagen(x, y) == 255) {
				return y;
				break;
			}
		}
	}
}

template<class T>
int obtener_Y_inferior(CImg<T> imagen) {
	//recorre la imagen y devuelve
	imagen.rotate(180);
	return ((imagen.height() - 1) - obtener_Y_superior(imagen));
}

template<class T>
bool es_tinto(CImg<T> imagen, int umbral = 10) {
	CImg<T> H = imagen.get_RGBtoHSI().get_channel(0);
	int contar = 0;
	cimg_forXY(H,x,y)
		{
			if (H(x, y) > 60 && H(x, y) < 90) {
				contar++;
			}
		}
	if (contar >= 10) {
		return false;
	} else
		return true;
}
