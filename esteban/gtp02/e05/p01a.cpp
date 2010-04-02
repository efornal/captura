/**
   CImg<T>& threshold( T value, 
                       bool soft_threshold = false, 
                       bool strict_threshold = false ) 			

   binariza la imagen segun un valor de umbral, sea valor de umbral=100
   para valores menores a 100 toma 0
   para valores mayores a 100 toma 1
*/
#include <CImg.h>
#include <artisticos.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    CImg<unsigned char> img1( filename1 );
    
    CImgDisplay disp, disp2, disp3;

    img1.display(disp);
    img1.threshold(100).display("threshold ");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
