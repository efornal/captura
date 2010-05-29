/*
 * filtros.h
 *
 *  Created on: 16/05/2010`
 *      Author: christian
 */

#include <CImg.h>
#include <vector>
using namespace std;
using namespace cimg_library;

//horizontal
template<class T>
CImg<T> get_horizontal() {
	//genera una mascara que detecta bordes horizontalmente
	CImg<T> hx(3, 3, 1, 1, -1);
	hx(1, 0) = 2.0;
	hx(1, 1) = 2.0;
	hx(1, 2) = 2.0;
	return hx;
}

//diagonal 45 grados
template<class T>
CImg<T> get_diag_45() {
	//genera una mascara que detecta bordes a 45 grados
	CImg<T> hx(3, 3, 1, 1, -1);
	hx(0, 2) = 2.0;
	hx(1, 1) = 2.0;
	hx(2, 0) = 2.0;
	return hx;
}

//diagonal -45 grados
template<class T>
CImg<T> get_diag_135() {
	//genera una mascara que detecta bordes a -45=135 grados
	CImg<T> hx(3, 3, 1, 1, -1);
	hx(0, 0) = 2.0;
	hx(1, 1) = 2.0;
	hx(2, 2) = 2.0;
	return hx;
}
//vertical
template<class T>
CImg<T> get_vertical() {
	//genera una mascara que detecta bordes a -45=135 grados
	CImg<T> hx(3, 3, 1, 1, -1);
	hx(0, 1) = 2.0;
	hx(1, 1) = 2.0;
	hx(2, 1) = 2.0;
	return hx;
}

template<class T>
CImg<T> segmentar(CImg<T> imagen, CImg<T> mascara_x, CImg<T> mascara_y,
		float umbral = 40.0, bool binaria = true) {
	/* LA IMAGEN DEVUELTA ES NORMALIZADA ENTRE 0 Y 255
	 * fucnion generica que segmenta una imagen con las mascaras pasadas por parametro
	 * por defecto binaria=true indica que devuelve una imagen binaria como resultado
	 * @umbral= valor de umbral para binarizado para valores menosres asigna 0
	 * */
	CImg<T> img_filx = imagen.get_convolve(mascara_x).get_abs();
	CImg<T> img_fily = imagen.get_convolve(mascara_y).get_abs();
	// armamos el grandiente

	CImg<T> suma(img_filx.width(), img_filx.height(), 1, 1, 0);

	cimg_forXY(imagen,x,y)
		{
			suma(x, y) = img_filx(x, y) + img_fily(x, y);
		}
	suma.normalize(0, 255); //normalizo porque los valores estan por encima de 255

	if (binaria) {
		cimg_forXY(imagen, x, y)
			{
				(suma(x, y) < umbral) ? suma(x, y) = 0 : suma(x, y) = 255;
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
	CImg<T> hy(5, 5, 1, 1, 0);
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
CImg<T> aplicar_roberts(CImg<T> imagen, float umbral = 40.0, bool binaria =
		true) {
	/*aplica una mascara de roberts a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_roberts_x<T> (), get_roberts_y<T> (), umbral,
			binaria);
}
template<class T>
CImg<T> aplicar_prewitt(CImg<T> imagen, float umbral = 40.0, bool binaria =
		true) {
	/*aplica una mascara de prewitt a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_prewitt_x<T> (), get_prewitt_y<T> (), umbral,
			binaria);
}
template<class T>
CImg<T> aplicar_sobel(CImg<T> imagen, float umbral = 40.0, bool binaria = true) {
	/*aplica una mascara de sobel a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_sobel_x<T> (), get_sobel_y<T> (), umbral,
			binaria);
}
template<class T>
CImg<T> aplicar_sobel_diagonal(CImg<T> imagen, float umbral = 40.0,
		bool binaria = true) {
	/*aplica una mascara de sobel para det de diag. a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_sobel_x_diagonal<T> (),
			get_sobel_y_diagonal<T> (), umbral, binaria);
}
template<class T>
CImg<T> aplicar_prewitt_diagonal(CImg<T> imagen, float umbral = 40.0,
		bool binaria = true) {
	/*aplica una mascara de prewitt para det de diag. a la imagen y devuelve el resultado
	 * */
	return segmentar(imagen, get_prewitt_x_diagonal<T> (),
			get_prewitt_y_diagonal<T> (), umbral, binaria);
}
template<class T>
CImg<T> aplicar_laplaciano(CImg<T> imagen, float umbral = 40.0, bool binaria =
		true) {
	/*aplica una mascara de laplaciano(sin tener en cuentas diagonales
	 *  a la imagen y devuelve el resultado
	 * */
	CImg<T> resul = imagen.channel(0).get_convolve(get_laplaciano1<T> ());
	resul.abs();
	if (binaria) {
		cimg_forXY(resul,x,y)
			{
				(resul(x, y) < umbral) ? resul(x, y) = 0 : resul(x, y) = 255;
			}
	}
	return resul;
}

template<class T>
CImg<T> aplicar_laplaciano_condiagonales(CImg<T> imagen, float umbral = 40.0,
		bool binaria = true) {
	/*aplica una mascara de laplaciano (TIENE en cuentas diagonales
	 *  a la imagen y devuelve el resultado
	 * */
	CImg<T> resul = imagen.channel(0).get_convolve(get_laplaciano2<T> ());
	resul.abs();
	if (binaria) {
		cimg_forXY(resul,x,y)
			{
				(resul(x, y) < umbral) ? resul(x, y) = 0 : resul(x, y) = 255;
			}
	}
	return resul;
}

template<class T>
CImg<T> aplicar_LoG(CImg<T> imagen, float umbral = 40.0, bool binaria = true) {
	/*aplica una mascara de laplaciano (TIENE en cuentas diagonales
	 *  a la imagen y devuelve el resultado
	 * */
	CImg<T> resul = imagen.channel(0).get_convolve(get_LoG<T> ());
	resul.abs();
	if (binaria) {
		cimg_forXY(resul,x,y)
			{
				(resul(x, y) > umbral) ? resul(x, y) = 0 : resul(x, y) = 255;
			}
	}
	return resul;
}
template<class T>
vector<T> get_pos_max(CImg<T> imagen) {
	/* Retorna en un vector la posicion del maximo de una imagen;
	 * */
	T posx = -1, posy = -1;
	T valor = -9999;
	cimg_forXY(imagen, x, y)
		{
			if (imagen(x, y) > valor) {
				posx = x;
				posy = y;
				valor = imagen(x, y);
			}
		}
	vector<T> max;
	max.push_back(posx);
	max.push_back(posy);
	return max;
}
/* funciones para transformada de hough*/
template<class T>
vector<T> obtener_maximos(CImg<T> imagen, int cantidad = 1, int direccion = -99) {
	/* funcion que deuvelve en un arrelgo la cantidad de maximos especificados
	 * siendo la pos 0 del arreglo el maximo de la imagen, pos 1 el anterior al maximo, etc.
	 * @param imagen: es la imagen sobre la cual se hallara los maximos (debe ser la imagen del espacio
	 * de hough que se obtuvo a partir de una imagen de bordes... imagen=hough_directa(bordes(imagen_bordes))
	 * @param cantidad: cantidad de maximos que se desean extraer de la imagen..
	 * @param direccion: obtiene solo los maximos en la direccion especificada por defecto 90 grados.
	 * 					 si el parametro vale -99 especifica que se hallan maximos en _todo el plano transf
	 * 					 sin importar la direccion
	 * 					 el valor de direccion debe estar entre -90 y 90.
	 *
	 * */
	vector<T> maximo_actual;
	vector<T> maximos;

	if (direccion != -99) { //busca en direccion especifica
		int ancho = imagen.width() - 1;
		int alto = imagen.height() - 1;
		int medio = (int) ancho / 2.0; // este va a ser el 0 grados

		int x = medio + (int) ((direccion * (ancho - medio)) / 90.0);
		imagen.crop(x, 0, x, alto); //ojo con los 90 y -90 explota creo
		//imagen.display();

		//hay que hacerlo asi ya que maximo me devuelve un vector con posx(que en este caso va a ser siempre 0!)
		for (int i = 0; i < cantidad; i++) {
			maximo_actual.clear();
			maximo_actual = get_pos_max(imagen); //tengo la posicion del maximo de la imagen
			maximos.push_back(maximo_actual[0] + x);
			maximos.push_back(maximo_actual[1]);
			imagen(maximo_actual[0], maximo_actual[1]) = 0; // lo pongo negro para que detecte el proximo maximo
		}
	} else {
		for (int i = 0; i < cantidad; i++) {
			maximo_actual.clear();
			maximo_actual = get_pos_max(imagen); //tengo la posicion del maximo de la imagen
			maximos.push_back(maximo_actual[0]);
			maximos.push_back(maximo_actual[1]);
			imagen(maximo_actual[0], maximo_actual[1]) = 0; // lo pongo negro para que detecte el proximo maximo
		}
	}
	return maximos;
}

template<class T>
CImg<T> colorea_rojo(CImg<T> imagen) {
	/* colorea los bordes de la imagen con rojo
	 * */
	CImg<double> color(imagen.width(), imagen.height(), 1, 3, 0);
	cimg_forXY(color,x,y)
		{
			color(x, y, 0, 0) = imagen(x, y);
			color(x, y, 0, 1) = 0.0;
			color(x, y, 0, 2) = 0.0;
		}
	return color;
}
