#include <CHImg.h>
#include <imagenes.h>
#include<iostream>

using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    //CImg<unsigned char> img1 = tonos_de_gris( 255 );
    CHImg<unsigned char> img1( filename );
    CImg<unsigned char> planos[8];
    
    CImgDisplay disp( img1, "planos de bit - descomposicion 0->7" , 1 );

    for ( int i=0; i<8; i++ ) {
        planos[i] = img1.get_plano_de_bit( i ) ;
    }

    int plano = 0;
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ){
        disp.wait();
        
        if (  disp.is_keyARROWDOWN() ) {
            if ( plano > 0 ) plano--;
            planos[plano].display(disp);
            cout << "plano: " << plano 
                 << "   MSE(Err. Cuad. Medio): " << planos[plano].MSE(img1) << endl;
    
        }
        if (  disp.is_keyARROWUP() ) {
            if ( plano < 7 ) plano++;
            planos[plano].display(disp);
            cout << "plano: " << plano 
                 << "   MSE(Err. Cuad. Medio): " << planos[plano].MSE(img1) << endl;
        }
    }
    return 0;
}
