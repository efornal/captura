#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

/**
 * red2grey recibe una imagen en gris con spectrum==1 o RGB con información
 * de interés en el canal 0 (R), y la replica en los 3 para obtener una imagen
 * desaturada.
 */
template<class T>
CImg<T> red2grey( const CImg<T> imagen_roja ){
  CImg<T> salida;
  if ( imagen_roja.spectrum() < 3 )
    salida.assign( imagen_roja.width(), imagen_roja.height(),1,3,0);
  else
    salida.assign(imagen_roja);
  unsigned x, y;
  cimg_forXY ( imagen_roja, x, y ) {
    salida(x,y,0) = imagen_roja(x,y,0);
    salida(x,y,1) = imagen_roja(x,y,0);
    salida(x,y,2) = imagen_roja(x,y,0);
  }
  return salida;
}

/**
 * red2greyHSI: versión de red2gray que usa transformaciones HSI para lograr
 * (supuestamente el mismo resultado que red2grey.
 * @TODO ver porqué el resultado no es el mismo que red2grey
 */
template<class T>
CImg<T> red2greyHSI( const CImg<T> imagen_roja ){
  CImg<T> salida;
  if ( imagen_roja.spectrum() < 3 )
    salida.assign( imagen_roja.width(), imagen_roja.height(),1,3,0);
  else
    salida.assign(imagen_roja);
  unsigned x, y;
  cimg_forXY ( salida, x, y ) {
    salida(x,y,0) = imagen_roja(x,y,0);
    salida(x,y,1) = 0;
    salida(x,y,2) = 0;
  }
  salida.RGBtoHSI();
  cimg_forXY ( salida, x, y ) {
    salida(x,y,1) = 0;
   }
  salida.HSItoRGB();
  return salida;
}


int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    printf("%s: Ejercicio de Modelos de color.\n", argv[0]);
    printf("uso: %s <archivo_imagen>\n", argv[0]);
    return 1;
  }

  // 1. Cargar la imagen y mostrarla con sus componentes R G B H S I
  CImg<double> imagen( argv[1] ), modif( argv[1] );
  unsigned w = imagen.width(), h=imagen.height(), x, y;
  
  CImgList<double> lista_orig ( imagen, red2grey(imagen.get_crop(0,0,0,0, w-1,h-1,0,0)),
			       red2grey(imagen.get_crop(0,0,0,1, w-1,h-1,0,1)),
			       red2grey(imagen.get_crop(0,0,0,2, w-1,h-1,0,2)));
  
  imagen.RGBtoHSI();
  lista_orig.insert( red2grey(imagen.get_crop(0,0,0,0, w-1,h-1,0,0) * (255/240.0)));
  lista_orig.insert( red2grey(imagen.get_crop(0,0,0,1, w-1,h-1,0,1) * (255.0)));
  lista_orig.insert( red2grey(imagen.get_crop(0,0,0,2, w-1,h-1,0,2) * 255.0 ));

  CImgDisplay original;
  original.display(lista_orig, 'y');

  modif.RGBtoHSI();
  cimg_forXY( modif, x, y ) {
    // reflexión horizontal de colores
    modif(x,y,0,0) = (double)240 - modif(x,y,0,0);
    // variación de saturación por filas, de cero arriba a color puro abajo
    modif(x,y,0,1) = (double)y/(double)(h-1);
    // brillo máximo
    modif(x,y,0,2) = 1.0;
  }

  modif.HSItoRGB();

  CImgList<double> lista_mod ( modif, red2grey(modif.get_crop(0,0,0,0, w-1,h-1,0,0)),
			       red2grey(modif.get_crop(0,0,0,1, w-1,h-1,0,1)),
			       red2grey(modif.get_crop(0,0,0,2, w-1,h-1,0,2)));
 
  modif.RGBtoHSI();

  lista_mod.push_back(red2grey(modif.get_crop(0,0,0,0, w-1,h-1,0,0)*(255/240.0) ) );
  lista_mod.push_back(red2grey(modif.get_crop(0,0,0,1, w-1,h-1,0,1) * (255.0)) );
  lista_mod.push_back(red2grey(modif.get_crop(0,0,0,2, w-1,h-1,0,2) * 255.0 ));
  
  CImgDisplay modificada;
  modificada.display(lista_mod, 'y');

  while ( !original.is_closed() && !modificada.is_closed() ) {
    original.wait_all();
  }

  return 0;
}
