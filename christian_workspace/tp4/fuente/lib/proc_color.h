/*
 * canales.h
 *
 *  Created on: 15/04/2010
 *      Author: christian
 */
#include<CImg.h>
#include <string>
#include <vector>
#include "../lib/CPDSI_functions.h"
using namespace std;
using namespace cimg_library;

template<class T>

CImg<T> segmentaRGB(CImg<T> img, float radio_tol, float R, float G, float B,
		float *color_a_rellenar) {
	float distancia, r_original, g_original, b_original;
	R /= 255.0, G /= 255.0, B /= 255.0; // centro de la esfera
	CImg<T> img_segmentada = img.normalize(0, 1);
	cimg_forXY(img_segmentada,x,y)
		{
			r_original = img(x, y, 0, 0);
			g_original = img(x, y, 0, 1);
			b_original = img(x, y, 0, 2);
			distancia = (r_original - R) * (r_original - R) + (g_original - G) * (g_original - G) + (b_original - B) * (b_original
					- B); //ecuacion de la esfera ojo r^2...
			distancia = sqrt(abs(distancia)); //r
			if (distancia < radio_tol) {
				img_segmentada(x, y, 0, 0) = color_a_rellenar[0];
				img_segmentada(x, y, 0, 1) = color_a_rellenar[1];
				img_segmentada(x, y, 0, 2) = color_a_rellenar[2];
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
	CImg<T> imagen(canal_rojo.width(), canal_rojo.height(), 1, 3);
	cimg_forXY(imagen, x, y)
		{
			imagen(x, y, 0, 0) = canal_rojo(x, y);
			imagen(x, y, 0, 1) = canal_verde(x, y);
			imagen(x, y, 0, 2) = canal_azul(x, y);
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
			canal_G(x, y, 0, 1) = imagen_a_descomponer(x, y, 0, 1);//canal rojo
			canal_B(x, y, 0, 2) = imagen_a_descomponer(x, y, 0, 2);//canal rojo
		}
	if (ecualizar_por_separado) { //ecualizacion de cada canal por serparado
		canal_R.equalize(0, 255);
		canal_G.equalize(0, 255);
		canal_B.equalize(0, 255);
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
	 * ecualizar_por_separado = true implica que devuelve por referencia cada canal ecualizado
	 */
	cimg_forXY(imagen_a_descomponer,x,y)
		{
			canal_R(x, y, 0, 0) = imagen_a_descomponer(x, y, 0, 0);//canal rojo
			canal_G(x, y, 0, 0) = imagen_a_descomponer(x, y, 0, 1);//canal rojo
			canal_B(x, y, 0, 0) = imagen_a_descomponer(x, y, 0, 2);//canal rojo
		}
	if (ecualizar_por_separado) { //ecualizacion de cada canal por serparado
		canal_R.equalize(0, 255);
		canal_G.equalize(0, 255);
		canal_B.equalize(0, 255);
		imagen_a_descomponer = componer_imagen<T> (canal_R, canal_G, canal_B);
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

CImg<float> aplicar_paleta(CImg<float> imagen, int numero_paleta = 1) {
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

	CImg<float> imagen_con_paleta_aplicada(imagen.width(), imagen.height(), 1,
			3);
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
