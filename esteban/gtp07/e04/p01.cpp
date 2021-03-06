/**
 * ./p01 -x0 260 -y0 170 -r 50
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/rosas.jpg",
                                         "ruta archivo imagen" );
    int x0     = cimg_option ( "-x0" ,   150, "valor x inicial" );
    int y0     = cimg_option ( "-y0" ,   135, "valor y inicial" );
    int radio  = cimg_option( "-r", 50, "radio de  tolerancia");

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CImg<double> img( filename );
    
    img.display(disp);
    disp.set_title("original");
                            
    CImg<unsigned char> mask = gen_mascara_segmentacion_rgb( img, x0, y0, radio );

    mask.normalize(0,255).display(disp2);
    disp2.set_title("mascara segmentada RGB");

    img.display();
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
