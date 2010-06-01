#define UNICODE
#include <CImg.h>
#include "comun.cpp"

using namespace cimg_library;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    printf( "%s: Aplica máscaras de promediado sobre una imagen.\n", argv[0] );
    printf( "uso: %s <archivo_imagen>\n", argv[0] );
    return 1;
  }

  CImg<double> kernel = kernel_promedio<double>(12,12);

  CImg<double> imagen( argv[1] );

  CImg<double> conv = imagen.get_convolve( kernel );

  CImgList<double> muestra( kernel.get_normalize(0,255),
			    imagen.get_normalize(0,255),
			    conv.get_normalize(0,255) );

  muestra.display();
  
  return 0;
}
