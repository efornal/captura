/**
   * Caractiristicas generales en histograma:
   * - imagen con poco brillo:
   *       |    
   *       |||____
   *   se consentra en los valores bajos.
   *
   * - imagen con mucho brillo:
   *       |    
   *       |____||
   *   se consentra en los valores altos.
   *
   * - imagen con bajo contraste:
   *       |    
   *       |__||__
   *   los valores estan concentrados en una zona
   *
   * - imagen con alto contraste:
   *       |    
   *       |_...._
   *   los valores estan dispersados
   *
   * Sobre los archivos (inferencias):
   * - histo1
   *    claros y oscuros
   *    alto contraste: valores dispersos
   * - histo2
   *    parte media-baja: mayoria de oscuros-grises
   *    bajo contraste
   * - histo3
   *    oscura
   *    bajo contraste
   * - histo4
   *   clara
   *   alto contraste
   * - histo5
   *   grises y claros
   *   contraste medio
   *
   * FIXME: cuales son las respuestas correctas, a q imagenes corresponen?
*/

#include <CImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {

    CImg<unsigned char> img1 ( "../../../imagenes/histo1.tif" ) ,
        img2 ( "../../../imagenes/histo2.tif" ),
        img3 ( "../../../imagenes/histo3.tif" ),
        img4 ( "../../../imagenes/histo4.tif" ),
        img5 ( "../../../imagenes/histo5.tif" );

    CImgDisplay disp( img1 ,"histo1" ), 
        disp2( img2 ,"histo2" ),
        disp3( img3 ,"histo3" ), 
        disp4( img4 ,"histo4" ),
        disp5( img5 ,"histo5" );

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
