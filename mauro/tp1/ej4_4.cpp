#define UNICODE
#include <CImg.h>
#include <iostream>
#include <cstdlib>

using namespace cimg_library;
using namespace std;

template<class T>
CImg<T> pasa_bajos ( unsigned lado=256,unsigned radio=64 ) {
  T blanco = (T) 1, negro = (T) 0;
  CImg<T> imagen( lado, lado, 1, 1, negro );
  imagen.draw_circle ( lado/2.0, lado/2.0, radio, &blanco );
  imagen.normalize();
  return imagen;
}

int main(int argc, char *argv[]) {

  if ( !argv[1] || !argv[2] ){
    cout<<argv[0]<<": genera una imagen negra con un círculo blanco centrado.\n";
    cout<<"uso: "<<argv[0]<<" <lado_imagen> <radio_circulo>"<<endl;
    return 1;
  }

  pasa_bajos<bool> ( atoi( argv[1] ), atoi( argv[2] ) ).display();
 
  return 0;
}
