/*
  FIXME:
  - Hacer el mosquito.stats() antes de print, condiciona el resultado porque
  modifica mosquito, con mosquito.get_stats(); no lo modifica? en q modifica?
  - .stats(); no informa nada?
*/

#include <CImg.h>
#include <iostream>
#include <string>
using namespace cimg_library;
using namespace std;

int main() {
    string nimg1 = "earth.bmp"; 
    string nimg2 = "mosquito.jpg";
    string nimg3 = "imagenA.tif";
    CImg<unsigned char> img1("../../imagenes/earth.bmp");
    CImg<unsigned char> img2("../../imagenes/mosquito.jpg"); //como concateno nimg*??
    CImg<unsigned char> img3("../../imagenes/imagenA.tif");
    CImgDisplay vimg1( img1, "img1", 0 );
    CImgDisplay vimg2( img2, "img2", 0 );
    CImgDisplay vimg3( img3, "img3", 0 );

    cout << "---- " << nimg1 << " ----" << endl;
    img1.get_stats(); //no informa nada?
    img1.print();
    cout << "---- " << nimg2 << " ----" << endl;
    img2.get_stats();
    img2.print();
    cout << "---- " << nimg3 << " ----" << endl;
    img3.get_stats();
    img3.print();

    while( !vimg3.is_closed() && !vimg3.is_keyQ() ){} 
    
    return 0;
}
