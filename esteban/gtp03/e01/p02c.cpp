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
   *   los valores estan concentrados en una zona (FIXME: o es por lo elevado?)
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
   *    claros y oscuros (MAL?, rpta: oscuros,bajo contraste)
   *    bajo contraste: valores dispersos 
   *
   * - imagenE
   *        |
   *        |.||....
   *    oscuros 
   *    alto contraste
   *
   *  FIXME: estan bien las inferencias? 
*/

#include <CImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {

    CImg<unsigned char> img1 ( "../../../imagenes/imagenA.tif" ) ,
        img2 ( "../../../imagenes/imagenE.tif" );

    CImgDisplay disp( img1 ,"imagenA" ), 
        disp2( img2 ,"imagenE" ), disp3, disp4;

    img1.get_histogram(256,0,255).display_graph(disp3, 3);
    img2.get_histogram(256,0,255).display_graph(disp4, 3);

    disp3.set_title("imagenA");
    disp4.set_title("imagenE");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
