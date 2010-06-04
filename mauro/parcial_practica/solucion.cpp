// PARCIAL práctica captura
// Alumno: Mauro Torrez
// El código que está comentado queda sólo para referencia, para dar una idea de
// las cosas que fui probando, leer log.txt para la solución definitiva

#define UNICODE
#define cimg_use_fftw3
#include <CImg.h>
#include <algorithm>
#include "include.cpp"

#ifdef cimg_use_fftw3
extern "C" {
#include <fftw3.h>
}
#endif

using namespace cimg_library;
//using namespace std;

/**
 * suma_imagen_h
 * dada una magen de entrada, devuelve otra de ancho=1
 * cuyos valores son la suma de los pixelesde cada fila
 * correspondiente en la imagen original.
 */
template<class T>
CImg<T> suma_imagen_h( const CImg<T> img ) {
  CImg<T> salida( 1, img.height(), 1, img.spectrum(), 0 );
  unsigned x,y,c;
  cimg_forXYC ( img, x, y, c ) {
    salida(0,y,0,c) += img(x,y,0,c); 
  }
  return salida;
}

/**
 * apaga_blanco
 * dada una imagen de entrada RGB, devuelve otra tal que sus
 * píxeles que eran blancos o muy cercanos a blancos ahora
 * son negros
 */
template<class T>
CImg<T> apaga_blanco ( CImg<T> img, T umbral = 0.95 ) {
  CImg<T> salida( img );

  img.RGBtoHSI();
  salida.RGBtoHSI();

  unsigned x,y;
  cimg_forXY ( img, x, y ) {
    if ( img(x,y,0,2) >= umbral )
      salida(x,y,0,2) = (T)0;
  }
  salida.HSItoRGB();
  return salida;
}

/**
 * detectar_base_copa
 * detecta el limite inferior de la copa considerando a partir de cuándo
 * se detecta un nivel de intensidad menor al umbral
 * la imagen _img es de 1xn, con n>=240 px
 */
template<class T>
short detectar_base_copa ( CImg<T> img, T umbral = 0.7 ) {
  img.RGBtoHSI();
  img.channel(2).normalize(0.0,1.0);

  short y=240;

  for( y; y>-2; y-- ) {
    if( img(0,y) < umbral )
      return y;
  }
  return y;
}

/**
 * detectar_tope_vino
 * detecta el limite superior del vino a partir de cuando se
 * detecta una intensidad de fondo superior al umbral
 * la imagen _img es de 1xn, con n>=(comienzo) px
 */
template<class T>
short detectar_tope_vino ( CImg<T> img, short comienzo=200, T umbral = 0.7 ) {
  img.RGBtoHSI();
  img.channel(2).normalize(0.0,1.0);

  short y=comienzo;

  for( y; y>-2; y-- ) {
    if( img(0,y) > umbral )
      return y;
  }
  return y;
}

// /**
//  * detectar_hue_vino
//  * detecta el hue del vino entre los pixeles (base,tope)
//  */
// template<class T>
// T detectar_hue_vino ( CImg<T> img, Cmg<bool> mascara ) {
//   img.RGBtoHSI();
//   img.channel(0).normalize(0,240);
//   T hue_medio = 0;

//   // promedio hue
//   // no me dio el tiempo!!!

//   return 
// }


int main(int argc, char *argv[]) {

  const char *i1 = cimg_option( "-img", "imgs_train/blanco_3.jpg", "imagen entrada" );
  double hue = cimg_option( "-h", 60.0, "hue" );
  double sat = cimg_option( "-s", 0.9, "saturacion" );
  double radio = cimg_option( "-r", 0.7, "radio" );

  CImg<double> imagen ( i1 );

  // pasos para lograr el primer objetivo: deteccion de copa
  // 1. suma_imagen_h
  // 2. al resultado, me quedo con la ntensidad

  // CImg<double> sum =  suma_imagen_h( imagen ).normalize(0.0,1.0);
  // sum.RGBtoHSI();
  
  // CImg<double> intensidad = sum.get_channel(2);
  // intensidad.normalize(1.0,0.0).threshold(0.7);

  // CImgList<double>( suma_imagen_h<double>(imagen).normalize(0.0,1.0),
  // 		    // sum.get_channel(0).normalize(0.0,1.0),
  // 		    // sum.get_channel(1).normalize(0.0,1.0),
  // 		    // sum.get_channel(2).normalize(0.0,1.0)
  // 		    intensidad
  // 		    ).display();

  ///imagen.RGBtoHSI().display();

  // short base, tope;
  // base=detectar_base_copa<double>( CImg<double>(sum), 0.7 );
  // tope=detectar_tope_vino<double>( CImg<double>(sum), 0.7 );
  // double hue=detectar_hue_vino( CImg<double>(sum), base, tope);

  // printf( "base: %d, tope: %d, hue: %d\n", base, tope, hue);

  CImg<double> segm=segmentar_hs( imagen, hue, sat, radio );
  segm.display();

  CImg<double> umbral( segm);
  umbral.RGBtoHSI();
  umbral.channel(2); 
  umbral.threshold( 0.2 );
  // CImg<bool> umbralbin=umbral;
  // umbralbin.display();

  short base=240, tope=0, x, y;

  for( short y=240; y>0; y-- ) {
    if ( umbral.get_crop(0,y,umbral.width(),y).sum() < 1 )
      if( y<base )
	{
	base=y;
	}
    if( y<base && umbral.get_crop(0,y,umbral.width(),y).sum() > 1 )
      break;
  }

  for( short y=0; y<base; y++ ) {
    if ( umbral.get_crop(0,y,umbral.width(),y).sum() < 1 )
      if( y>tope )
	tope=y;
  } 

  // detecto la copa

  double porcentaje_llenado=0.0;

  if ( (abs(base-160)) < 20 ) // la copa es alta
    {
      printf("copa alta. ");
      printf("porcentaje llenado: %f", ((double)(base-tope)/150.0)*100.0);
    }
  if ( (abs(base-210)) < 20 ) // la copa es baja
    {
      printf("copa baja. ");
      printf("porcentaje llenado: %f\n", ((double)(base-tope)/170.0)*100.0);
    }    



  // CImg<double> centroide = detectar_coords_centroide_vino ( imagen, hue, sat, radio );

  printf( "base: %d, tope: %d\n", base, tope);

  return 0;
}

