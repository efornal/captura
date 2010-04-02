/**
   FIXME: porque tengo  que hacer el normalizado antes del display??
     de lo contrario no se ve. porque?
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
    int cont = 0;

    img1.display(disp);
    img1.get_threshold(127).normalize(0,255).display(disp2);
 
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

        if (cont > 127) cont = 127;
        if (cont < -127) cont = -127;

        if (  disp.is_keyARROWDOWN() ) {
            img1.get_threshold((cont--)+127).normalize(0,255).display(disp2);
        } else if (  disp.is_keyARROWUP() ) {
            img1.get_threshold((cont++)+127).normalize(0,255).display(disp2);
        }
    }

    return 0;
}
