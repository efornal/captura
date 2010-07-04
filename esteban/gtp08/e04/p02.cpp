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

  // Si sizeblock = 8 => 64 coeficientes => N ->[1,2,..,64]
  CImgList<double> list (
                 jpeg( img, sizeblock, 1 ),
                 jpeg( img, sizeblock, 10 ),
                 jpeg( img, sizeblock, 30 ),
                 jpeg( img, sizeblock, 40 ),
                 jpeg( img, sizeblock, 60 ) );
  list.display();

}
