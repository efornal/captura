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
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyN() ) {
      ++norma %= 3;
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWUP() ) {
      radio += 0.05;
      segmentar_hs( imagen, h, s, radio, norma ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWDOWN() ) {
      radio -= 0.05;
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
