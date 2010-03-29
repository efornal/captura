#include <CImg.h>
#include <operaciones.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f", "../../imagenes/letras2.tif", 
                                        "ruta archivo imagen 1" );
    int x0 = 80,  y0 = 20;
    int x1 = 200, y1 = 100;
    int z0 = 0, c0 = 0, z1 = 0, c1 = 0;
    CImg<unsigned char> img1( filename1 );
    unsigned char color_mask[] = {1,1,1};
    CImg<unsigned char> mascara( img1.width(), img1.height(), 1, 1, 0 ); // con 0
    mascara.draw_rectangle ( x0, y0,  x1,  y1,  color_mask ); // recuadro con 1

    CImgDisplay disp, disp2, disp3;

    img1.display(disp);
    mascara.display(disp2);
    enmascarar(img1,mascara).display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
