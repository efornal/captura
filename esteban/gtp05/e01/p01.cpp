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
    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    unsigned char color[] = {255,255,255};

    CHImg<double> punto (300,300,1,1 );
    CHImg<double> circulo (300,300,1,1 );
    CHImg<double> cuadrado (300,300,1,1 );
    CHImg<double> linea_h (300,300,1,1 );
    CHImg<double> linea_v (300,300,1,1 );

    punto.draw_point(150,150,color);
    circulo.draw_circle(150,150,10,color);
    cuadrado.draw_rectangle(145,145,155,155,color);
    linea_h.draw_line(0,150,300,150,color);
    linea_v.draw_line(150,0,150,300,color);

    CImgList<double> list1( punto, 
                            punto.get_fft_modulo(false).normalize(0,255),
                            punto.get_fft_modulo(true).normalize(0,255) );
    CImgList<double> list2( circulo, 
                            circulo.get_fft_modulo(false).normalize(0,255),
                            circulo.get_fft_modulo(true).normalize(0,255) );
    CImgList<double> list3( cuadrado, 
                            cuadrado.get_fft_modulo(false).normalize(0,255) ,
                            cuadrado.get_fft_modulo(true).normalize(0,255) );
    CImgList<double> list4( linea_h, 
                            linea_h.get_fft_modulo(false).normalize(0,255),
                            linea_h.get_fft_modulo(true).normalize(0,255) );
    CImgList<double> list5( linea_v, 
                            linea_v.get_fft_modulo(false).normalize(0,255),
                            linea_v.get_fft_modulo(true).normalize(0,255) );

    list1.display(disp);
    list2.display(disp2);
    list3.display(disp3);
    list4.display(disp4);
    list5.display(disp5);

    disp.set_title("punto - fft - centrada");
    disp2.set_title("circulo - fft - centrada");
    disp3.set_title("cuadrado - fft - centrada");
    disp4.set_title("linea horizontal - fft - centrada");
    disp5.set_title("linea vertical - fft - centrada");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
