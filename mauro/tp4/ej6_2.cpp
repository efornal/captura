#define UNICODE
#include <CImg.h>
#include <iostream>
#include "comun.cpp"
#include "CPDSI_functions.h"

using namespace cimg_library;
using namespace std;

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
template<class T>
bool pertenece_entorno( T h, T s, T h0, T s0, T radio=(T)0.1, int norma=2 ){
  switch( norma ) {
  case 1:
    return ((abs(h-h0)/240.0+abs(s-s0))/2.0 <= radio )? true:false;
  case 2:
    return (sqrt(pow((h-h0)/240.0,2)+pow(s-s0,2))<=radio)? true:false;
  default:
    return (max(abs(h-h0)/240.0,abs(s-s0)) <= radio )? true:false;
  }
}

/**
 * segmentar_hs segmenta la imagen en el espacio de color HSI, ignorando I, dejando
 * solo aquellos colores que caen suficientemente "cerca" del entorno centrado en
 * (h, s) con radio radio y calculado según la norma norma.
 * @param img: imagen a segmentar, EN ESPACIO DE COLOR RGB
 * @param h, s: coordenadas (h,s) del centro del entorno
 * @param radio: radio del entorno
 * @param norma: norma usada para calcular el entorno en el espacio HS
 */
template<class T>
CImg<T> segmentar_hs ( CImg<T> &img, T h, T s, T radio=(T)2, int norma=2 ) {

  CImg<bool> mascara( img.width(), img.height() );
  CImg<T> resultado(img);
  img.RGBtoHSI();
  resultado.RGBtoHSI();
  unsigned x, y;
  cimg_forXY(img,x,y) {
    mascara(x,y) = pertenece_entorno( img(x,y,0,0), img(x,y,0,1), h, s, radio, norma );
    if ( ! mascara(x,y) ){
      resultado(x,y,0,2)=(T)0;
    }
  }
  img.HSItoRGB();
  resultado.HSItoRGB();
  return resultado;
}

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
template<class T>
void promedio_valores_hsi( CImg<T>imagen, T &h, T &s, T &i,
			   int entorno, int x, int y ) {
  imagen.RGBtoHSI();
  h = imagen.get_crop(max(0,x-entorno), max(0,y-entorno),
		      min(imagen.width()-1,x+entorno),
		      min(imagen.height()-1,y+entorno)).channel(0).mean();
  s = imagen.get_crop(max(0,x-entorno), max(0,y-entorno),
		      min(imagen.width()-1,x+entorno),
		      min(imagen.height()-1,y+entorno)).channel(1).mean();
  i = imagen.get_crop(max(0,x-entorno), max(0,y-entorno),
		      min(imagen.width()-1,x+entorno),
		      min(imagen.height()-1,y+entorno)).channel(2).mean();
  imagen.HSItoRGB();
}


int main(int argc, char *argv[]) {

  const char *im = cimg_option( "-img", "../img/futbol.jpg", "imagen" );

  CImg<double> imagen( im );
  CImgDisplay d_imagen;

  double radio = 0.1;
  int norma = 2, entorno=2;

  double h, s, i;

  int x, y;

  //  imagen.RGBtoHSI();

  imagen.display( d_imagen );

  while( !d_imagen.is_closed() ) {
    d_imagen.wait_all();

    if ( d_imagen.button() && d_imagen.mouse_x() >=0 &&
	 d_imagen.mouse_y() >=0 ) {
      x = d_imagen.mouse_x();
      y = d_imagen.mouse_y();
      promedio_valores_hsi( imagen, h, s, i, entorno, x, y );

      printf("\n H=%f, S=%f, I=%f\n", h, s, i );

      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyN() ) {
      ++norma %= 3;
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWUP() ) {
      radio += 0.05;
      printf("\n radio=%f\n", radio );
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWDOWN() ) {
      radio -= 0.05;
      printf("\n radio=%f\n", radio );
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWLEFT() ) {
      --entorno;
      promedio_valores_hsi( imagen, h, s, i, entorno, x, y );
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWRIGHT() ) {
      ++entorno;
      promedio_valores_hsi( imagen, h, s, i, entorno, x, y );
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyR() ) {
      radio = 6;
      norma = 0;
      entorno = 2;
      promedio_valores_hsi( imagen, h, s, i, entorno, x, y );
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
  }
  return 0;
}
