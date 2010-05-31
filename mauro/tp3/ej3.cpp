#define UNICODE
#include <CImg.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cimg_library;
using namespace std;

template<class T>
CImg<T> kernel_gaussiano( unsigned w, unsigned h, double var=0.4, double mean=0.5 ) {
  CImg<T> k ( w, h, 1, 1 );
  unsigned x,y;
  cimg_forXY ( k, x, y ) {
    k(x,y) = exp( -( pow(x-(w-1)*mean,2)+pow(y-(h-1)*mean,2) ) / pow(var*w,2) );
  }
  return k;
}


int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": Convoluciona la imagen con diferentes kernels gaussianos.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    return 1;
  }

  CImg<double> kernel = kernel_gaussiano<double>(12,12);

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

