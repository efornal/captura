#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;


// template<class T>
// T max( T a, T b ) {
//   return ( a > b ) ? a : b;
// }

// template<class T>
// T min( T a, T b ) {
//   return ( a > b ) ? b : a;
// }

template<class T>
CImg<T> emboss( CImg<T> imagen, int x, int y, bool inv=false ) {
  if (inv) imagen *= -1;
  int w = imagen.width(), h = imagen.height();
  CImg<T> salida = imagen.get_crop(max(0,-x),max(0,-y),min(w,w-x),min(h,h-y))
    - imagen.get_crop(max(x,0),max(y,0),min(w,w+x),min(h,h+y));
  return salida;
}

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cerr<<"ERROR: No se ha especificado un archivo imagen.\n";
    cout<<argv[0]<<": Aplica efecto 'emboss' sobre la imagen.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    return 1;
  }

  CImg<float> original( argv[1] );
  CImg<float> mod( original );
  CImgDisplay disp;

  short x=0, y=0;
  bool invertir = false;
  mod.display(disp);

  while (! disp.is_closed() ) {
    disp.wait();
    if ( disp.is_keyARROWUP() ) { y +=1; disp.flush(); }
    if ( disp.is_keyARROWDOWN() ) { y -=1; disp.flush(); }
    if ( disp.is_keyARROWLEFT() ) { x -=1; disp.flush(); }
    if ( disp.is_keyARROWRIGHT() ) { x +=1; disp.flush(); }
    if ( disp.is_keyI() ) { invertir = !invertir; disp.flush(); }

    mod = emboss( original, x, y, invertir);
    disp.resize(mod);
    mod.display( disp );

  }

  return 0;
}

