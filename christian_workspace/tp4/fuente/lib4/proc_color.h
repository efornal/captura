#include<CImg.h>
#include <string>
#include <vector>
#include "CPDSI_functions.h"
using namespace std;
using namespace cimg_library;

////////////////////////////////////////////////////////////////////////////////////////////
//De Mauro:
////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
T max(T a, T b, T c) {
	//devuelve el maximo valor de los arguementos
	return max(a, max(b, c));
}

template<class T>
T min(T a, T b, T c) {
	//devuelve el minimo valor de los arguementos
	return min(a, min(b, c));
}

template<class T>
bool pertenece_entorno(T h, T s, T h0, T s0, T radio = (T) 0.1, int norma = 2) {
	/**
	 * pertenece_entorno me dice si el color dado por (h, s) está dentro del entorno
	 * centrado en el punto (h0, s0) (notar que ignoro i). Este entorno se define
	 * según el radio radio y la norma norma: si radio=4 y norma=2 será un círculo
	 * centrado en (h0, s0); si norma=1 será un rombo, y si norma=0 un cuadrado.
	 * /// NOTAR que definí la norma 0 queriendo hacer en realidad la norma infinito,
	 *     asi que si norma=0 calcula la norma infinito.
	 * @param h, s: coordenadad h, s del color a comparar
	 * @param h0, s0: coordenadas h0, s0 del centro del entorno
	 * @param radio: radio del entorno
	 * @param norma: norma usada para definir el entorno (notar que supone 0=inf)
	 */
	switch (norma) {
	case 1:
		return ((abs(h - h0) / 240.0 + abs(s - s0)) / 2.0 <= radio) ? true
				: false;
	case 2:
		return (sqrt(pow((h - h0) / 240.0, 2) + pow(s - s0, 2)) <= radio) ? true
				: false;
	default:
		return (max(abs(h - h0) / 240.0, abs(s - s0)) <= radio) ? true : false;
	}
}

template<class T>
CImg<T> segmentar_hs(CImg<T> &img, T h, T s, T radio = (T) 2, int norma = 2) {
	/** entorno=0 se para en ese pixel nomas... y no saca el promedio...
	 * segmentar_hs segmenta la imagen en el espacio de color HSI, ignorando I, dejando
	 * solo aquellos colores que caen suficientemente "cerca" del entorno centrado en
	 * (h, s) con radio radio y calculado según la norma norma.
	 * @param img: imagen a segmentar, EN ESPACIO DE COLOR RGB
	 * @param h, s: coordenadas (h,s) del centro del entorno
	 * @param radio: radio del entorno
	 * @param norma: norma usada para calcular el entorno en el espacio HS
	 */
	CImg<bool> mascara(img.width(), img.height());
	CImg<T> resultado(img);
	img.RGBtoHSI();
	resultado.RGBtoHSI();
	cimg_forXY(img,x,y)
		{ //si queres obtener la mascara binaria hay que devolver la mascara
			mascara(x, y) = pertenece_entorno(img(x, y, 0, 0), img(x, y, 0, 1),
					h, s, radio, norma); //esto retorna true o false!
			if (!mascara(x, y)) { //si el pixel no pertenece al entorno lo pinto de negro
				resultado(x, y, 0, 2) = (T) 0; //pinto de negro componente de Intensidad = negro
			}
		}
	img.HSItoRGB();
	resultado.HSItoRGB();
	return resultado;
}

template<class T>
void promedio_valores_hsi(CImg<T> imagen, T &h, T &s, T &i, int entorno, int x,
		int y) {
	/**
	 * promedio_valores_hsi toma una vecindad centrada en (x,y) y con ancho
	 * y alto (2*entorno+1), de la imagen imagen y calcula los valores medios de
	 * los canales h, s, e i, seteandolos en estos parametros pasados por referencia
	 * @param imagen: la imagen de la que se saca el entorno
	 * @param h, s, i: variables donde se guradará eel color h, s, i promedio
	 * @param entorno: el "radio" (norma infinito) de la subimagen que se usara para
	 *                 calcular el promedio
	 * @param x, y: coordenadas del punto que será centro de la subimagen
	 * /// NOTAR la diferencia entre este entorno y los de las funciones arriba, este
	 *     entorno es simplemente una medida espacial, arriba era un nombre genérico
	 *     de una figura en el espacio, determinada por la norma y el radio
	 */
	imagen.RGBtoHSI();
	h = imagen.get_crop(max(0, x - entorno), max(0, y - entorno), min(
			imagen.width() - 1, x + entorno), min(imagen.height() - 1, y
			+ entorno)).channel(0).mean();
	s = imagen.get_crop(max(0, x - entorno), max(0, y - entorno), min(
			imagen.width() - 1, x + entorno), min(imagen.height() - 1, y
			+ entorno)).channel(1).mean();
	i = imagen.get_crop(max(0, x - entorno), max(0, y - entorno), min(
			imagen.width() - 1, x + entorno), min(imagen.height() - 1, y
			+ entorno)).channel(2).mean();
	imagen.HSItoRGB();
}

////////////////////////////////////////////////////////////////////////////////////////////
//Mis funciones:
////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
CImg<T> segmentaRGB(CImg<T> img, float radio_tol, float R, float G, float B,
		float *color_a_rellenar, bool color_verdadero = false) {
	/* img: imagen RGB a segmentar
	 * radio_tol: radio de tolerancia del color a segmentar en la esfera - el color a segmentar es el centro de la esfera.
	 * 			  La  misma esta dentro de cubo RGB a medida que se incrementa el radio, toma todos los valores dentro de la esfera
	 * 			  de radio radio_tol como valores a segmentar...
	 * R: valor del pixel Red del centro de la esfera
	 * G: valor del pixel green del centro de la esfera
	 * B: valor del pixel blue del centro de la esfera
	 * color_a_rellenar: es el color con el cual se quiere rellenar la parte segmentada de la no segmentada.
	 * color_verdadero(por default false): usa color_a_rellenar para la segmentacion. Si se cambia a true, ignora color_a_rellenar
	 * 										y usa los valores rgb originales de la imagen para la segmetnacion.
	 * */
	float distancia, r_img, g_img, b_img;
	R /= 255.0, G /= 255.0, B /= 255.0; // centro de la esfera es el punto RGB que seleccionaste...
	CImg<T> img_segmentada = img.normalize(0, 1);
	cimg_forXY(img_segmentada,x,y) //recorro imagen para ver si esta dentro de la esfera el putno o fuera de la misma con un radio te tolerancia
		{
			r_img = img(x, y, 0, 0);
			g_img = img(x, y, 0, 1);
			b_img = img(x, y, 0, 2);
			distancia = pow((r_img - R), 2) + pow((g_img - G), 2) + pow((b_img
					- B), 2); //ecuacion de la esfera r^2=(x-x0)^2+(y-y0)^2+(z-z0)^2
			distancia = sqrt(abs(distancia)); //obtengo r - distancia= distancia entre el punto que seleccione y el que estoy recorriendo de la imagen.
			if (color_verdadero) {
				if (distancia < radio_tol) {
					img_segmentada(x, y, 0, 0) = img(x, y, 0, 0);
					img_segmentada(x, y, 0, 1) = img(x, y, 0, 1);
					img_segmentada(x, y, 0, 2) = img(x, y, 0, 2);
				} else {
					img_segmentada(x, y, 0, 0) = 0;
					img_segmentada(x, y, 0, 1) = 0;
					img_segmentada(x, y, 0, 2) = 0;
				}
			} else { //relleno con el color que se paso por parametro
				if (distancia < radio_tol) {
					img_segmentada(x, y, 0, 0) = color_a_rellenar[0];
					img_segmentada(x, y, 0, 1) = color_a_rellenar[1];
					img_segmentada(x, y, 0, 2) = color_a_rellenar[2];
				}
			}
		}
	return img_segmentada;
}

template<class T>
void visualizar_HSI(CImg<T> &canal_h, CImg<T> &canal_s, CImg<T> &canal_i) {
	/* devuleve por referencia los canales HSI para poder ser visualizadas correctamente*/
	cimg_forXY(canal_h,x,y)
		{
			canal_h(x, y) = canal_h(x, y) / 360.0 * 255.0; //recordar que H esta entre 0 y 360
			canal_s(x, y) = canal_s(x, y) * 255.0; //recordar que S va de 0 a 1.0
			canal_i(x, y) = canal_i(x, y) * 255.0; //recordar que I esta entre 0 y 1.0
		}
}

template<class T>
CImg<T> componer_imagen(CImg<T> canal_rojo, CImg<T> canal_verde,
		CImg<T> canal_azul) {
	// a paritr de los canales pasados como parametros compone una imagen en RGB
	CImg<T> imagen(canal_rojo.width(), canal_rojo.height(), 1, 3);
	cimg_forXY(imagen, x, y)
		{
			imagen(x, y, 0, 0) = canal_rojo(x, y, 0, 0);
			if (canal_verde.spectrum() == 3) { //si tiene 3 canales
				imagen(x, y, 0, 1) = canal_verde(x, y, 0, 1);
			} else { //solo tiene un canal
				imagen(x, y, 0, 1) = canal_verde(x, y, 0, 0); //esto lo hago por si canal verde es de un solo canal
			}
			if (canal_azul.spectrum() == 3) { //si tiene 3 canales
				imagen(x, y, 0, 2) = canal_azul(x, y, 0, 2);
			} else { //solo tiene un canal
				imagen(x, y, 0, 2) = canal_azul(x, y, 0, 0); //esto lo hago por si canal verde es de un solo canal
			}
		}
	return imagen;
}

template<class T>
void descomponer_rgb3(CImg<T> &imagen_a_descomponer, CImg<T> &canal_R,
		CImg<T> &canal_G, CImg<T> &canal_B, bool ecualizar_por_separado = false) {
	/* Descompone una imagen RGB en sus canales
	 * devuelve los canales R, G y B con sus colores correspondientes por referencia
	 * OJO LOS CANALES QUE SE PASAN DEBEN SER DE 3 CANALES - ESTA ECHO ASI PARA LA VISUALIZACION
	 * ecualizar_por_separado = false implica que no haya ecualizacion por canal
	 * ecualizar_por_separado = true implica que devuelve por referencia cada canal ecualizado
	 */
	cimg_forXY(imagen_a_descomponer,x,y)
		{
			canal_R(x, y, 0, 0) = imagen_a_descomponer(x, y, 0, 0);//canal rojo
			canal_R(x, y, 0, 1) = 0; //POSTA: guarda porque la cimg_forXY te hace para todos los C si no le especificas nada!!
			canal_R(x, y, 0, 2) = 0;

			canal_G(x, y, 0, 0) = 0;//canal verde
			canal_G(x, y, 0, 1) = imagen_a_descomponer(x, y, 0, 1);//canal verde
			canal_G(x, y, 0, 2) = 0;//canal verde

			canal_G(x, y, 0, 0) = 0;//canal azul
			canal_G(x, y, 0, 1) = 0;//canal azul
			canal_B(x, y, 0, 2) = imagen_a_descomponer(x, y, 0, 2);//canal azul
		}
	if (ecualizar_por_separado) { //ecualizacion de cada canal por serparado
		canal_R.equalize(255);
		canal_G.equalize(255);
		canal_B.equalize(255);
		imagen_a_descomponer = componer_imagen<T> (canal_R, canal_G, canal_B);
		cout << endl << "Se ecualizaron los canales por serparado" << endl;
	}
}
template<class T>
void descomponer_rgb(CImg<T> &imagen_a_descomponer, CImg<T> &canal_R,
		CImg<T> &canal_G, CImg<T> &canal_B, bool ecualizar_por_separado = false) {
	/* Descompone una imagen RGB en sus canales
	 * devuelve los canales R, G y B con sus colores correspondientes por referencia
	 * ecualizar_por_separado = false implica que no haya ecualizacion por canal
	 * ecualizar_por_separado = true implica que devuelva los tres canales ecualizados por separado
	 */
	cimg_forXY(imagen_a_descomponer,x,y)
		{
			canal_R(x, y, 0, 0) = imagen_a_descomponer(x, y, 0, 0);//canal rojo
			canal_R(x, y, 0, 1) = 0;// negro al verde
			canal_R(x, y, 0, 2) = 0;// negro al azul

			canal_G(x, y, 0, 0) = 0;//canal rojo en 0
			canal_G(x, y, 0, 1) = imagen_a_descomponer(x, y, 0, 1);//canal verde
			canal_G(x, y, 0, 2) = 0;//canal azul en 0

			canal_B(x, y, 0, 0) = 0;//canal rojo en 0
			canal_B(x, y, 0, 1) = 0;//canal verde en 0
			canal_B(x, y, 0, 2) = imagen_a_descomponer(x, y, 0, 2);//canal azul
		}
	if (ecualizar_por_separado) { //ecualizacion de cada canal por serparado
		canal_R.channel(0).equalize(255);
		canal_G.channel(1).equalize(255);
		canal_B.channel(2).equalize(255);
		cout << endl << "Se ecualizaron los canales por serparado" << endl;
	}
}
template<class T>
CImg<T> ecualizar_por_separado(CImg<T> imagen) {
	/* Ecualiza cada canal por serparado y devuelve una imagen con los 3 canales ecualizados
	 * */
	CImg<T> imagen_devolver(imagen.width(), imagen.height(), 1, 3);
	return componer_imagen<T> (imagen.get_channel(0).equalize(255),
			imagen.get_channel(1).equalize(255),
			imagen.get_channel(2).equalize(255));
}

template<class T>
CImg<T> componer_imagen_hsi(CImg<T> canal_h, CImg<T> canal_s, CImg<T> canal_i) {
	/*Tener en cuenta que los canales que deben pasarseles a esta funcion son tal cula fueron devueltos por la fucnion
	 * get_RGB_TO_HSI()*/
	CImg<T> imagen(canal_h.width(), canal_h.height(), 1, 3);
	cimg_forXY(imagen, x, y)
		{
			imagen(x, y, 0, 0) = canal_h(x, y, 0, 0);
			imagen(x, y, 0, 1) = canal_s(x, y, 0, 0);
			imagen(x, y, 0, 2) = canal_i(x, y, 0, 0);
		}
	return imagen;
}

template<class T>
CImg<T> invertir_HSI(CImg<T> imagen_H) {
	/* si era rojo tiene que ser azul....
	 * para ello modifico el canal H
	 * */
	cimg_forXY(imagen_H, x, y)
		{
			imagen_H(x, y, 0, 0) = imagen_H(imagen_H.height() - 1 - x, y, 0, 0); //reflexion horizontal
		}
	return imagen_H;
}
template<class T>
CImg<T> aplicar_paleta(CImg<T> imagen, int numero_paleta = 1) {
	/* carga una paleta con nombre_paleta la aplica a la imagen pasada como parametro y
	 * devuelve la imagen con la paleta aplicada
	 * @numeropaleta=1 -> ../../paletas/bone.pal
	 * @numeropaleta=2 -> ../../paletas/cool.pal
	 * @numeropaleta=3 -> ../../paletas/copper.pal
	 * @numeropaleta=4 -> ../../paletas/gray.pal
	 * @numeropaleta=5 -> ../../paletas/hot.pal
	 * @numeropaleta=6 -> ../../paletas/hsv.pal
	 * @numeropaleta=7 -> ../../paletas/jet.pal
	 * @numeropaleta=8 -> ../../paletas/pink.pal
	 * */
	vector<vector<float> > paleta; //creo un vecotr de vecotres
	switch (numero_paleta) {
	case 1:
		cargar_paleta(paleta, "../../paletas/bone.pal");
		break;
	case 2:
		cargar_paleta(paleta, "../../paletas/cool.pal");
		break;
	case 3:
		cargar_paleta(paleta, "../../paletas/copper.pal");
		break;
	case 4:
		cargar_paleta(paleta, "../../paletas/gray.pal");
		break;
	case 5:
		cargar_paleta(paleta, "../../paletas/hot.pal");
		break;
	case 6:
		cargar_paleta(paleta, "../../paletas/hsv.pal");
		break;
	case 7:
		cargar_paleta(paleta, "../../paletas/jet.pal");
		break;
	case 8:
		cargar_paleta(paleta, "../../paletas/pink.pal");
		break;
	default:
		break;
	}

	CImg<T> imagen_con_paleta_aplicada(imagen.width(), imagen.height(), 1, 3);
	cimg_forXY(imagen_con_paleta_aplicada, x, y)
		{ //es mas o menos una lut...
			imagen_con_paleta_aplicada(x, y, 0, 0) = paleta[imagen(x, y)][0]
					* 255.0; //canal rojo
			imagen_con_paleta_aplicada(x, y, 0, 1) = paleta[imagen(x, y)][1]
					* 255.0; //canal verde
			imagen_con_paleta_aplicada(x, y, 0, 2) = paleta[imagen(x, y)][2]
					* 255.0; //canal azul
		}
	return imagen_con_paleta_aplicada;
}
template<class T>
CImg<T> get_binary(CImg<T> imagen) {
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
