#define UNICODE
#include <CImg.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": Convoluciona la imagen con u kernel de 3x3.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    return 1;
  }

  CImg<double> kernel ( 3,3,1,1,1);
  unsigned x, y;
  kernel(0,0)=0; kernel(1,0)=1; kernel(2,0)=2;
  kernel(0,1)=0; kernel(1,1)=2; kernel(2,1)=0;
  kernel(0,2)=2; kernel(1,2)=1; kernel(2,2)=2;

  CImg<double> imagen( argv[1] );

  CImg<double> conv = imagen.get_convolve( kernel ),
    corr = imagen.get_correlate( kernel );

  CImgList<double> result ( imagen.get_normalize(0,255),
			    imagen.get_convolve( kernel ).get_normalize(0,255),
			    imagen.get_correlate(kernel ).get_normalize(0,255) );

  CImg<double> error( imagen );

  cimg_forXY( error, x, y ) {
    error(x,y) = conv(x,y) - corr(x,y);
  }

  conv.get_normalize(0,255).display();
  corr.get_normalize(0,255).display();
  error.get_normalize(0,255).display();
  
  return 0;
}

