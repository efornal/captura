#define UNICODE
#include <CImg.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cimg_library;
using namespace std;

/*
 * función aplicar_umbral: recibe una imagen en GRIS y un vector de
 * valores donde se transicionará entre blanco y negro. Los valores
 * en este array deberán estar ordenados y el cálculo es como sigue:
 * si el pixel < valores[0] => pixel=negro, si pix < valores[1] => blanco,
 * ... , si pix >= valores[n] => blanco. (si el array no está ordenado
 * no falla, pero no se garantiza que el resultado sea el esperado)
 * Devuelve una imagen binaria con el resultado de aplicar tal umbral.
 */
template<class T>
CImg<bool> aplicar_umbral( CImg<T> &imagen, unsigned n_valores, T* valores ) {
  unsigned x=0, y=0;
  bool valor = 1;
  CImg<bool> resultado( imagen.width(), imagen.height(), 1, 1, 0); //genero la imagen negra
  for (unsigned i=0; i<n_valores; i++ ) {
    cimg_forXY( imagen, x, y ) {
      if ( imagen(x,y) >= valores[i] )
	resultado(x,y) = valor;
    }
    valor = !valor;
  }
  return resultado;
}

template<class T>
CImg<bool> aplicar_umbral( CImg<T> &imagen, unsigned n_valores, vector<T> valores) {
  unsigned x=0, y=0;
  bool valor = 1;
  CImg<bool> resultado( imagen.width(), imagen.height(), 1, 1, 0); //genero la imagen negra
  for (unsigned i=0; i<n_valores; i++ ) {
    cimg_forXY( imagen, x, y ) {
      if ( imagen(x,y) >= valores[i] )
	resultado(x,y) = valor;
    }
    valor = !valor;
  }
  return resultado;
}

template<class T>
void gen_gradiente_horizontal( CImg<T> & imagen, T min, T max ){
  unsigned x=0, y=0;
  cimg_forXY( imagen, x, y ) {
    imagen(x,y) = ((T)x/(T)imagen.width())*((T)max-(T)min)+(T)min;
  }
}

void NOT( CImg<bool> & imagen ) {
  unsigned x=0, y=0;
  cimg_forXY( imagen, x, y ) {
    imagen(x,y) = !imagen(x,y);
  }
}


int main(int argc, char *argv[]) {

  if ( !argv[1] || !argv[2] ){
    cout<<argv[0]<<": Carga 2 imágenes y aplica umbrales invertidos en ellas.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen0> <archivo_imagen1>"<<endl;
    return 1;
  }

  CImg<float> imagen1( argv[1] );
  CImg<float> imagen2( argv[2] );
  CImg<float> gradiente(512, 64, 1, 1 );
  gen_gradiente_horizontal( gradiente, (float)0.0, (float)255.0 );

  vector<float> valores;

  CImg<bool> imagen1_bw = aplicar_umbral( imagen1, 0, valores );
  CImg<bool> imagen2_bw = aplicar_umbral( imagen2, 0, valores );
  CImg<bool> gradiente_bw = aplicar_umbral( gradiente, 0, valores );

  CImgDisplay d_imagen1( imagen1_bw );
  CImgDisplay d_imagen2( imagen2_bw );
  CImgDisplay d_gradiente( gradiente_bw );

  imagen1_bw.display( d_imagen1 );
  imagen2_bw.display( d_imagen2 );
  gradiente_bw.display( d_gradiente );

  while ( !d_imagen1.is_closed() && !d_imagen2.is_closed() && !d_gradiente.is_closed() ) {
    d_gradiente.wait_all();
    if ( d_gradiente.button() ) {
      if ( d_gradiente.mouse_x()>=0 ) { 
	valores.push_back( (float)floor( d_gradiente.mouse_x()/2.0 ) );
	sort( valores.begin(), valores.end() );
	unique( valores.begin(), valores.end() );

	imagen1_bw = aplicar_umbral( imagen1, valores.size(), valores );
	imagen2_bw = aplicar_umbral( imagen2, valores.size(), valores );
	gradiente_bw = aplicar_umbral( gradiente, valores.size(), valores );

	imagen1_bw.display( d_imagen1 );
	imagen2_bw.display( d_imagen2 );
	gradiente_bw.display( d_gradiente );
      }
    }
    if ( d_gradiente.is_keyR() ) {
      valores.clear();
      imagen1_bw = aplicar_umbral( imagen1, valores.size(), valores );
      imagen2_bw = aplicar_umbral( imagen2, valores.size(), valores );
      gradiente_bw = aplicar_umbral( gradiente, valores.size(), valores );

      imagen1_bw.display( d_imagen1 );
      imagen2_bw.display( d_imagen2 );
      gradiente_bw.display( d_gradiente );
    }
    if ( d_imagen1.is_keyN() ) {
      NOT(imagen1_bw);
      imagen1_bw.display( d_imagen1 );
    }
    if ( d_imagen2.is_keyN() ) {
      NOT(imagen2_bw);
      imagen2_bw.display( d_imagen2 );
    }
    if ( d_imagen1.is_keyO() ) {
      imagen1_bw |= imagen2_bw.resize(imagen1.width(),imagen1.height());
      imagen1_bw.display( d_imagen1 );
    }
    if ( d_imagen2.is_keyO() ) {
      imagen2_bw |= imagen1_bw.resize(imagen2.width(),imagen2.height());
      imagen2_bw.display( d_imagen2 );
    }
    if ( d_imagen1.is_keyA() ) {
      imagen1_bw &= imagen2_bw.resize(imagen1.width(),imagen1.height());
      imagen1_bw.display( d_imagen1 );
    }
    if ( d_imagen2.is_keyA() ) {
      imagen2_bw &= imagen1_bw.resize(imagen2.width(),imagen2.height());
      imagen2_bw.display( d_imagen2 );
    }
  }

  return 0;
}

