#include <CImg.h>
#include <stdio.h>
#include <medios_tonos.h>

using namespace std;
using namespace cimg_library;

int main( int argc, char **argv ) {

    CImgDisplay disp1, disp2, disp3;

    CImg<unsigned char> img1("../../imagenes/huang1.jpg");
    CImg<unsigned char> img2("../../imagenes/huang2.jpg");
    CImg<unsigned char> img3("../../imagenes/huang3.jpg");

    img1.display(disp1);
    img2.display(disp2);
    img3.display(disp3);
    
    to_medio_tono( img1 ).display();
    to_medio_tono( img2 ).display();       
    to_medio_tono( img3 ).display();

    return 0;
}
