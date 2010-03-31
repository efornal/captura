/*
  calculo bmp: 50x50 = 2500 pixels
  1 pixcel = 1 byte (por ser tipo char)
  => 2500 pixels = 2500 bytes
  dado RGB 3 dimensiones
  => 2500 * 3 = 7500 
  mas 54 bytes de cabecera:
  => total = 7554 bytes
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

    while( !ventana.is_closed() && !ventana.is_keyQ() ){} 
    
    return 0;
}
