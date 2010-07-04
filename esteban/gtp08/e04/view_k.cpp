/**
 * Si tomo un único coeficiente ( coeficientes conservados ) el coeficiente
 * que preserva es el primero, posicion coef(0,0) = coef. DC 
 * (el gris medio o promedio), por lo tanto el bloque completo tiene una
 * única tonalidad luego en la descompresion?
*/
#include <CImg.h>
#include <compresion.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char** argv) {

  cimg_usage("Compresión JPEG");
  const char *filename = cimg_option( "-f",
                                        "../../imagenes/hand.tif",
                                         "ruta archivo imagen" );
  const int sizeblock = cimg_option("-s",8,"Tamaño de bloque.");
  int N = cimg_option("-k",24,"Número de coeficientes conservados.");

  CImg<double> img( filename );
  CImgDisplay disp(img,"original"),
    disp2( jpeg( img, sizeblock, N ), "comprimida" );



  while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
    disp.wait_all();

    if ( disp.is_keyARROWDOWN() ){
      jpeg( img, sizeblock, --N ).display(disp2);
      printf("N = %d \n", N);
    }
    if ( disp.is_keyARROWUP() ){
      jpeg( img, sizeblock, ++N ).display(disp2);
      printf("N = %d \n", N);
    }

  }
  return 0;

}
