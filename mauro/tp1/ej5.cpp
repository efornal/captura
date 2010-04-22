#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": carga una imagen y la muestra a resoluciones menores.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;

    return 1;
  }

  CImg<float> imagen( argv[1] );

  unsigned ancho=imagen.width(), alto=imagen.height(), w=ancho, h=alto;

  CImgList<float> l( imagen);

  while (ancho >1 && alto > 1) {

    ancho/=2;
    alto/=2;
    l.insert( imagen.get_resize(ancho,alto).resize(w,h));

     }

  l.display();
  return 0;
}

