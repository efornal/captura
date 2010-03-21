/**
  draw_circle (const int x0, 
    const int y0, 
    int radius, 
    const tc *const color, 
    const float opacity=1)
*/

#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    cimg_usage( "Parametros de recuadro y círculo:" );
    const int dx    = cimg_option( "-dx", 100, "Ancho recuadro" );
    const int dy    = cimg_option( "-dy", 100, "Alto  recuadro" );
    const int radio = cimg_option( "-r", 1, "Radio del círculo" );

    int x = (int)(dx/2);
    int y = (int)(dy/2);
    unsigned char color[] = {255,0,0};
    CImgDisplay disp;
    CImg<unsigned char> img1(dx,dy,1,1);

    img1.draw_circle( x, y, radio, color, 1 );
    img1.display(disp);

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
