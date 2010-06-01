#define UNICODE
#include <CImg.h>

using namespace cimg_library;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    printf( "%s: Compara convolucion vs correlación.\n", argv[0] );
    printf( "uso: %s <archivo_imagen>\n", argv[0] );
    return 1;
  }

  CImg<double> kernel ( 3,3,1,1,1);

  // hago el kernel asimétrico (i.e. diferente si lo roto 180°)
  // cosa que me de error cuando comparo convolucion vs correlación
  kernel(0,0)=0; kernel(1,0)=1; kernel(2,0)=2;
  kernel(0,1)=0; kernel(1,1)=2; kernel(2,1)=0;
  kernel(0,2)=2; kernel(1,2)=1; kernel(2,2)=2;

  CImg<double> imagen( argv[1] );

  CImg<double> conv = imagen.get_convolve( kernel ),
    corr = imagen.get_correlate( kernel );

  CImg<double> error( imagen );

  unsigned x, y;
  cimg_forXY( error, x, y ) {
    error(x,y) = conv(x,y) - corr(x,y);
  }

  printf( "Error cuadrático medio: %f\n", conv.MSE(corr) );

  CImgList<double> result ( conv.get_normalize(0,255),
			    corr.get_normalize(0,255),
			    error.get_normalize(0,255) );

  result.display();
  
  return 0;
}

