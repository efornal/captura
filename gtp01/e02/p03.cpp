#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    CImg<unsigned char> img1("../../imagenes/earth.bmp");
    CImg<unsigned char> img2("../../imagenes/mosquito.jpg");
    CImg<unsigned char> img3("../../imagenes/imagenA.tif");

    CImgList<unsigned char> lista(img1,img2,img3);

    lista.print();

    CImgDisplay disp;
    lista.display(disp);
    while( !disp.is_closed() && !disp.is_keyQ() ){} 
    
    return 0;
}
