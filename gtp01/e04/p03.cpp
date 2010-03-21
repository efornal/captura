/**
   FIXME:
     1. porque no funciona con  cimg_forX( img1, x ) img1.fillY() 
     //deja franja gris
     y si con cimg_forXY !!??
     2. que sentido tiene con 0101..binaria, no se ve la diferencia
     entre el negro 0 y el negro 1.

*/
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    int normalizacion = 1; //0-255
    CImg<unsigned char> img1(100,100,1,1);
    img1.fill(255); //fondo blanco
    CImgDisplay disp;

    // cimg_forX( img1, x ) { // otra forma de cimg_forXY
    //     img1.fillY( x, 0, 0, x%2 );
    //     //sleep(1);
    //     //img1.display(disp);
    // }
    cimg_forXY(img1,x,y){
        img1(x,y) = x%2; // *255 para diferenciar
    }

    img1.display(disp);
    //    Cimgdisplay disp( img1, "Tono de grises 0-100", normalizacion );

    while ( !disp.is_closed() && !disp.is_closed() ) {}
    return 0;
}
