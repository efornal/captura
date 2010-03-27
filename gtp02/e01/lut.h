#include <CImg.h>

using namespace cimg_library;

CImg<unsigned char> lut( CImg<unsigned char> img1, int a=1, int c=0 ) {

    CImg<unsigned char> img2( img1.width(), img1.height(), 1, 1 );
    cimg_forXY( img1, x, y ) {
        img2(x,y) =  a*img1(x,y) + c;
        if ( (a*img1(x,y) + c) > 255 ) img2(x,y) = 255; // clipping
        if ( (a*img1(x,y) + c) < 1   ) img2(x,y) = 0; // clipping
    }
    return img2; 
}

void ver_mapeo( int a, int c ){
    unsigned char rojo[] = {255,0,0};
    CImg<unsigned char> mapeo(255,1,1,1,0);
    CImg<unsigned char> mapeo_disp(255,255,1,1,0);
    cimg_forX( mapeo, x ){ mapeo(x) = x; }

    CImg<unsigned char> mapeado = lut( mapeo, a, c );

    mapeo_disp.draw_graph( mapeado, rojo, 1, 1, 1 , 255, 0 ).display();

}
