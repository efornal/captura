#include <CImg.h>
#include <lut.h>

using namespace cimg_library;

int main() {

    CImg<unsigned char> img1("../../imagenes/orion.jpg");

    CImgDisplay disp,disp2;

    img1.channel(1);

    CImg<unsigned char> img2 = lut(img1);

    img1.display(disp);
    img2.display(disp2);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
