/**
FIXME: como se escala el nivel de gris de la imagen 
para que ocupe el rango completo de medios tonos?
*/
#include <CImg.h>
#include <iostream>
#include <medios_tonos.h>

using namespace std;
using namespace cimg_library;


int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", 
                                        "../../imagenes/clown.jpg", 
                                        "ruta archivo imagen" );
    const int mostrar = cimg_option( "-p", 1, "mostrar imagen intermedia (!=0)"); 

    CImg<unsigned char> img1( filename );
    CImgDisplay disp, disp2;

    img1.display(disp);

    CImg<unsigned char> mediotono = to_medio_tono_unresized( img1 );

    if ( mostrar != 0 ) mediotono.display(disp2);

    mediotono.resize( (int)(mediotono.width()/3), (int)(mediotono.height()/3) );
    mediotono.display();

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
