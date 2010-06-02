#define UNICODE
#include <CImg.h>
//#include <vector>
#include "comun.cpp"
//#include "CPDSI_functions.h"

using namespace cimg_library;
//using namespace std;



int main(int argc, char *argv[]) {

  const char *im = cimg_option( "-img", "../img/rio.jpg", "imagen" );

  CImg<double> gris( im );
  CImgDisplay d_histo, d_imagen;
  CImg<double> histograma(256,256,1,1);
  double negro[] = {0};
  gris.normalize(0,255);
  histograma.fill(200,200,200).draw_graph(gris.get_histogram(256),negro);
  histograma.display( d_histo);
  unsigned umbral = 0;
  pintar_grises<double,double>( gris, 0, umbral ).display(d_imagen);
  while( !d_imagen.is_closed() && !d_histo.is_closed() ) {
    d_imagen.wait_all();
    if ( d_imagen.is_keyARROWUP() ) {
      umbral += 1;
      pintar_grises<double,double>( gris, 0, umbral ).display(d_imagen);
    }
    if ( d_imagen.is_keyARROWDOWN() ) {
      umbral -= 1;
      pintar_grises<double,double>( gris, 0, umbral ).display(d_imagen);
    }
  }

  return 0;
}
