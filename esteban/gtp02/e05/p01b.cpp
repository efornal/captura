/**
   FIXME: para encontrar los opuestos:
     si tomamos 100
     inicial es 100
     255-100 =  155
     el opuesto de 100 es 155

   - los opuestos no tienen mucha relacion entre si, simplemente muestra:
     0 => p < 100    1 => p > 100
     0 => p < 155    1 => p > 155
*/
#include <CImg.h>
#include <artisticos.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    CImg<unsigned char> img1( filename1 );
    
    CImgDisplay disp, disp2, disp3;

    img1.display(disp);

    img1.get_threshold(155).normalize(0,255).display( disp2 );
    img1.get_threshold(100).normalize(0,255).display( disp3 );

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
