#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

// me devuelve 0 si la imagen es vertical, 1 si horizontal
template<class T> int orientacion ( const T & imagen ){ return (imagen.width() >= imagen.height()) ? 1 : 0; }

// idem anterior pero con coordenadas
int orientacion ( int x0, int y0, int x1, int y1 ) { return abs(x1-x0) >= abs(y1-y0) ? 1 : 0; }

CImg<unsigned char> perfil_intensidad ( const CImg<unsigned char> & imagen, int x0, int y0, int x1, int y1, short canal=0 ) {
  
  // chequeo que las coordenadas estén dentro de los rangos válidos, sino devuelvo
  // un nuevo objeto CImg vacío.
  if ( x0 < 0 || x1 < 0 || y0 < 0 || y1 < 0 ||
       x0 > imagen.width()-1 || x1 > imagen.width()-1 || y0 > imagen.height()-1 || y1 > imagen.height()-1 ) {
    return CImg<unsigned char> ();
  }

  unsigned nro_canales = imagen.spectrum();
  unsigned char* blanco = new unsigned char[nro_canales], * negro = new unsigned char[nro_canales];
  for ( unsigned i=0; i<nro_canales; i++ ) {
    blanco [i] = 255;
    negro [i] = 0;
  }

  // genero como máscara un segmento que va de (x0,y0) a (x1,y1)
  CImg<unsigned char> enmascarada( imagen.get_crop( 0,0,0,0,imagen.width()-1,imagen.height()-1,0,imagen.spectrum()-1).fill(*negro).draw_line(x0,y0,x1,y1,blanco).get_min(imagen) );
  
  //CImg<unsigned char> resultado ();

  //enmascarada.display();

  if ( orientacion (x0,y0,x1,y1) == 1 ) {
    //resultado = CImg<unsigned char> (abs(x1-x0)+1,1,1,nro_canales);
    
    // sgn indica si los valores se recorren de derecha a izq o viceversa
    int sgn = 1;
       if( x1 == 0 ) sgn = -1;
        else if (x0 != x1 ) sgn = (x1-x0) / abs(x1-x0);
    
    for (unsigned i=0; i<=abs(x1-x0); i++ ) {
      enmascarada(i,0)=enmascarada.get_crop(x0+(i*sgn),y0,0,x0+(i*sgn),y1,0).max();
    }
    return enmascarada.get_line(0);
  }
  else {
    //    resultado.assign(1,abs(y1-y0)+1,1,nro_canales);
    int sgn = 1;
       if( y1 == 0 ) sgn = -1;
        else if (y0 != y1 ) sgn = (y1-y0) / abs(y1-y0);
    for (unsigned i=0; i<=abs(y1-y0); i++ ) {
      enmascarada(0,i)=enmascarada.get_crop(x0,y0+(i*sgn),0,x1,y0+(i*sgn),0).max();
    }
    
  }
  return enmascarada.get_column(0);
}

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": carga una imagen de intensidad e informa la de los puntos que se cliquean.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen_intensidad>"<<endl;

    return 0;
  }

  // 1. Cargar las imagenes y crear displays
  CImg<unsigned char> imagen( argv[1] ), grafico(300,300,1,1,192);
  CImgDisplay disp_imag(imagen,"Imagen"), disp_graf(grafico,"Perfil de intensidad");

  // esto supuestamente convertiría la imagen en una de un solo canal???
  //imagen.assign(imagen.get_crop(0,0,0,0,imagen.width()-1,imagen.height()-1,0,0));

  int x0,y0,x1,y1;
  const unsigned char color [] = { 0 };

  bool click_es_2do_punto = false;

  while ( !disp_imag.is_closed() && !disp_graf.is_closed() ) {

    disp_imag.wait(); // espero tecla/click
    
    if ( disp_imag.button() ) {

	if ( disp_imag.mouse_x()>=0 && disp_imag.mouse_y()>=0 )
	  { 

	    if ( !click_es_2do_punto ) {
	      x0 = disp_imag.mouse_x();
	      y0 = disp_imag.mouse_y();
	      click_es_2do_punto = true;
	    }
	    else {
	      x1 = disp_imag.mouse_x();
	      y1 = disp_imag.mouse_y();
	      
	      grafico.fill(192).draw_graph( perfil_intensidad( imagen,x0,y0,x1,y1) , color, 1,1,1,0,0,true ).display(disp_graf);

	      click_es_2do_punto = false;
	    }
	  }

	cout<<"Intensidad punto ("<<disp_imag.mouse_x()<<","<<disp_imag.mouse_y()<<"): "<<
	  (unsigned int)imagen(disp_imag.mouse_x(),disp_imag.mouse_y())<<endl;
      }

  }

  return 0;
}

