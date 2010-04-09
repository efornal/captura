/**
   FIXME: completar, esto solo prueba inicial,..
*/
#include <CHImg.h>
#include <iostream>
#include <lut.h>


using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/earth.bmp", 
                                        "ruta archivo imagen" );

    CHImg<unsigned char> img( filename );
    CImgDisplay disp;

    img.display(disp);
    lut_x_tramo(img,0,10).display();
    mapeo_x_tramo(0,10).display();
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ){
    }        
    return 0;
}
