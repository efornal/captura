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
   * - imagenA
   *        |
   *        |...:::.
   *    claros y oscuros
   *    bajo contraste: valores dispersos
   *
   * - imagenE
   *        |
   *        |.||....
   *    oscuros 
   *    alto contraste
*/

#include <CImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {

    CImg<unsigned char> img1 ( "../../../imagenes/imagenA.tif" ) ,
        img2 ( "../../../imagenes/imagenE.tif" );


    CImgDisplay disp( img1 ,"histo1" ), 
        disp2( img2 ,"histo2" );

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
