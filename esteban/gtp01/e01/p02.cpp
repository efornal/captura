#include "CImg.h"
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    
    CImg<unsigned char> img("../../imagenes/huang2_corrida.tif");
    CImgDisplay ventana( img, "Imagen", 0 );
    while( !ventana.is_closed() && !ventana.is_keyQ() ){} 

    return 0;
}
