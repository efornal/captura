#define UNICODE
#include <CImg.h>

using namespace cimg_library;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    printf( "%s: Convoluciona la imagen con un kernel de 3x3.\n", argv[0] );
    printf( "uso: %s <archivo_imagen>\n", argv[0] );
    return 1;
  }

  CImg<double> kernel ( 3,3,1,1,1);

  kernel(0,0)=0; kernel(1,0)=1; kernel(2,0)=2;
  kernel(0,1)=1; kernel(1,1)=2; kernel(2,1)=1;
  kernel(0,2)=2; kernel(1,2)=1; kernel(2,2)=0;

  CImg<double> imagen( argv[1] );

  CImgList<double> result ( imagen.get_normalize(0,255),
			    kernel.get_normalize(0,255),
			    imagen.get_convolve( kernel ).get_normalize(0,255) );

  result.display();
  
  return 0;
}

