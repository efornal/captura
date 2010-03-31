/**
  FIXME: 
  1. la opcion de despliegue en 255 se realiza con:
  CImgDisplay disp( img1, "Tono de grises 0-100", normalizacion );
  con normalizacion = 1 ??
  2. no se puede setear el intervalo de normalizacion? 0-100 por ej.??
  3. No se nota la diferencia entre el blanco de 255 y el de 100. porque?
     para ver esto correr p01(255) y p02(100) a la vez.
*/

#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    int normalizacion = 1; //0-255
    CImg<unsigned char> img1(100,100,1,1);

    cimg_forXY( img1, x, y ) {
        img1(x,y) = x;
    } 

    CImgDisplay disp( img1, "Tono de grises 0-100", normalizacion );

    cout << "narmalización: " << disp.normalization() << endl;
    img1.display();
    while ( !disp.is_closed() && !disp.is_closed() ) {}

    return 0;
}
