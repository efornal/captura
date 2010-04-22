#include <CImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename );
    CImg<double> img_h(img.width(),img.height(),1,3,0);
    CImg<double> img_s(img.width(),img.height(),1,3,0);
    CImg<double> img_i(img.width(),img.height(),1,3,0);
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp); 
    img.print();
    img.RGBtoHSI();
    cimg_forXY(img,x,y){
        img_h(x,y,0,0) = img(x,y,0,0);
        img_s(x,y,0,1) = img(x,y,0,1);
        img_i(x,y,0,2) = img(x,y,0,2);
    }

    img_h.display( disp2 );
     disp2.set_title("h");

     img_s.display( disp3 );
     disp3.set_title("s");

    img_i.display( disp4 );
    disp4.set_title("i");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
