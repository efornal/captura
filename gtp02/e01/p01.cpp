#include <CImg.h>
#include <iostream>
//include <lut.h>

using namespace cimg_library;
using namespace std;

int main() {

    int a = 2, c = 0;

    CImg<unsigned char> img1("../../imagenes/orion.jpg");
    CImg<unsigned char> img2(img1.width(),img1.height(),1,1);
    CImgDisplay disp,disp2;

    img1.channel(1);

    cimg_forXY(img1,x,y){
        img2(x,y) =  a*img1(x,y) + c;
    }

    img1.display(disp);
    img2.display(disp2);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
