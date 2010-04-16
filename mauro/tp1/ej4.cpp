#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;


int main(int argc, char *argv[]) {

  // 1. Genere una matriz de 256x256 cuyas columnas tomen valores de 0 a 255

  CImg<unsigned char> p1(256,256,1,1);
  for (unsigned i=0; i<256; i++)
    p1.draw_line(i,0,i,255,(char*)&i);
  p1.display("Ej 4.1");

  // 2. Genere una matriz de 100x100 cuyas columnas tomen valores de 0 a 100...

  CImg<unsigned char> p2(100,100,1,1);
  for (unsigned i=0; i<100; i++)
    p2.draw_line(i,0,i,99,(char*)&i);
  // ...visualice modificando las ops de despliegue para apreciar un cambio de 0 a 255.
  p2.normalize(0,255).display("Ej 4.2");

  // 3. Genere una matriz de 100x100 cuyas columnas tomen valores intercalados de 0 y 1.
  CImg<bool> p3(100,100,1,1);
  bool color = false;
  for (unsigned i=0; i<100; i++) {
    color = (i%2) ? true: false;
    p3.draw_line(i,0,i,99,&color);
  }
  p3.display("Ej. 4.3");

  return 0;
}

