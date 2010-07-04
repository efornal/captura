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
  const int N = cimg_option("-k",24,"Número de coeficientes conservados.");

  CImg<double> img( filename );
  CImgDisplay disp(img,"original");

  // Si sizeblock = 8 => 64 coeficientes => N ->[1,2,..,64]
  CImgList<double> list1 ( jpeg( img, sizeblock, 1 ),
                           jpeg( img, sizeblock, 5 ),
                           jpeg( img, sizeblock, 10 ),
                           jpeg( img, sizeblock, 20 ) );

  CImgList<double> list2 ( jpeg( img, sizeblock, 30 ),
                           jpeg( img, sizeblock, 40 ),
                           jpeg( img, sizeblock, 50 ),
                           jpeg( img, sizeblock, 60 ),
                           jpeg( img, sizeblock, 64 ) );

  CImgDisplay disp1( list1, "N = 1, 5 , 10 y 20" ),
    disp2( list2, "N = 30, 40 , 50, 60 y 64" );

  list1.display("N = 1, 5 , 10 y 20");
  list2.display("N = 30, 40 , 50, 60 y 64");

  while ( (!disp1.is_closed() &&  !disp1.is_keyQ()) ) {
    disp1.wait_all();
  }
  return 0;

}
