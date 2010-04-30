/**
   para visualizar el modulo:
   log{ sqrt(r^2 + i^2) + eps }   eps=numero muy chico
*/
#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;


int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );
    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    unsigned char color[] = {255,255,255};

    CHImg<double> lineav (512,512,1,1 );

    lineav.draw_line(255,0,255,512,color);

    CHImg<double> lineav_rotada ( lineav );
    lineav.get_fft_modulo(true).normalize(0,255).display();
    lineav_rotada.rotate(20); // rota 20 grados
    lineav_rotada.crop( 200, 200, 455, 455);
    lineav_rotada.print("linea v rotada");

    lineav.crop(200, 200, 455, 455);
    lineav.print("linea v");

     CImgList<double> list1( lineav, 
                             lineav.get_fft_modulo(true).normalize(0,255) );
     CImgList<double> list2( lineav_rotada, 
                             lineav_rotada.get_fft_modulo(true).normalize(0,255) );

     list1.display(disp);
     list2.display(disp2);

    disp.set_title("linea v");
    disp2.set_title("linea v rotada 20grad");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
