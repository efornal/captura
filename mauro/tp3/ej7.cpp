#define UNICODE
#include <CImg.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cimg_library;
using namespace std;

// radio es el entorno en norma infinito por afuera del pixel.
// por ej: si radio es 1, el entorno es de 3x3
template<class T>
void ecualizacion_local( CImg<T> &imagen, unsigned radio=1 ) {
  unsigned x, y;
  cimg_forXY( imagen, x, y ) {
    imagen(x,y) = imagen.get_crop(x-radio, y-radio, x+radio, y+radio).equalize(255,0,256)(radio,radio);
  }
}

template<class T>
CImg<T> ecualizacion_local( const CImg<T> &imagen, unsigned radio=1 ) {
  unsigned x, y;
  CImg<T> salida(imagen);
  cimg_forXY( imagen, x, y ) {
    salida(x,y) = imagen.get_crop(x-radio, y-radio, x+radio, y+radio).equalize()(radio,radio);
  }
  return salida;
}

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": ecualizacion local\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    return 1;
  }

  CImg<double> imagen( argv[1] );
  ecualizacion_local(imagen);
  imagen.display();

  return 0;
}

