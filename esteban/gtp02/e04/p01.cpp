/**
   FIXME: cuando es con relieve interno y cuando externo?
*/
#include <CImg.h>
#include <artisticos.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    const int dx = cimg_option( "-dx", 1, "traslado repujado en direccion de x" );
    const int dy = cimg_option( "-dy", 1, "traslado repujado en direccion de y" );

    CImg<unsigned char> img1( filename1 );
    
    CImgDisplay disp, disp2, disp3;

    img1.display(disp);
    repujado(img1,dx,dy,1).display("relieve interno"); // relieve interno?
    repujado(img1,dx,dy,0).display("relieve externo"); // relieve externo?

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
