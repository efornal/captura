#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename );
    CImgDisplay disp, disp2, disp3, disp4;
    unsigned char rojo[] = {255,0,0};
    unsigned char verde[] = {0,255,0};
    unsigned char azul[] = {0,0,255};
    img.display(disp);
    img.draw_graph( img.get_channel(0), rojo, 1, 1, 1 , 0, 255 ).display(disp4);
    img.draw_graph( img.get_channel(0), rojo, 1, 1, 1 , 0, 255 ).display(disp4);
    img.draw_graph( img.get_channel(0), rojo, 1, 1, 1 , 0, 255 ).display(disp4);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
