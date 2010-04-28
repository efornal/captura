#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

template<class T>
CImg<T> mul( CImg<T> im1, CImg<T> im2 ) {
  //  unsigned x=0, y=0, c=0;
  CImg<T> salida;
  if ( im1.width() != im2.width() || im1.height() != im2.height() || im1.spectrum() != im2.spectrum() )
    return salida;
  salida = im1;
  cimg_forXYC( im1, x, y, c ) {
    salida(x,y,c) = im1(x,y,c) * im2(x,y,c);
  }
  return salida;
}

int main(int argc, char *argv[]) {

  if ( !argv[1] || !argv[2] || !argv[3] ){
    cout<<argv[0]<<": Aplica una operación aritmética entre dos imágenes.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen1> <operación> <archivo_imagen2>"<<endl;
    cout<<"        "<<" donde operación=(sum|dif|mul|div)."<<endl;
    return 1;
  }

  short operacion;
  if ( strncmp(argv[2],"sum", 3) == 0 )
    operacion = 1;
  else if ( strncmp(argv[2],"dif", 3) == 0 )
    operacion = 2;
  else if ( strncmp(argv[2],"mul", 3) == 0 )
    operacion = 3;
  else if ( strncmp(argv[2],"div", 3) == 0 )
    operacion = 4;
  else {
    cout<<"uso: "<<argv[0]<<"¡No entiendo qué operación querés realizar!"<<endl;
    return 1;
  }
  
  CImg<float> imagen1( argv[1] );
  CImg<float> imagen2( argv[3] );
  CImg<float> salida;

  switch (operacion) {
  case 1:
    salida = (imagen1+imagen2.resize(imagen1.width(),imagen1.height())).get_normalize(0,255);
    break;
  case 2:
    salida = imagen1-imagen2.resize(imagen1.width(),imagen1.height());
    salida = salida - salida.min();
    salida.normalize(0,255);
    break;
  case 3:
    salida = mul(imagen1, imagen2.resize(imagen1.width(),imagen1.height()).get_quantize(2).normalize(0,1) );
    break;
  case 4:
    salida = mul(imagen1, (imagen2.resize(imagen1.width(),imagen1.height()).pow(-1)+1) );
    break;
  }
  salida.display( );
  return 0;
}

