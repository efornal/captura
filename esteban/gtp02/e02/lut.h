#include <CImg.h>

using namespace cimg_library;

CImg<unsigned char> lut_log( CImg<unsigned char> img1, int factor ) {

    CImg<unsigned char> img2(img1.width(),img1.height(),1,1);
    cimg_forXY( img1, x, y ) {

        img2(x,y) =  log(1 + img1(x,y) ) * factor;

        if ( (img2(x,y)) > 255 ) img2(x,y) = 255; //clipping
        if ( (img2(x,y)) < 1   ) img2(x,y) = 0; //clipping
    }
    return img2; 
}

CImg<unsigned char> lut_exp( CImg<unsigned char> img1, double factor ) {

    CImg<unsigned char> img2(img1.width(),img1.height(),1,1);
    cimg_forXY( img1, x, y ) {

        img2(x,y) =  pow( img1(x,y), factor );

        if ( (img2(x,y)) > 255 ) img2(x,y) = 255; //clipping
        if ( (img2(x,y)) < 1   ) img2(x,y) = 0; //clipping
    }
    return img2; 
}

CImg<unsigned char> mapeo_log( int factor ){
    unsigned char rojo[] = {255,0,0};
    CImg<unsigned char> mapeo(255,1,1,1,0);
    CImg<unsigned char> mapeo_disp(255,255,1,1,0);

    cimg_forX( mapeo, x ){ mapeo(x) = x; }

    CImg<unsigned char> mapeado = lut_log( mapeo, factor);

    return mapeo_disp.draw_graph( mapeado, rojo, 1, 1, 1 , 255, 0 );

}

CImg<unsigned char> mapeo_exp( double factor ){
    unsigned char rojo[] = {255,0,0};
    CImg<unsigned char> mapeo(255,1,1,1,0);
    CImg<unsigned char> mapeo_disp(255,255,1,1,0);

    cimg_forX( mapeo, x ){ mapeo(x) = x; }

    CImg<unsigned char> mapeado = lut_exp( mapeo, factor);

    return mapeo_disp.draw_graph( mapeado, rojo, 1, 1, 1 , 255, 0 );

}
