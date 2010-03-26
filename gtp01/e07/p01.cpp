#include <CImg.h>
//#include <unistd.h>

using namespace std;
using namespace cimg_library;

CImg<unsigned char> to_medio_tono( CImg<unsigned char> img, int x, int y ){

}

void pintar( CImg<unsigned char> &cuadro,int tipo ){
    switch(tipo){
    case 1:
        cuadro(0,1) = 255;
    case 2:
        cuadro(0,1) = 255;
        cuadro(2,2) = 255;
    case 3:
        cuadro(0,0) = 255;
        cuadro(0,1) = 255;
        cuadro(2,2) = 255;
    case 4:
        cuadro(0,0) = 255;
        cuadro(0,1) = 255;
        cuadro(2,2) = 255;
        cuadro(2,0) = 255;
    case 5:
        cimg_for_insideXY( cuadro, x, y, 1) { cuadro(x,y) = 255; }
        cuadro(1,0) = 0;
        cuadro(1,1) = 0;
        cuadro(1,2) = 0;
        cuadro(2,1) = 0;
    case 6:
        cimg_for_insideXY( cuadro, x, y, 1) { cuadro(x,y) = 255; }
        cuadro(1,0) = 0;
        cuadro(1,1) = 0;
        cuadro(2,1) = 0;
    case 7:
        cimg_for_insideXY( cuadro, x, y, 1) { cuadro(x,y) = 255; }
        cuadro(1,0) = 0;
        cuadro(1,1) = 0;
    case 8:
        cimg_for_insideXY( cuadro, x, y, 1) { cuadro(x,y) = 255; }
        cuadro(1,1) = 0;
    case 9:
        cimg_for_insideXY( cuadro, x, y, 1) { cuadro(x,y) = 255; }
    }
}

CImg<unsigned char> tono( int valor ){
    CImg<unsigned char> cuadro( 3, 3, 1, 1, 0 );
    int parte = 255/10;
    if( valor < parte) {
        pintar(cuadro,0); 
    } else if( valor < 2*parte) {
        pintar(cuadro,1); 
    } else if( valor < 3*parte) {
        pintar(cuadro,2); 
    } else if( valor < 4*parte) {
        pintar(cuadro,3); 
    } else if( valor < 5*parte) {
        pintar(cuadro,4); 
    } else if( valor < 6*parte) {
        pintar(cuadro,5); 
    } else if( valor < 7*parte) {
        pintar(cuadro,6); 
    } else if( valor < 8*parte) {
        pintar(cuadro,7); 
    } else if( valor < 9*parte) {
        pintar(cuadro,8); 
    }
    return cuadro;
}


int main( int argc, char **argv ) {

    CImg<unsigned char> img1( "../../imagenes/clown.jpg" );
    CImg<unsigned char> mediotono( 3*img1.width(), 3*img1.height(), 1, 1 );
    CImgDisplay disp, disp2;

    img1.display(disp);

    cimg_for_insideXY( img1, x, y, 1 ) {
        CImg<unsigned char> cuadro = tono(img1(x,y));
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


    mediotono.display(disp2);
    mediotono.save("mediotono.jpg");

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
