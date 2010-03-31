/**
   Uniformly quantize values of the instance image into \p nb_levels levels.
     \param nb_levels Number of quantization levels.
     \param keep_range Tells if resulting values keep the same range as the original ones.
*/

#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {

    CImg<unsigned char> img1( "../../imagenes/huang2.jpg" );

    CImgDisplay disp ( img1, "imagen", 1 );

    CImgList<unsigned char> lista ( img1.get_quantize(8), 
                                    img1.get_quantize(7),
                                    img1.get_quantize(6),
                                    img1.get_quantize(5),
                                    img1.get_quantize(4),
                                    img1.get_quantize(3),
                                    img1.get_quantize(2),
                                    img1.get_quantize(1) );
    
    lista.display("Quantizacion 8 niveles (8..1)");

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
