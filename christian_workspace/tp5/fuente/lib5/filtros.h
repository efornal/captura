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
CImg<T> aplicar_PB_ideal(CImg<T> imagen, int frec_corte = 10) {
	/*aplica un filtro pasa Bajos IDEAL centrado de radio=frec_corte. Por defecto 10. (muy selectivo)
	 * Devuelve la imagen filtrada para ser mostrada.
	 */
	CImg<T> H(imagen.width(), imagen.height(), 1, 1);
	circulo_centrado<T> (H.width() / 2, H.height() / 2, H, frec_corte, 0); //creo la mascara
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
/*template <calss T>
void Butterworth(CImg <T> &imagen, int frec_corte=10, int orden=1){
	cimg_forXY(H,x,y){
		H(x,y)=1/(1+pow((H(x,y)/frec_corte),2.0*orden));
	}
}*/
//TODO: esto todavia no funca...
template<class T>
CImg<T> aplicar_Butter_PB(CImg<T> imagen, CImg <T> &H, int frec_corte=10, int orden=1) {
	/*aplica un filtro pasa Bajos Butterwortch con frecuencia de corte: frec_corte y orden = orden.
	 * Por defecto: frec_corte=10 y orden=1
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro...
	 */
	float distancia;
	float mediox=imagen.width()/2.0;
	float medioy=imagen.height()/2.0;
	//CImg<T> H(imagen.width(), imagen.height(), 1, 1);
	cimg_forXY(H,x,y){
		distancia = sqrt ( pow(x-mediox,2.0) + pow(y-medioy,2.0) );
		H(x,y)=1.0/(1.0+pow(distancia/abs(frec_corte), 2.0*abs(orden)));
	}
	//H.normalize(0.0, 1.0);
	//H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
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
