/**
   para visualizar el modulo:
   log{ sqrt(r^2 + i^2) + eps }   eps=numero muy chico
*/
#include <CHImg.h>
#include <iostream>
#include <math.h>
#include <CPDSI_functions.h>

using namespace cimg_library;
using namespace std;


int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );
    CImgDisplay disp, disp2, disp3, disp4;
    unsigned char color[] = {255,255,255};

    CImg<double> punto (300,300,1,1 );
    CImg<double> circulo (300,300,1,1 );
    CImg<double> cuadrado (300,300,1,1 );

    punto.draw_circle(150,150,1,color);
    circulo.draw_circle(150,150,10,color);
    cuadrado.draw_rectangle(145,145,155,155,color);

    punto.display(0,0);
    circulo.display(0,0);
    cuadrado.display(0,0);


    CImg<unsigned char> punto_mod;
    magn_tdf( punto, punto_mod );

    CImg<unsigned char> circulo_mod;
    magn_tdf( circulo, circulo_mod );

    CImg<unsigned char> cuadrado_mod;
    magn_tdf( cuadrado, cuadrado_mod );

    punto_mod.display(disp);
    cuadrado_mod.display(disp2);
    circulo_mod.display(disp3);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
