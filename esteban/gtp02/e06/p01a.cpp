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
#include <CHImg.h>
#include <imagenes.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    
    CHImg<unsigned char> img1 = tonos_de_gris( 255 );
    //    CImg<unsigned char> img1 ( filename );
    
    CImgDisplay disp  ( img1.get_plano_de_bit( 0 ), "plano 0", 1 );
    CImgDisplay disp1 ( img1.get_plano_de_bit( 1 ), "plano 1", 1 );
    CImgDisplay disp2 ( img1.get_plano_de_bit( 2 ), "plano 2", 1 );
    CImgDisplay disp3 ( img1.get_plano_de_bit( 3 ), "plano 3", 1 );
    CImgDisplay disp4 ( img1.get_plano_de_bit( 4 ), "plano 4", 1 );
    CImgDisplay disp5 ( img1.get_plano_de_bit( 5 ), "plano 5", 1 );
    CImgDisplay disp6 ( img1.get_plano_de_bit( 6 ), "plano 6", 1 );
    CImgDisplay disp7 ( img1.get_plano_de_bit( 7 ), "plano 7", 1 );

    img1.display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
