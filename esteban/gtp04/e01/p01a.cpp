#include <CImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename );
    CImg<double> img_r(img.width(),img.height(),1,3,0);
    CImg<double> img_g(img.width(),img.height(),1,3,0);
    CImg<double> img_b(img.width(),img.height(),1,3,0);
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp); 
    img.print();
    cimg_forXY(img,x,y){
        img_r(x,y,0,0) = img(x,y,0,0);
        img_g(x,y,0,1) = img(x,y,0,1);
        img_b(x,y,0,2) = img(x,y,0,2);
    }

    img_r.display( disp2 );
     disp2.set_title("rojo");

     img_g.display( disp3 );
     disp3.set_title("verde");

    img_b.display( disp4 );
    disp4.set_title("azul");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
