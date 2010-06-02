#define UNICODE
#include <CImg.h>
#include <iostream>
#include "comun.cpp"
#include "CPDSI_functions.h"

using namespace cimg_library;
using namespace std;

/**
 * max devuelve el máximo de los 3
 */
template<class T>
T max( T a, T b, T c ) {
  return max( a, max( b, c ) );
}

/**
 * max devuelve el mínimo de los 3
 */
template<class T>
T min( T a, T b, T c ) {
  return min( a, min( b, c ) );
}

/**
 * pertenece_entorno me dice si el color dado por r, g, b está dentro del entorno
 * centrado en el punto (r0, g0, b0). Este entorno se define según el radio radio
 * y la norma norma: si radio=4 y norma=2 será una esfera centrada en r0, g0, b0;
 * si norma=1 la esfera será un "rombo", si norma=0 un cubo.
 * /// NOTAR que definí la norma 0 queriendo hacer en realidad la norma infinito,
 *     asi que si norma=0 calcula la norma infinito.
 * @param r, g, b: coordenadas r, g, b del color a comparar
 * @param r0, g0, b0: coordenadas del centro del entorno
 * @param radio: radio del entorno
 * @param norma: norma usada para definir el entorno (notar que supone 0=inf) 
*/
template<class T>
bool pertenece_entorno( T r, T g, T b, T r0, T g0, T b0, T radio=(T)2, int norma=2 ){
  switch( norma ) {
  case 1:
    return ((abs(r-r0)+abs(g-g0)+abs(b-b0))/3.0 <= radio )? true:false;
  case 2:
    return (sqrt(pow(r-r0,2)+pow(g-g0,2)+pow(b-b0,2))<=radio)? true:false;
  default:
    return ( max(abs(r-r0),abs(g-g0),abs(b-b0)) <= radio )? true:false;
  }
}

/**
 * segmentar_rgb segmenta la imagen en el espacio de color, dejando solo aquellos
 * colores que caben suficientemente "cerca" del entorno centrado en (r, g, b)
 * con radio radio y calculado según la norma norma.
 * @param img: imagen a segmentar
 * @param r, g, b: coordenadas r g y b del centro del entorno
 * @param radio: radio del entorno
 * @param norma: norma usada para calcular el entorno en el espacio RGB
 */
template<class T>
CImg<T> segmentar_rgb ( const CImg<T> &img, T r, T g, T b, T radio=(T)2, int norma=2 ) {
  CImg<bool> mascara( img.width(), img.height() );
  CImg<T> resultado(img);
  unsigned x, y;
  cimg_forXY(img,x,y) {
    mascara(x,y) = pertenece_entorno( img(x,y,0,0), img(x,y,0,1), img(x,y,0,2),
				      r, g, b, radio, norma );
    if ( ! mascara(x,y) ){
      resultado(x,y,0,0)=(T)0;
      resultado(x,y,0,1)=(T)0;
      resultado(x,y,0,2)=(T)0;
    }
  }
  return resultado;
}

/**
 * promedio_valores_rgb toma una vecindad centrada en (x,y) y con ancho
 * y alto (2*entorno+1), de la imagen imagen y calcula los valores medios de
 * los canales r, g y b, seteandolos en estos parametros pasados por referencia
 * @param imagen: la imagen de la que se saca el entorno
 * @param r, g, b: variables donde se guradará eel color r, g, b promedio
 * @param entorno: el "radio" (norma infinito) de la subimagen que se usara para
 *                 calcular el promedio
 * @param x, y: coordenadas del punto que será centro de la subimagen
 * /// NOTAR la diferencia entre este entorno y los de las funciones arriba, este
 *     entorno es simplemente una medida espacial, arriba era un nombre genérico
 *     de una figura en el espacio, determinada por la norma y el radio
 */
template<class T>
void promedio_valores_rgb( CImg<T>imagen, T &r, T &g, T &b,
			   int entorno, int x, int y ) {
  r = imagen.get_crop(max(0,x-entorno), max(0,y-entorno),
		      min(imagen.width()-1,x+entorno),
		      min(imagen.height()-1,y+entorno)).channel(0).mean();
  g = imagen.get_crop(max(0,x-entorno), max(0,y-entorno),
		      min(imagen.width()-1,x+entorno),
		      min(imagen.height()-1,y+entorno)).channel(1).mean();
  b = imagen.get_crop(max(0,x-entorno), max(0,y-entorno),
		      min(imagen.width()-1,x+entorno),
		      min(imagen.height()-1,y+entorno)).channel(2).mean();
}

int main(int argc, char *argv[]) {

  const char *im = cimg_option( "-img", "../img/futbol.jpg", "imagen" );

  CImg<double> imagen( im );
  CImgDisplay d_imagen;

  double radio = 2;
  int norma = 2, entorno=2;

  double r, g, b;

  int x, y;

  imagen.display( d_imagen );

  while( !d_imagen.is_closed() ) {
    d_imagen.wait_all();

    if ( d_imagen.button() && d_imagen.mouse_x() >=0 &&
	 d_imagen.mouse_y() >=0 ) {
      x = d_imagen.mouse_x();
      y = d_imagen.mouse_y();
      promedio_valores_rgb( imagen, r, g, b, entorno, x, y );
      segmentar_rgb( imagen, r, g, b, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyN() ) {
      ++norma %= 3;
      segmentar_rgb( imagen, r, g, b, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWUP() ) {
      ++radio;
      segmentar_rgb( imagen, r, g, b, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWDOWN() ) {
      --radio;
      segmentar_rgb( imagen, r, g, b, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWLEFT() ) {
      --entorno;
      promedio_valores_rgb( imagen, r, g, b, entorno, x, y );
      segmentar_rgb( imagen, r, g, b, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWRIGHT() ) {
      ++entorno;
      promedio_valores_rgb( imagen, r, g, b, entorno, x, y );
      segmentar_rgb( imagen, r, g, b, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyR() ) {
      radio = 6;
      norma = 0;
      entorno = 2;
      promedio_valores_rgb( imagen, r, g, b, entorno, x, y );
      segmentar_rgb( imagen, r, g, b, radio, norma ).display(d_imagen);
    }


  }

  return 0;
}
