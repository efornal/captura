#include <CImg.h>

using namespace cimg_captura;

int main( int argc, char **argv ) {

    CImg<unsigned char> img("../../../imagenes/tablero.png");
    img.display("this is a test");

    CImg<unsigned char> img2(200,200,1,1,255);
    img2.display("this is a test");

    return 0;
}
