#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": carga una imagen y la muestra cuantizada con menos bits.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;

    return 1;
  }

  CImg<float> imagen( argv[1] );

  unsigned q=8;

  CImgList<float> l( imagen);

  while (q>1) {
    l.insert( imagen.get_quantize(q--));
  }

  l.display();
  return 0;
}

