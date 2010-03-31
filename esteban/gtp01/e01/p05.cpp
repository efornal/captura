/*
  => total = 7554 bytes
  FIXME: la imagen tiene 7654 (sobran 100 bytes, de donde?!)
  7654 mar 18 20:43 recuadro.bmp
*/

#include "CImg.h"
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    
    CImg<unsigned char> img("../../imagenes/huang2_corrida.tif");
    CImgDisplay ventana( img, "Original", 0 );
    CImg<unsigned char> recuadro = img.get_crop(100,40,149,89);
    CImgDisplay ventana2( recuadro, "Recuadro", 0 );

    recuadro.get_stats(); // que hace?
    recuadro.print();

    recuadro.save_bmp("recuadro.bmp");

recuadro

    while( !ventana.is_closed() && !ventana.is_keyQ() ){} 
    
    return 0;
}
