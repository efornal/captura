/*
 * filtros.h
 *
 *  Created on: 07/05/2010
 *      Author: christian
 */
/*FUNCIONES PARA FILTRADO EN EL DOMINIO FRECUENCIAL
 * */

#include <CImg.h>
#include "../../../tp4/fuente/lib4/CPDSI_functions.h"

#include "../../../tp2/fuente/lib2/op_aritmeticos.h"
#include "figuras.h"

using namespace std;
using namespace cimg_library;

template<class T>
CImg<T> filtrar(CImg<T> imagen, CImg<T> H) {
	/**
	 * Retorna la imagen filtrada con el filtro pasado
	 * El filtro debe estar diseñado centrado
	 */
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

template<class T>
CImg<T> filtrar_complejo(CImg<T> img, CImgList<T> filtro) {
	/**by chaco...
	 * Retorna la imagen filtrada con el filtro pasado complejo
	 * El filtro debe estar diseñado centrado y
	 * FIXME: deberia estar el filtro shifteado???
	 */
	CImgList<T> tdf = img.get_FFT();

	filtro[0].shift(filtro[0].width() / 2, filtro[0].height() / 2, 0, 0, 2); //correcto?
	filtro[1].shift(filtro[1].width() / 2, filtro[1].height() / 2, 0, 0, 2); //correcto?

	cimg_forXY( img, x, y )
		{
			tdf[0](x, y) *= filtro[0](x, y);
			tdf[1](x, y) *= filtro[1](x, y);
		}
	return tdf.get_FFT(true)[0];
}
//######################################################################################
//######################################################################################
template<class T>
CImg<T> get_PB_ideal(int dimx, int dimy, float frec_corte = 10.0) {
	/* genera un PB ideal con frec corte =10.0 por defecto de dimx x dimy*/
	CImg<T> H(dimx, dimy, 1, 1, 0.0);
	circulo_centrado<T> (H.width() / 2, H.height() / 2, H, frec_corte, 0); //creo la mascara
	H.normalize(0.0, 1.0);
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
	return H;
}

template<class T>
CImg<T> get_PB_Butter(int dimx, int dimy, float frec_corte = 10.0, float orden =
		1.0) {
	//genera un filtro pasa bajos butterworth de dimx x dimy con frec corte =10 por defecto y orden 1.0 por defecto
	float distancia;
	float mediox = dimx / 2.0;
	float medioy = dimy / 2.0;
	CImg<T> H(dimx, dimy, 1, 1, 0.0);
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 / (1.0 + pow(distancia / abs(frec_corte), 2.0 * abs(
					orden)));
		}
	return H;
}
template<class T>
CImg<T> get_PB_gauss(int dimx, int dimy, float varianza = 1.0) {
	float distancia;
	CImg<T> H(dimx, dimy, 1, 1, 0);
	float mediox = dimx / 2.0;
	float medioy = dimy / 2.0;
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = exp((-1.0 * pow(distancia, 2.0)) / (2.0
					* pow(varianza, 2)));
		}
	return H;
}

template<class T>
CImg<T> get_PA_ideal(int dimx, int dimy, float frec_corte = 10.0) {
	/* genera un PA ideal con frec corte =10.0 por defecto de dimx x dimy*/
	CImg<T> H(dimx, dimy, 1, 1);
	circulo_centrado_inverso<T> (H.width() / 2, H.height() / 2, H, frec_corte,
			0); //creo la mascara
	H.normalize(0.0, 1.0);
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
	return H;
}

template<class T>
CImg<T> get_PA_Butter(int dimx, int dimy, float frec_corte = 10.0, float orden =
		1.0) {
	//genera un filtro pasa altos butterworth de dimx x dimy con frec corte =10 por defecto y orden 1.0 por defecto
	float distancia;
	float mediox = dimx / 2.0;
	float medioy = dimy / 2.0;
	CImg<T> H(dimx, dimy, 1, 1, 0.0);
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 / (1.0 + pow(abs(frec_corte) / distancia, 2.0 * abs(
					orden)));
		}
	return H;
}
template<class T>
CImg<T> get_PA_gauss(int dimx, int dimy, float varianza = 1.0) {
	//genera un filtro PA gaussiano con varianza 1.0 por defecto
	float distancia;
	CImg<T> H(dimx, dimy, 1, 1, 0);
	float mediox = dimx / 2.0;
	float medioy = dimy / 2.0;
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 - exp((-1.0 * pow(distancia, 2.0)) / (2.0 * pow(
					varianza, 2)));
		}
	return H;
}
//######################################################################################
//######################################################################################
// FILTROS DEFINIDOS EN FRECUENCIA:
template<class T>
CImg<T> aplicar_PB_ideal(CImg<T> imagen, float frec_corte = 10.0) {
	/*aplica un filtro pasa Bajos IDEAL centrado de radio=frec_corte. Por defecto 10. (muy selectivo)
	 * Devuelve la imagen filtrada para ser mostrada.
	 */
	CImg<T> H = get_PB_ideal<T> (imagen.width(), imagen.height(), frec_corte);
	return filtrar<T> (imagen, H);
}

template<class T>
CImg<T> aplicar_PB_Butter(CImg<T> imagen, CImg<T> &H, float frec_corte = 10.0,
		float orden = 1.0) {
	/*aplica un filtro pasa Bajos Butterwortch con frecuencia de corte: frec_corte y orden = orden.
	 * Por defecto: frec_corte=10 y orden=1
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro...
	 */
	H = get_PB_Butter<T> (imagen.width(), imagen.height(), frec_corte, orden);
	CImg<T> Hf = H.get_shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2);
	return filtrar<T> (imagen, Hf);
}

template<class T>
CImg<T> aplicar_PB_Gaussiano(CImg<T> imagen, CImg<T> &H, float varianza = 1.0) {
	/*aplica un filtro pasa Bajos Gaussiano con varianza=sigma (DEFINIDO EN FRECUENCIA)
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	H = get_PB_gauss<T> (imagen.width(), imagen.height(), varianza);
	CImg<T> Hf = H.get_shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2);
	return filtrar<T> (imagen, Hf);
}

//FILTROS DEFINIDOS EN TIEMPO Y CONVERTIDOS A FRECUENCIA
template<class T>
CImg<T> aplicar_Gaussiano_PB_desdetioempo(CImg<T> imagen, CImg<T> &H,
		float sigma = 1.0) {
	//fixme: esta funcion no anda!
	/*aplica un filtro pasa Bajos Gaussiano con varianza=sigma desde tiempo convierte a frecuencia... so
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */

	CImg<T> h = gaussian_mask(imagen.width(), sigma); //filtro gaussiando pasa bajos espacial
	CImgList<T> H_FFT = h.get_FFT(); //obtengo la respuesta en frecuencia del filtro gaussiano

	CImg<T> H_real = H_FFT[0];
	H = H_real;
	H_real.shift(h.height() / 2.0, H.width() / 2.0, 0, 0, 2);
	imagen.shift(imagen.width() / 2, imagen.height() / 2, 0, 0, 2);

	CImgList<T> IMAGEN_FFT = imagen.get_FFT();
	CImg<T> IMAGEN_real = IMAGEN_FFT[0];
	CImg<T> IMAGEN_imag = IMAGEN_FFT[1];

	IMAGEN_real = multiplicar<T> (IMAGEN_real, H_real, false);
	IMAGEN_imag = multiplicar<T> (IMAGEN_imag, H_real, false); //fixme: la parte imaginaria la multiplico por la parte real de la funcion de transferencia... esta bien esto?
	cimg_forXY(IMAGEN_FFT[0],X,Y)
		{
			IMAGEN_FFT[0](X, Y) = IMAGEN_real(X, Y);
			IMAGEN_FFT[1](X, Y) = IMAGEN_imag(X, Y);
		}
	return IMAGEN_FFT.get_FFT(true)[0]; //devuelvo la parte real
}

/*##########################################################################################
 * ##########################################################################################*/

/*FILTROS PASA ALTOS PARA EJERCICIO 4 -
 * */
// FILTROS DEFINIDOS EN FRECUENCIA:
template<class T>
CImg<T> aplicar_PA_ideal(CImg<T> imagen, float frec_corte = 10.0) {
	/*aplica un filtro pasa Altos IDEAL centrado de radio=frec_corte. Por defecto 10. (muy selectivo)
	 * Devuelve la imagen filtrada para ser mostrada.
	 */
	CImg<T> H(imagen.width(), imagen.height(), 1, 1, 1.0);
	H = get_PA_ideal<T> (imagen.width(), imagen.height(), frec_corte);
	return filtrar<T> (imagen, H);
}

template<class T>
CImg<T> aplicar_PA_Butter(CImg<T> imagen, CImg<T> &H, float frec_corte = 10.0,
		float orden = 1.0) {
	/*aplica un filtro pasa Altos Butterwortch con frecuencia de corte: frec_corte y orden = orden.
	 * Por defecto: frec_corte=10 y orden=1
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro...
	 */
	H = get_PA_Butter<T> (imagen.width(), imagen.height(), frec_corte, orden);
	CImg<T> Hf = H.get_shift(H.width() / 2, H.height() / 2, 0, 0, 2); //vuelvo a la original para ver el filtro centrado
	return filtrar<T> (imagen, Hf);
}

template<class T>
CImg<T> aplicar_PA_Gaussiano(CImg<T> imagen, CImg<T> &H, float varianza = 1.0) {
	/*aplica un filtro pasa Altos Gaussiano con varianza=sigma (DEFINIDO EN FRECUENCIA)
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	H = get_PA_gauss<T> (imagen.width(), imagen.height(), varianza);
	CImg<T> Hf = H.get_shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2.0);
	return filtrar<T> (imagen, Hf);
}

//FILTROS DEFINIDOS EN TIEMPO Y CONVERTIDOS A FRECUENCIA
template<class T>
CImg<T> aplicar_Gaussiano_PA_desdetiempo(CImg<T> imagen, CImg<T> &H,
		float sigma = 1.0) {
	/*aplica un filtro pasa Altos Gaussiano con varianza=sigma
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	CImg<T> h = gaussian_mask(imagen.width(), sigma); //filtro gaussiando pasa bajos espacial
	CImgList<T> H_FFT = h.get_FFT(); //obtengo la respuesta en frecuencia del filtro gaussiano
	/*	cimglist_apply(H_FFT, shift)
	 (imagen.width() / 2, imagen.height() / 2, 0, 0, 2);*/
	CImg<T> H_real = H_FFT[0];
	cimg_forXY(H_real, x,y)
		{
			H_real(x, y) = 1.0 - H_real(x, y); // lo paso a Pasa altos
		}
	H = H_real;
	//h.shift(h.height() / 2.0, H.width() / 2.0, 0, 0, 2); //todo: para que cuerno hago esto? revisar...
	imagen.shift(imagen.width() / 2, imagen.height() / 2, 0, 0, 2);
	//H_real.shift(H_real.width() / 2, H_real.height() / 2, 0, 0, 2); //descentro para palicarselo a la iamgen

	CImgList<T> IMAGEN_FFT = imagen.get_FFT();
	CImg<T> IMAGEN_real = IMAGEN_FFT[0];
	CImg<T> IMAGEN_imag = IMAGEN_FFT[1];

	IMAGEN_real = multiplicar<T> (IMAGEN_real, H_real, false);
	IMAGEN_imag = multiplicar<T> (IMAGEN_imag, H_real, false); //fixme: la parte imaginaria la multiplico por la parte real de la funcion de transferencia... esta bien esto?
	cimg_forXY(IMAGEN_FFT[0],X,Y)
		{
			IMAGEN_FFT[0](X, Y) = IMAGEN_real(X, Y);
			IMAGEN_FFT[1](X, Y) = IMAGEN_imag(X, Y);
		}
	return IMAGEN_FFT.get_FFT(true)[0]; //devuelvo la parte real
}

//##########################################################################################


//filtrado homomorfico: GRACIAS CHACO... :)
template<class T>
CImg<T> get_homomorfico(CImg<T> img, double wc = 1.0, double gl = 0.0,
		double gh = 1.0, float orden = 1.0) {
	/* retorna un filtro Homomorfico
	 * Debe filtrarse con get_filtrado_homomorfico(filtro)
	 * por defecto gh=1, gl=0 => pasaaltos normalizado
	 * 1-) genero un PA con wc y orden dados
	 * 2-) normalizo entre los valor gl y gh
	 */
	CImg<T> filtro = get_PA_Butter<T> (img.width(), img.height(), wc, orden);
	return filtro.normalize(gl, gh);
}
template<class T>
CImg<T> to_log(CImg<T> &img) {
	/**
	 * Aplicado de logaritmo teniendo en cuenta valores negativos
	 * log = log(1+img(x,y))
	 */
	cimg_forXY(img,x,y)
		{
			img(x, y) = log(1 + img(x, y));
		}
	return img;
}
template<class T>
CImg<T> aplicar_filtrado_homomorfico(CImg<T> img, CImg<T> filtro) {
	/* Retorna la imagen con filtrado Homomorfico con el filtro pasado
	 * El filtro debe estar diseñado centrado,
	 * y ser de tipo homomorfico: get_homomorfico(...)
	 * pasos: f(x,y) -> log{} -> F{} -> H*F(u,v) -> Finv.{} -> exp{} -> g(x,y)
	 * */
	CImgList<T> tdf = to_log<double> (img).get_FFT();
	filtro.shift(filtro.width() / 2, filtro.height() / 2, 0, 0, 2);
	cimg_forXY( filtro, x, y )
		{
			tdf[0](x, y) *= filtro(x, y);
			tdf[1](x, y) *= filtro(x, y);
		}
	return tdf.get_FFT(true)[0].exp();
}

/*################## FILTRADO ALTA POTENCIA #############################*/
template<class T>
CImg<T> aplicar_PA_alta_potencia(CImg<T> imagen, float varianza = 1.0, float A =
		2.0) {
	//fixme: esto no funciona!ver
	/*aplica un filtro de alta potencia usando una mascara gaussiana
	 * (A-1)+gaussiano(varianza)... USAR TIPO DE DATOS float para que no explote
	 * */
	CImg<T> h_pa = gaussian_mask(imagen.width(), varianza); //obtengo el filtro pasa altos gaussiano espacial
	CImgList<T> H_PA = h_pa.get_FFT(); //obtengo el filtro en frecuencia
	CImgList<T> H_AP(H_PA[0], H_PA[1]); // filtro de alta pontencia frecuencial... falta meterlo lod el A-1
	cimg_forXY(H_PA[0], x, y)
		{
			H_AP[0](x, y) = (A - 1.0) + H_PA[0](x, y); //parte real
			H_AP[1](x, y) = (A - 1.0) + H_PA[1](x, y); //parte imaginaria
		}
	//ya tengo el filtro de alta potencia
	return filtrar_complejo<T> (imagen, H_AP);
}
