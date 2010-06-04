// PARCIAL práctica captura
// Alumno: Mauro Torrez
// El código que está comentado queda sólo para referencia, para dar una idea de
// las cosas que fui probando, leer log.txt para la solución definitiva

#define UNICODE
//#define cimg_use_fftw3
#include <CImg.h>
//#include <algorithm>
#include "include.cpp"

// #ifdef cimg_use_fftw3
// extern "C" {
// #include <fftw3.h>
// }
// #endif

using namespace cimg_library;
//using namespace std;

int main(int argc, char *argv[]) {

  const char *i1 = cimg_option( "-img", "imgs_train/blanco_3.jpg", "imagen entrada" );
  double hue = atof( cimg_option( "-h", "30.0", "hue" ));
  double sat = atof( cimg_option( "-s", "0.3", "saturacion" ));
  double radio = atof( cimg_option( "-r", "0.2", "radio" ));

  CImg<double> imagen ( i1 );

  CImg<double> segm=segmentar_hs( imagen, hue, sat, radio );
  segm.display();

  CImg<double> umbral( segm);
  umbral.RGBtoHSI();

  umbral.channel(2); 
  umbral.threshold( 0.2 );
  CImg<bool> umbralbin=umbral;
  //  umbralbin.display();

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

  printf("\n #############################\n #############################\n");

  if ( (abs(base-160)) < 20 ) // la copa es alta
    {
      printf(" * copa alta.\n");
      printf(" * %f%% llena.\n", ((double)(base-tope)/150.0)*100.0);
    }
  if ( (abs(base-210)) < 20 ) // la copa es baja
    {
      printf(" * copa baja. \n");
      printf(" * %f%% llena.\n", ((double)(base-tope)/170.0)*100.0);
    }    

  CImg<double> huenorm = obtener_hue_180( segm );
  //  huenorm.display();

  // detecto el vino
  double hue_vino = huenorm.get_mul(umbral).sum() / umbral.sum();

  if ( abs(hue_vino) < 30 )
    printf(" * vino tinto.\n");
  if ( abs(hue_vino-60.0) < 30 )
      printf(" * vino blanco.\n");

  printf( "\n (base: %d, tope: %d, hue: %f)", base, tope, hue_vino);
  printf("\n #############################\n #############################\n");

  return 0;
}

