#define UNICODE
#include <CImg.h>

using namespace cimg_library;

int main(int argc, char *argv[]) {
  cimg_usage("Ejercicio 1");

  // 1. Cargar la imagen
  CImg<unsigned char> imagen("../img/huang2.jpg");

  // 2. Visualizarla
  imagen.display();

  // 3. Generar subimagen y visualizarla

  CImg<unsigned char> subimg = imagen.get_crop(60,20,0,180,120,0);
  subimg.display();

  // 4. Ver el output cuando se crea la ventana; o bienteniendo en cuenta que ser'ia
  //    (ancho)*(alto)*(bytes del tipo de dato)*(nro. canales)
  //    por ej. 120*100*1*1+54=12054 bytes

  // 5. Guardo como BMP
  subimg.save("subimagen.bmp");

  return 0;
}
