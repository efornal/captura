#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

CImg<unsigned char> lut( CImg<unsigned char> img1, int factor ) {

    CImg<unsigned char> img2(img1.width(),img1.height(),1,1);
    cimg_forXY( img1, x, y ) {
        //el uno es para no hacer log(0)
        img2(x,y) =  log(1 + img1(x,y) ) * factor;
        if ( (img2(x,y)) > 255 ) img2(x,y) = 255;
        if ( (img2(x,y)) < 1   ) img2(x,y) = 0;
    }
    return img2; 
}

int main() {
    int factor = 5;
    unsigned char rojo[] = {255,0,0};
    CImg<unsigned char> mapeo(255,1,1,1);
    CImg<unsigned char> mapeo_disp(255,255,1,1);
    CImg<unsigned char> img1("../../imagenes/orion.jpg");
    CImgDisplay disp, disp2;

    img1.channel(1);

    cimg_forX(mapeo,x){
        mapeo(x) = log(x) * factor;
    }

    CImg<unsigned char> img2 = lut( img1, factor );

    img1.display(disp);
    img2.display(disp2);
    

    mapeo_disp.draw_graph( mapeo, rojo, 1, 1, 1 , 255, 0 ).display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
