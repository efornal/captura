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
  cimg_forXY( kernel, x, y ) {
    kernel(x,y) = exp(-pow(x-1,2)-pow(y-1,2));
  }

  CImg<double> imagen( argv[1] );

  CImgList<double> result ( imagen.normalize(0,255), kernel.normalize(0,255), imagen.get_convolve( kernel ).normalize(0,255) );

  CImgDisplay d_imgs, d_hist;


  result.display( );
  
  // while ( !d_imgs.is_closed() && !d_hist.is_closed() ) {
  //   d_imgs.wait_all();
  // }
  return 0;
}

