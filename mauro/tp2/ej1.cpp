#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

template<class T>
CImg<T> aplicar_LUT( const CImg<T> &imagen, float a=1, float c=0) {
  unsigned x=0, y=0, chan=0;
  CImg<T> salida( imagen );
  cimg_forXYC( imagen, x, y, chan ) {
    salida(x,y,chan) = (T)(imagen(x,y,chan)*a+c);
  }
  return salida;
}

template<class T>
void aplicar_clip( CImg<T> &imagen, T min=0, T max=1) {
  unsigned x=0, y=0, c=0;
  cimg_forXYC( imagen, x, y, chan ) {
    if ( imagen(x,y,c) < min )
      imagen(x,y,c) = min;
    else if ( imagen(x,y,c) > max )
      imagen(x,y,c) = max;
  }
}

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": Aplica una LUT (s=ar+c) a la imagen.\
 Si no se proporcionan los parámetros a o c, toman el	  \
 valor por defecto de 1 y 0, respectivamente.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen> [a] [c]"<<endl;
    
    return 1;
  }
  
  float a=1, c=0;

  if ( argv[2] ) a = atof( argv[2] );
  if ( argv[3] ) c = atof( argv[3] );
  
  CImg<float> imagen( argv[1] );
  CImg<float> salida( imagen );
  CImg<float> grafico(256,256,1,1,0.9);
  CImg<float> valores(256,1,1,1,0);
  
  unsigned x=0, y=0;
  cimg_forXY( valores, x, y) {
    valores(x,y)=(float)x;
  }
  valores.normalize(0,1);
  valores = aplicar_LUT( valores, a, c );
  aplicar_clip(valores);
  
  imagen.normalize(0,1);
  salida = aplicar_LUT( imagen, a, c);
  aplicar_clip(salida);

  CImgList<float> lista;

  float color=0;

  lista.insert( imagen );
  lista.insert( grafico.draw_graph(valores,&color) );
  lista.insert( salida );

  lista.display();
  
  return 0;
}

