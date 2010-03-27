/** 
    FIXME: el mapeo por tramos no se ve como deberia ser , porque?
    NOTA:
      modificar la funcion de lut para que en determinados tramos sea
      constante, por ejemplo 
      if (img1(x,y)) esta entre 40 y 90, asignar valor constante 100
      si esta en otro rango, asignar una recta con otra pendiente, y a asi..
         __/
      --/
**/
#include <CImg.h>
#include <lut.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", 
                                        "../../imagenes/earth.bmp", 
                                        "ruta archivo imagen" );
    CImg<unsigned char> img1( filename );
    CImgDisplay disp, disp2, disp3;
    int x1 = 100, x2 = 200;
    CImg<unsigned char> img2 = lut_x_tramo( img1, x1, x2 );

    img1.display(disp);
    img2.display(disp2);
    
    mapeo_x_tramo( x1, x2 ).display(disp3);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
