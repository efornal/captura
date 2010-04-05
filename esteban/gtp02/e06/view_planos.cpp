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
    const char *filename = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    CImgDisplay disp;
    //    CImg<unsigned char> img1 = tonos_de_gris( 255 );
    CImg<unsigned char> img1( filename );
    CImg<unsigned char> result;
    CImg<unsigned char> planos[8];
    
    for ( int i=0;i<8;i++){
        planos[i] = plano_de_bit( img1, i ) ;
    }
    int cont = 7;
    result = planos[7]*;
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
        
        if (  disp.is_keyARROWDOWN() ) {
            result +=

    (plano6*64+plano7*128).display("Con plano 7");
    (plano6*64+plano7*128).display("Con plano 7");
    (plano6*64+plano7*128).display("Con plano 7");
    (plano6*64+plano7*128).display("Con plano 7");
    (plano6*64+plano7*128).display("Con plano 7");


        }
    }
    return 0;
}
