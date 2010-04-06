#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": carga una imagen de intensidad e informa la de los puntos que se cliquean.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen_intensidad>"<<endl;

    return 0;
  }

  // Variable para perfiles horizontales(0)/verticales(1)
  bool orientacion = 0;

  // 1. Cargar las imagenes y crear displays
  CImg<unsigned char> imagen( argv[1] ), grafico(300,300,1,1,192);
  CImgDisplay disp_imag(imagen,"Imagen"), disp_graf(grafico,"Perfil de intensidad");

  // esto supuestamente convertiría la imagen en una de un solo canal???
  //imagen.assign(imagen.get_crop(0,0,0,0,imagen.width()-1,imagen.height()-1,0,0));

  int x=0,y=0;
  const unsigned char color [] = { 0 };

  while ( !disp_imag.is_closed() && !disp_graf.is_closed() ) {

    disp_imag.wait(); // espero tecla/click
    
    if ( disp_imag.button() ) {

	if ( orientacion==0 && disp_imag.mouse_y()>=0 )
	  { // si el evento fue un click, en la altura de la img, y orient = horiz
	    y =  disp_imag.mouse_y();
	    
	    grafico.fill(192).draw_graph( imagen.get_crop(0,y,imagen.width()-1,y),color).display(disp_graf);
	  }

	if ( orientacion==1 && disp_imag.mouse_x()>=0 )
	  { // si el evento fue un click, en el ancho dxe la img, y orient = vert
	    x =  disp_imag.mouse_x();
	    
	    grafico.fill(192).draw_graph( imagen.get_crop(x,0,x,imagen.height()-1),color).display(disp_graf);
	  }

	cout<<"Intensidad punto ("<<disp_imag.mouse_x()<<","<<disp_imag.mouse_y()<<"): "<<
	  (unsigned int)imagen(disp_imag.mouse_x(),disp_imag.mouse_y())<<endl;

      }

    if ( disp_imag.is_keyO() ) { 
	orientacion = !orientacion;
	cout<<"orientacion == "<<orientacion<<endl;
      }
  }

  return 0;
}
