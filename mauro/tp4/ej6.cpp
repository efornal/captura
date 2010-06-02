#define UNICODE
#include <CImg.h>
#include <iostream>
#include "comun.cpp"
#include "CPDSI_functions.h"

using namespace cimg_library;
using namespace std;

template<class T>
T max( T a, T b, T c ) {
  return max( a, max( b, c ) );
}

template<class T>
T min( T a, T b, T c ) {
  return min( a, min( b, c ) );
}

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
