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
    //    CImgDisplay disp, disp2;
    //CImg<unsigned char> img1 = tonos_de_gris( 255 );
    CImg<unsigned char> img1( filename );
    CImg<unsigned char> result;
    CImg<unsigned char> planos[8];
    
    CImgDisplay disp( img1, "planos de bit - descomposicion 0->7" , 1 );

    sleep(1);
    for ( int i=0;i<8;i++){
        planos[i] = plano_de_bit( img1, i ) ;
        planos[i].display(disp);
        sleep(2);
    }


    result = planos[7]*pow(2,7);
    result.display(disp);
    CImgDisplay disp2( result, "planos de bit - composicion 7->0" , 1 );
    sleep(5); 
    for ( int i=6;i>=0;i--){
        result = result + planos[i]*pow(2,i);
        result.display(disp2);
        sleep(2);
    }

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
