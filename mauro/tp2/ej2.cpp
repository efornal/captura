#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

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

  if ( !argv[1] || !argv[2] ){
    cout<<argv[0]<<": Aplica una transformación logarítmica ó de potencia sobre la imagen.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen> [tipo_transformacion] [gamma]"<<endl;
    cout<<"        "<<" donde tipo_transformacion=(log|exp)."<<endl;
    return 1;
  }

  bool es_log;
  if ( strncmp(argv[2],"log", 3) == 0 )
    es_log = true;
  else if ( strncmp(argv[2],"exp", 3) == 0 )
    es_log = false;
  else {
    cout<<"uso: "<<argv[0]<<"¡No entiendo qué operación querés realizar!"<<endl;
    return 1;
  }

  float gamma = 2;
  if ( argv[3] )
    gamma = atof( argv[3] );
  
  CImg<float> imagen( argv[1] );
  CImg<float> salida( imagen );
  CImg<float> grafico(256,256,1,1,0.9);
  CImgDisplay d_grafico( grafico );
  CImgDisplay d_salida( salida );

  CImg<float> valores(256,1,1,1,0);
  unsigned x=0, y=0;
  cimg_forXY( valores, x, y) {
    valores(x,y)=(float)x;
  }
  
  imagen.normalize(0,255);

  float negro = 0;
  float gris = 128;

  grafico.fill(255);
  if (es_log)
    grafico.draw_graph( (valores+1.0).log() , &negro );
  else
    grafico.draw_graph( (valores+1.0).pow(gamma) , &negro );
  grafico.draw_line( 0,255, 255,0, &gris );
  grafico.display( d_grafico );

  if (es_log)
    salida = (imagen+1.0).log();
  else
    salida = (imagen+1.0).pow(gamma);
  salida.display( d_salida );

  while ( !d_grafico.is_closed() && !d_salida.is_closed() ) {
    d_grafico.wait_all();
    if ( d_grafico.is_keyARROWUP() || d_grafico.is_keyARROWDOWN() ) {
      if ( d_grafico.is_keyARROWUP() )
	gamma += 0.1;
      else
	gamma -= 0.1;


      grafico.fill(255);
      if (es_log)
	grafico.draw_graph( (valores+1.0).log() , &negro );
      else
	grafico.draw_graph( (valores+1.0).pow(gamma) , &negro );
      grafico.draw_line( 0,255, 255,0, &gris );
      grafico.display( d_grafico );

      if (es_log)
	salida = (imagen+1.0).log();
      else
	salida = (imagen+1.0).pow(gamma);
      salida.display( d_salida );


    }
  }

  return 0;
}

