#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    CImg<unsigned char> img ( filename );
    CImgDisplay disp, disp2, disp3, disp4;
    unsigned char rojo[]  = {255,0,0};
    unsigned char verde[] = {0,255,0};
    unsigned char azul[]  = {0,0,255};
    int plot_type=1, vertex_type = 1;
    CImg<unsigned char> grafr( img.width(), 100, 1, 1 ), 
        grafg( img.width(), 100, 1, 1 ), 
        grafb( img.width(), 100, 1, 1 );

    CImg<unsigned char> img_r( img.get_channel(0) );
    CImg<unsigned char> img_g( img.get_channel(1) );
    CImg<unsigned char> img_b( img.get_channel(2) );

    img.display(disp);
    disp.set_title("imagen original");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

        if ( disp.button() && disp.mouse_y() >= 0 ) {
            grafr.fill(0);
            grafg.fill(0);
            grafb.fill(0);

            grafr.draw_graph( img_r.get_crop( 0, 
                                            disp.mouse_y(), 
                                            0, 
                                            0,
                                            img.width()-1,
                                            disp.mouse_y(),
                                            0,
                                            0),
                              rojo, 1, plot_type, vertex_type , 255, 0 );
            grafr.display( disp2 );


            grafg.draw_graph( img_g.get_crop( 0, 
                                            disp.mouse_y(), 
                                            0, 
                                            0,
                                            img.width()-1,
                                            disp.mouse_y(),
                                            0,
                                            0),
                              rojo, 1, plot_type, vertex_type , 255, 0 );
            grafg.display( disp3 );

            grafb.draw_graph( img_b.get_crop( 0, 
                                            disp.mouse_y(), 
                                            0, 
                                            0,
                                            img.width()-1,
                                            disp.mouse_y(),
                                            0,
                                            0),
                              rojo, 1, plot_type, vertex_type , 255, 0 );
            grafb.display( disp4 );

            disp2.set_title("canal rojo");
            disp3.set_title("canal verde");
            disp4.set_title("canal azul");
        }
    }

    return 0;
}
