/*
  FIXME:
  - porque  cout << img1(100,100) << endl; no muestra el valor 255
*/

#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {

    CImg<unsigned char> img1(400,200,1,1);

    cout << "valor(100,100) = " << img1(100,100) << endl;
    
    img1(100,100) = 255;

    cout << "valor(100,100) = " << img1(100,100) << endl;
    cout << img1(100,100) << endl;
    img1.display("Imagen de intensidad");

    return 0;
}
