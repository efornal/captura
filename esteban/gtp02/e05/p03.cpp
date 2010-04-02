#include <CImg.h>
#include <operadores_relacionales.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f1", "../../../imagenes/letras1.tif", 
                                        "ruta archivo imagen" );
    const char *filename2 = cimg_option( "-f2", "../../../imagenes/letras2.tif", 
                                        "ruta archivo imagen" );

    CImg<unsigned char> img1( filename1 );
    CImg<unsigned char> img2( filename2 );
    CImgDisplay disp, disp2, disp3;

    img1.display(disp);
    img2.display(disp2);
    menor(img1,img2).display("img1 Menor img2");
    menor(img2,img1).display("img2 Menor img1");
    mayor(img1,img2).display("img1 Menor img2");
    mayor(img2,img1).display("img2 Menor img1");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
