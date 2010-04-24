#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

template<class T>
CImg<T> LUT_n_puntos( const CImg<T> &imagen, unsigned n, T* r, T* s) {

  unsigned x=0, y=0, c=0;
  CImg<T> salida( imagen );
  T valor_pixel;
  cimg_forXYC( imagen, x, y, c ) {
    valor_pixel = imagen(x,y,c);
    for( unsigned i=1; i<n; i++ ) {
      if ( valor_pixel >= r[i-1] && valor_pixel <= r[i] ) {
	salida(x,y,c) = s[i-1] + (valor_pixel-r[i-1])*((s[i]-s[i-1])/(r[i]-r[i-1]));
	break;
      }
      else
	continue;
    }
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
    cout<<argv[0]<<": Aplica una LUT definida haciendo clic sobre el gráfico a la imagen.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    return 1;
  }
  
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

  float r[] = {0, 128, 192, 255};
  float s[] = {0, 128, 192, 255};

  float negro = 0;
  float gris = 128;
  bool click_es_2do_punto = false;

  grafico.fill(255);
  grafico.draw_graph( LUT_n_puntos(valores,4,r,s), &negro );
  grafico.draw_line( 0,255, 255,0, &gris );
  grafico.display( d_grafico );

  while ( !d_grafico.is_closed() && !d_salida.is_closed() ) {
    d_grafico.wait_all();
    if ( d_grafico.button() ) {
      if ( d_grafico.mouse_x()>=0 && d_grafico.mouse_y()>=0 )
	{ 
	  if ( !click_es_2do_punto ) {
	    r[1] = d_grafico.mouse_x();
	    s[1] = 255-d_grafico.mouse_y();
	    click_es_2do_punto = true;
	  }
	  else {
	    if ( d_grafico.mouse_x() < r[1] ) {
	      r[2] = r[1];
	      s[2] = s[1];
	      r[1] = d_grafico.mouse_x();
	      s[1] = 255-d_grafico.mouse_y();
	    } else {
	      r[2] = d_grafico.mouse_x();
	      s[2] = 255-d_grafico.mouse_y();
	    }
	    
	    // Aplico la LUT 4 puntos a la imagen y 
	    salida = LUT_n_puntos( imagen, 4, r, s);
	    salida.display( d_salida );

	    grafico.fill(255);
	    grafico.draw_graph( LUT_n_puntos(valores,4,r,s), &negro );
	    grafico.draw_line( 0,255, 255,0, &gris );
	    grafico.display( d_grafico );
	    
	    click_es_2do_punto = false;
	    }
	  }
      }
  }

  return 0;
}

