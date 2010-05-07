/*
 * filtros.h
 *
 *  Created on: 07/05/2010
 *      Author: christian
 */
/*FUNCIONES PARA FILTRADO EN EL DOMINIO FRECUENCIAL
 * */

#include <CImg.h>
using namespace std;
using namespace cimg_library;

template<class T>
CImg<T> aplicar_PB_ideal(CImg<T> imagen, int radio = 10) {
	/*aplica un filtro pasa Bajos IDEAL centrado de radio=Radio. Por defecto 10. (muy selectivo)
	 * Devuelve la imagen filtrada para ser mostrada.
	 */
	CImg<T> H(imagen.width(), imagen.height(), 1, 1);
	circulo_centrado<T> (H.width() / 2, H.height() / 2, H, radio, 0); //creo la mascara
	H.normalize(0.0, 1.0);
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
	CImgList<T> F = imagen.get_FFT();//obtengo la transformada
	CImg<T> F_real = F[0]; //parte real
	CImg<T> F_imag = F[1]; //parte imaginaria
	//realizo el filtrado en el dominio de las frecuecnias:
	F_real = multiplicar<T> (F_real, H, false);
	F_imag = multiplicar<T> (F_imag, H, false);
	F[0] = F_real;
	F[1] = F_imag;
	return F.get_FFT(true)[0]; //devuelvo la parte real
}
