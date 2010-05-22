/*
 * filtros.h
 *
 *  Created on: 16/05/2010`
 *      Author: christian
 */

#include <CImg.h>
using namespace std;
using namespace cimg_library;

template<class T>
CImg<T> segmentar(CImg<T> imagen, CImg<T> mascara_x, CImg<T> mascara_y,
		bool binaria = true) {
	/* fucnion generica que segmenta una imagen con las mascaras pasadas por parametro
	 * por defecto binaria=true indica que devuelve una imagen binaria como resultado
	 * */
	CImg<T> img_filx = imagen.get_convolve(mascara_x).get_abs();
	CImg<T> img_fily = imagen.get_convolve(mascara_y).get_abs();
	// armamos el grandiente
	CImg<T> suma(img_filx.width(), img_filx.height(), 1, 1, 0);
	cimg_forXY(imagen,x,y)
		{
			suma(x, y) = img_filx(x, y) + img_fily(x, y);
			if (binaria) {
				(suma(x, y) < 127) ? suma(x, y) = 0 : suma(x, y) = 255;
			}
		}
	return suma;
}

//definicion de mascaras:
//roberts:
template<class T>
CImg<T> get_roberts_x() {
	//genera una mascara de roberts en la direccion x
	CImg<T> hx(2, 2, 1, 1, 0);
	hx(0, 0) = -1.0;
	hx(1, 1) = 1.0;
	return hx;
}

template<class T>
CImg<T> get_roberts_y() {
	//genera una mascara de roberts en la direccion y
	CImg<T> hy(2, 2, 1, 1, 0);
	hy(0, 1) = -1.0;
	hy(1, 0) = 1.0;
	return hy;
}

//prewitt:
template<class T>
CImg<T> get_prewitt_x() {
	//genera una mascara de prewitt en la direccion x
	CImg<T> hx(3, 3, 1, 1, 0);
	hx(0, 0) = -1.0;
	hx(0, 1) = -1.0;
	hx(0, 2) = -1.0;

	hx(1, 0) = 0.0;
	hx(1, 1) = 0.0;
	hx(1, 2) = 0.0;

	hx(2, 0) = 1.0;
	hx(2, 1) = 1.0;
	hx(2, 2) = 1.0;
	return hx;
}

template<class T>
CImg<T> get_prewitt_y() {
	//genera una mascara de prewitt en la direccion y
	CImg<T> hy(3, 3, 1, 1, 0);
	hy(0, 0) = -1.0;
	hy(0, 1) = 0.0;
	hy(0, 2) = 1.0;

	hy(1, 0) = -1.0;
	hy(1, 1) = 0.0;
	hy(1, 2) = 1.0;

	hy(2, 0) = -1.0;
	hy(2, 1) = 0.0;
	hy(2, 2) = 1.0;
	return hy;
}

//prewitt diagonal:
template<class T>
CImg<T> get_prewitt_x_diagonal() {
	//genera una mascara de prewitt en la direccion x diagonal 45 grados
	CImg<T> hx(3, 3, 1, 1, 0);
	hx(0, 0) = 0.0;
	hx(0, 1) = 1.0;
	hx(0, 2) = 1.0;

	hx(1, 0) = -1.0;
	hx(1, 1) = 0.0;
	hx(1, 2) = 1.0;

	hx(2, 0) = -1.0;
	hx(2, 1) = -1.0;
	hx(2, 2) = 0.0;
	return hx;
}

template<class T>
CImg<T> get_prewitt_y_diagonal() {
	//genera una mascara de prewitt en la direccion y diagonal -45 grados
	CImg<T> hy(3, 3, 1, 1, 0);
	hy(0, 0) = -1.0;
	hy(0, 1) = -1.0;
	hy(0, 2) = 0.0;

	hy(1, 0) = -1.0;
	hy(1, 1) = 0.0;
	hy(1, 2) = 1.0;

	hy(2, 0) = 0.0;
	hy(2, 1) = 1.0;
	hy(2, 2) = 1.0;
	return hy;
}

//sobel:
template<class T>
CImg<T> get_sobel_x() {
	//genera una mascara de sobel en la direccion x
	CImg<T> hx(3, 3, 1, 1, 0);
	hx(0, 0) = -1.0;
	hx(0, 1) = -2.0;
	hx(0, 2) = -1.0;

	hx(1, 0) = 0.0;
	hx(1, 1) = 0.0;
	hx(1, 2) = 0.0;

	hx(2, 0) = 1.0;
	hx(2, 1) = 2.0;
	hx(2, 2) = 1.0;
	return hx;
}

template<class T>
CImg<T> get_sobel_y() {
	//genera una mascara de sobel en la direccion y
	CImg<T> hy(3, 3, 1, 1, 0);
	hy(0, 0) = -1.0;
	hy(0, 1) = 0.0;
	hy(0, 2) = 1.0;

	hy(1, 0) = -2.0;
	hy(1, 1) = 0.0;
	hy(1, 2) = 2.0;

	hy(2, 0) = -1.0;
	hy(2, 1) = 0.0;
	hy(2, 2) = 1.0;
	return hy;
}

//sobel diagonal:
template<class T>
CImg<T> get_sobel_x_diagonal() {
	//genera una mascara de sobel en la direccion x diagonal 45 grados
	CImg<T> hx(3, 3, 1, 1, 0);
	hx(0, 0) = 0.0;
	hx(0, 1) = 1.0;
	hx(0, 2) = 2.0;

	hx(1, 0) = -1.0;
	hx(1, 1) = 0.0;
	hx(1, 2) = 1.0;

	hx(2, 0) = -2.0;
	hx(2, 1) = -1.0;
	hx(2, 2) = 0.0;
	return hx;
}

template<class T>
CImg<T> get_sobel_y_diagonal() {
	//genera una mascara de sobel en la direccion y -45 grados
	CImg<T> hy(3, 3, 1, 1, 0);
	hy(0, 0) = -2.0;
	hy(0, 1) = -1.0;
	hy(0, 2) = 0.0;

	hy(1, 0) = -1.0;
	hy(1, 1) = 0.0;
	hy(1, 2) = 1.0;

	hy(2, 0) = 0.0;
	hy(2, 1) = 1.0;
	hy(2, 2) = 2.0;
	return hy;
}

template<class T>
CImg<T> get_LoG() {
	//genera una mascara de sobel en la direccion y -45 grados
	CImg<T> hy(3, 3, 1, 1, 0);
	hy(0, 0) = 0.0;
	hy(0, 1) = 0.0;
	hy(0, 2) = 1.0;
	hy(0, 3) = 0.0;
	hy(0, 4) = 0.0;

	hy(1, 0) = 0.0;
	hy(1, 1) = -1.0;
	hy(1, 2) = -2.0;
	hy(1, 3) = -1.0;
	hy(1, 4) = 0.0;

	hy(2, 0) = -1.0;
	hy(2, 1) = -2.0;
	hy(2, 2) = 16.0;
	hy(2, 3) = -2.0;
	hy(2, 4) = -1.0;

	hy(3, 0) = 0.0;
	hy(3, 1) = 0.0;
	hy(3, 2) = 1.0;
	hy(3, 3) = 0.0;
	hy(3, 4) = 0.0;

	hy(4, 0) = 0.0;
	hy(4, 1) = -1.0;
	hy(4, 2) = -2.0;
	hy(4, 3) = -1.0;
	hy(4, 4) = 0.0;
	return hy;
}

template<class T>
CImg<T> get_laplaciano1() {
	//genera una mascara de tipo laplaciano (no tien en cuenta las diagonales
	CImg<T> hy(3, 3, 1, 1, 0);
	hy(0, 0) = 0.0;
	hy(0, 1) = -1.0;
	hy(0, 2) = 0.0;

	hy(1, 0) = -1.0;
	hy(1, 1) = 4.0;
	hy(1, 2) = -1.0;

	hy(2, 0) = 0.0;
	hy(2, 1) = -1.0;
	hy(2, 2) = 0.0;
	return hy;
}

template<class T>
CImg<T> get_laplaciano2() {
	//genera una mascara de tipo laplaciano (tiene en cuenta las diagonales
	CImg<T> hy(3, 3, 1, 1, 0);
	hy(0, 0) = -1.0;
	hy(0, 1) = -1.0;
	hy(0, 2) = -1.0;

	hy(1, 0) = -1.0;
	hy(1, 1) = 8.0;
	hy(1, 2) = -1.0;

	hy(2, 0) = -1.0;
	hy(2, 1) = -1.0;
	hy(2, 2) = -1.0;
	return hy;
}

template<class T>
CImg<T> aplicar_roberts(CImg<T> imagen, bool binaria = true) {
	/*aplica una mascara de roberts a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_roberts_x<T> (), get_roberts_y<T> (), binaria);
}
template<class T>
CImg<T> aplicar_prewitt(CImg<T> imagen, bool binaria = true) {
	/*aplica una mascara de prewitt a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_prewitt_x<T> (), get_prewitt_y<T> (), binaria);
}
template<class T>
CImg<T> aplicar_sobel(CImg<T> imagen, bool binaria = true) {
	/*aplica una mascara de sobel a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_sobel_x<T> (), get_sobel_y<T> (), binaria);
}
template<class T>
CImg<T> aplicar_sobel_diagonal(CImg<T> imagen, bool binaria = true) {
	/*aplica una mascara de sobel para det de diag. a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_sobel_x_diagonal<T> (),
			get_sobel_y_diagonal<T> (), binaria);
}
template<class T>
CImg<T> aplicar_prewitt_diagonal(CImg<T> imagen, bool binaria = true) {
	/*aplica una mascara de prewitt para det de diag. a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_prewitt_x_diagonal<T> (),
			get_prewitt_y_diagonal<T> (), binaria);
}
template<class T>
CImg<T> aplicar_laplaciano(CImg<T> imagen, bool binaria = true) {
	/*aplica una mascara de laplaciano(sin tener en cuentas diagonales
	 *  a la imagen y devuelve el resultado
	 * */
	CImg<T> resul = imagen.channel(0).get_convolve(get_laplaciano1<T> ());
	resul.abs();
	if (binaria) {
		cimg_forXY(resul,x,y)
			{
				(resul(x, y) < 127) ? resul(x, y) = 0 : resul(x, y) = 255;
			}
	}
	return resul;
}

template<class T>
CImg<T> aplicar_laplaciano_condiagonales(CImg<T> imagen, bool binaria = true) {
	/*aplica una mascara de laplaciano (TIENE en cuentas diagonales
	 *  a la imagen y devuelve el resultado
	 * */
	CImg<T> resul = imagen.channel(0).get_convolve(get_laplaciano2<T> ());
	resul.abs();
	if (binaria) {
		cimg_forXY(resul,x,y)
			{
				(resul(x, y) < 127) ? resul(x, y) = 0 : resul(x, y) = 255;
			}
	}
	return resul;
}

template<class T>
CImg<T> aplicar_LoG(CImg<T> imagen, bool binaria = true) {
	/*aplica una mascara de laplaciano (TIENE en cuentas diagonales
	 *  a la imagen y devuelve el resultado
	 * */
	CImg<T> resul = imagen.channel(0).get_convolve(get_LoG<T> ());
	resul.abs();
	if (binaria) {
		cimg_forXY(resul,x,y)
			{
				(resul(x, y) < 127) ? resul(x, y) = 0 : resul(x, y) = 255;
			}
	}
	return resul;
}
