#include <CHImg.h>
#include <math.h>

using namespace cimg_library;
using namespace std;

int distancia (int x0, int y0, int c0, int x1, int y1, int c1){
    int x=(x0-x1), y(y0-y1), c=(c0-c1);
    return sqrt(x*x + y*y + c*c);
}

CImg<unsigned char> gen_mascara_segmentacion( CImg<unsigned char> img, 
                                              int x0, int y0,
                                              int radio ){
    CImg<unsigned char> mask ( img.width(), img.height(), 1, 1, 0 );
    cimg_forXY( img,x,y){
        mask(x,y,0,0) = ( distancia (img(x0,y0,0,0),
                                     img(x0,y0,0,1),
                                     img(x0,y0,0,2),
                                     img(x,y,0,0),
                                     img(x,y,0,1),
                                     img(x,y,0,2) ) > radio ) ? 0 : 1; 
    }
    return mask;
}


int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/futbol.jpg", 
                                        "ruta archivo imagen" );
    int radio = cimg_option( "-r", 10, "radio de  tolerancia");

    CImg<unsigned char> img ( filename ), 
        img_r( img.width(), img.height(), 1, 3, 0 ),
        img_g( img.width(), img.height(), 1, 3, 0 ),
        img_b( img.width(), img.height(), 1, 3, 0 ),
        mask_r( img.width(), img.height(), 1, 3, 0 ),
        mask_g( img.width(), img.height(), 1, 3, 0 ),
        mask_b( img.width(), img.height(), 1, 3, 0 );

    CImgDisplay disp, disp2, disp3, disp4;
    //struct punto punto_selec = { 90, 100, 80};
    int x0=90, y0=100;

    img.display(disp);
    disp.set_title("original");

    //separacion de canales
    cimg_forXY(img,x,y){
        img_r(x,y,0,0) = img(x,y,0,0);
        img_g(x,y,0,1) = img(x,y,0,1);
        img_b(x,y,0,2) = img(x,y,0,2);
    }

    // lista canales rgb 
    CImgList<unsigned char> rgb ( img_r.resize(200,200).normalize(0,255),
                                  img_g.resize(200,200).normalize(0,255),
                                  img_b.resize(200,200).normalize(0,255) );
    rgb.display(disp3);
    disp3.set_title("canales RGB");

    CImg<unsigned char> mask = gen_mascara_segmentacion(img,x0,y0,radio);
    mask.normalize(0,255).display();

    cimg_forXY(img,x,y){
        img(x,y,0,0) *= mask(x,y);
        img(x,y,0,1) *= mask(x,y);
        img(x,y,0,2) *= mask(x,y);
    }
    img.display("mascarada");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

    }
    return 0;
}
