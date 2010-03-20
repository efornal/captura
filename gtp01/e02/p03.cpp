/*
  # lista.display(disp2,'x','p');
  \param axis  : The axis used to append the image for visualization. 
    Can be 'x' (default),'y','z' or 'c'.
  \param align : Defines the relative alignment of images when displaying 
    images of different sizes.
    Can be '\p c' (centered, which is the default), 
    '\p p' (top alignment) and 
    '\p n' (bottom aligment).
*/

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

    CImgDisplay disp1;
    lista.display(disp1,'x','p');
    while( !disp1.is_closed() && !disp1.is_keyQ() ){} 

    CImgDisplay disp2;
    lista.display(disp2,'y','p');
    while( !disp2.is_closed() && !disp2.is_keyQ() ){} 

    CImgDisplay disp3;
    lista.display(disp3,'z','p');
    while( !disp3.is_closed() && !disp3.is_keyQ() ){} 

    CImgDisplay disp4;
    lista.display(disp4,'c','p');
    while( !disp4.is_closed() && !disp4.is_keyQ() ){} 

    CImgDisplay disp5;
    lista.display(disp5,'x','n');
    while( !disp5.is_closed() && !disp5.is_keyQ() ){} 

    CImgDisplay disp6;
    lista.display(disp6,'x','c');
    while( !disp6.is_closed() && !disp6.is_keyQ() ){} 

    return 0;
}
