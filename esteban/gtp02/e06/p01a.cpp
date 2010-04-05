/**
   Con la imagen en escala de grises se aprecia como interpreta los bits:
   dec  | bin
   0    | 0000 0000
   1    | 0000 0001
   ...  | 0...
   127  | 0111 1111
   ----------------
   128  | 1000 0000
   ...  | 1...
   255  | 1111 1111
   ________________
   pos  : 7654 3210
   
   para la posicion 7 (bit7) - ver en tabla a lo vertical
      de 0-127 son todos ceros
      de 128-255 son todos unos
   por tanto la imagen correspondiente a este plano es una
   mitad blanca mitad negra. y asi con el resto.
*/
#include <CImg.h>
#include <plano_bit.h>
#include <imagenes.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    
    CImg<unsigned char> img1 = tonos_de_gris( 255 );
    //    CImg<unsigned char> img1 ( filename );
    
    CImgDisplay disp  ( plano_de_bit( img1, 0 ), "plano 0", 1 );
    CImgDisplay disp1 ( plano_de_bit( img1, 1 ), "plano 1", 1 );
    CImgDisplay disp2 ( plano_de_bit( img1, 2 ), "plano 2", 1 );
    CImgDisplay disp3 ( plano_de_bit( img1, 3 ), "plano 3", 1 );
    CImgDisplay disp4 ( plano_de_bit( img1, 4 ), "plano 4", 1 );
    CImgDisplay disp5 ( plano_de_bit( img1, 5 ), "plano 5", 1 );
    CImgDisplay disp6 ( plano_de_bit( img1, 6 ), "plano 6", 1 );
    CImgDisplay disp7 ( plano_de_bit( img1, 7 ), "plano 7", 1 );

    img1.display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
