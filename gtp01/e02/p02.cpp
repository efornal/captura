/*
  # CImgDisplay
     
  # Cimg&display()
    - Segun donde se posicione el mouse, muestra, para ese pixel:
        la posicion (x,y)
        el valor de color de cada canal que tenga la imagen
    - Permite hacer zoom sobre la imagen
    - Realiza un print() en consola
*/
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    CImg<unsigned char> img("../../imagenes/earth.bmp");
    CImgDisplay vimg( img, "imagen con CImgDisplay", 0 );

    img.display("imagen con img.display()");
    
    while( !vimg.is_closed() && !vimg.is_keyQ() ){} 
    
    return 0;
}
