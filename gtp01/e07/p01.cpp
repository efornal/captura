#include <CImg.h>
//#include <unistd.h>

using namespace std;
using namespace cimg_library;

CImg<unsigned char> to_medio_tono( CImg<unsigned char> img, int x, int y ){

}

CImg<unsigned char> tono( int valor ){
    CImg<unsigned char> cuadro( 3, 3, 1, 1, 0 );
    cuadro(0,0) = 255;
    cuadro(1,1) = 255;
    cuadro(2,2) = 255;
    return cuadro;
}


int main( int argc, char **argv ) {

    CImg<unsigned char> img1( "../../imagenes/pruebas/pequenia.jpg" );
    CImg<unsigned char> mediotono( 3*img1.width(), 3*img1.height(), 1, 1 );
    CImgDisplay disp, disp2;


    cimg_for_insideXY( img1, x, y, 1 ) {
        CImg<unsigned char> cuadro = tono(2);
        mediotono( 3*x,   3*y )   = cuadro(0,0);
        mediotono( 3*x,   3*y+1 ) = cuadro(0,1);
        mediotono( 3*x,   3*y+2 ) = cuadro(0,2);
        mediotono( 3*x+1, 3*y )   = cuadro(1,0);
        mediotono( 3*x+1, 3*y+1 ) = cuadro(1,1);
        mediotono( 3*x+1, 3*y+2 ) = cuadro(1,2);
        mediotono( 3*x+2, 3*y )   = cuadro(2,0);
        mediotono( 3*x+2, 3*y+1 ) = cuadro(2,1);
        mediotono( 3*x+2, 3*y+2 ) = cuadro(2,2);
        //        mediotono.display(disp2);
    }

    img1.display(disp);
    mediotono.display(disp2);
    mediotono.save("mediotono.jpg");

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
