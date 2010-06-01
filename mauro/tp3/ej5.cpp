#define UNICODE
#include <CImg.h>
#include "comun.cpp"

using namespace cimg_library;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    printf("%s: Convoluciona la imagen con kernel pasa-altos.\n", argv[0]);
    printf("uso: %s <archivo_imagen>",argv[0]);
    return 1;
  }

  CImg<double> kernel = kernel_mexican_hat<double>(3,3,1);

  CImg<double> imagen( argv[1] );

  CImg<double> conv = imagen.get_convolve( kernel ),
    corr = imagen.get_correlate( kernel );

  CImg<double> error( imagen );

  cimg_forXY( error, x, y ) {
    error(x,y) = conv(x,y) - corr(x,y);

  }

  kernel.display();
  conv.display();
  corr.display();
  error.display();
  
  return 0;
}

