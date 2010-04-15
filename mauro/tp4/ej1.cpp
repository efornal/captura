#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": Ejercicio de Modelos de color.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;

    return 0;
  }

  // 1. Cargar las imagenes y crear displays
  CImg<float> imagen( argv[1] );
  // copio la imagen original
  CImg<float> mod1=imagen, mod2=imagen, mod3=imagen;

  unsigned w = imagen.width(), h=imagen.height();
  
  CImgList<float> lista_orig ( imagen, imagen.get_crop(0,0,0,0, w-1,h-1,0,0),
			       imagen.get_crop(0,0,0,1, w-1,h-1,0,1),
			       imagen.get_crop(0,0,0,2, w-1,h-1,0,2));

  imagen.RGBtoHSI();
  lista_orig.insert( imagen.get_crop(0,0,0,0, w-1,h-1,0,0) * (255/360.0));
  lista_orig.insert( imagen.get_crop(0,0,0,1, w-1,h-1,0,1) * (255.0));
  lista_orig.insert( imagen.get_crop(0,0,0,2, w-1,h-1,0,2) * 255.0 );

  CImgDisplay original ( lista_orig, "Original, RGB, HSI");

  while ( !original.is_closed() ) {
    original.wait_all();
  }



  mod1.display();
  //reflejo los colores
  mod1.RGBtoHSI();
  mod1.channel(0) =  ( mod1.get_crop(0,0,0,0,w-1,h-1,0,0)*(-1))+240;

  //mod1.HSItoRGB();
  mod1.display();

  return 0;
}
