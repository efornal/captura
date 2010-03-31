#include <CImg.h>

using namespace cimg_library;

CImg<unsigned char> lut( CImg<unsigned char> img1, int a=1, int c=0 ) {

    CImg<unsigned char> img2( img1.width(), img1.height(), 1, 1 );
    cimg_forXY( img1, x, y ) {
        img2(x,y) =  a*img1(x,y) + c;
        if ( img2(x,y) > 255 ) img2(x,y) = 255; // clipping
        if ( img2(x,y) < 1   ) img2(x,y) = 0; // clipping
    }
    return img2; 
}

/**
   s=r*factor en el rango x1 <= x <= x2
*/
CImg<unsigned char> lut_x_tramo( CImg<unsigned char> img1, int x1, int x2 ) {
    int factor = 2;
    CImg<unsigned char> img2( img1.width(), img1.height(), 1, 1, 0 );
    cimg_forXY( img1, x, y ) {
        if ( x < x1 || x > x2 ) img2(x,y) =  img1(x,y);
        if ( x >= x1 && x <= x2 ) img2(x,y) =  img1(x,y)*factor;

        if ( img2(x,y) > 255 ) img2(x,y) = 255; // clipping
        if ( img2(x,y) < 1   ) img2(x,y) = 0; // clipping
    }
    return img2; 
}

CImg<unsigned char> mapeo_x_tramo( int x1, int x2 ){
    unsigned char rojo[] = {255,0,0};
    CImg<unsigned char> mapeo(255,1,1,1,0);
    CImg<unsigned char> mapeo_disp(255,255,1,1,0);

    cimg_forX( mapeo, x ){ mapeo(x) = x; }

    CImg<unsigned char> mapeado = lut_x_tramo( mapeo, x1, x2 );

    return mapeo_disp.draw_graph( mapeado, rojo, 1, 1, 1 , 255, 0 );

}

CImg<unsigned char> mapeo( int a, int c ){
    unsigned char rojo[] = {255,0,0};
    CImg<unsigned char> mapeo(255,1,1,1,0);
    CImg<unsigned char> mapeo_disp(255,255,1,1,0);

    cimg_forX( mapeo, x ){ mapeo(x) = x; }

    CImg<unsigned char> mapeado = lut( mapeo, a, c );

    return mapeo_disp.draw_graph( mapeado, rojo, 1, 1, 1 , 255, 0 );

}

void ver_mapeo( int a, int c ){
    mapeo( a, c ).display();
}
