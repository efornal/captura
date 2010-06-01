#define UNICODE
#include <CImg.h>

using namespace cimg_library;
using namespace std;

/**
 * orientacion devuelve 1 si imagen es horizontal, 0 si vertical
 */
template<class T>
int orientacion ( const CImg<T> & imagen ){ return (imagen.width() >= imagen.height()) ? 1 : 0; }

// idem anterior pero con coordenadas
template<class T>
int orientacion ( T x0, T y0, T x1, T y1 ) { return abs(x1-x0) >= abs(y1-y0) ? 1 : 0; }

/**
 * perfil_intensidad devuelve el perfil de intensidad de imagen entre los puntos (x0,y0)->(x1,y1)
 * del canal canal de la imagen, como una imagen CImg<T> de espectro 1.
 */
template<class T>
CImg<T> perfil_intensidad ( const CImg<T> & imagen,
			    int x0, int y0, int x1, int y1,
			    short canal=0 ) {
  
  // chequeo que las coordenadas estén dentro de los rangos válidos, sino devuelvo
  // un nuevo objeto CImg vacío.
  if ( x0 < 0 || x1 < 0 || y0 < 0 || y1 < 0 ||
       x0 > imagen.width()-1 || x1 > imagen.width()-1 ||
       y0 > imagen.height()-1 || y1 > imagen.height()-1 ) {
    return CImg<T>().empty();
  }

  unsigned sp = imagen.spectrum(), w=imagen.width(), h=imagen.height();
  T blanco [] = { (T)1 };//, negro [] = { (T)0 };

  // obtengo el canal de interés
  CImg<T> chan = imagen.get_channel(canal);

  // creo una máscara con la línea por donde va el perfil de intensidad y multiplico el canal
  // por ésta
  CImg<T> mask = imagen.get_channel(canal).fill(0).draw_line(x0,y0,x1,y1,blanco).get_mul(chan);
  
  if ( orientacion (x0,y0,x1,y1) == 1 ) {
    // sgn indica si los valores se recorren de derecha a izq o viceversa
    int sgn = 1;
    if( x1 == 0 ) sgn = -1;
    else if (x0 != x1 ) sgn = (x1-x0) / abs(x1-x0);
    
    for (unsigned i=0; i<=abs(x1-x0); i++ ) {
      mask(i,0)=mask.get_crop(x0+(i*sgn),y0,0,x0+(i*sgn),y1,0).max();
    }
    return mask.get_crop(0,0,abs(x1-x0),0);
  }
  else {
    int sgn = 1;
    if( y1 == 0 ) sgn = -1;
    else if (y0 != y1 ) sgn = (y1-y0) / abs(y1-y0);
    for (unsigned i=0; i<=abs(y1-y0); i++ ) {
      mask(0,i)=mask.get_crop(x0,y0+(i*sgn),0,x1,y0+(i*sgn),0).max();
    }
  }
  return mask.get_crop(0,0,0,abs(y1-y0));
}

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    printf("%s: carga una imagen RGB y muestra los perfiles de intensidad.\n", argv[0]);
    printf("uso: %s <archivo_imagen_intensidad>\n",argv[0]);

    return 0;
  }

  // 1. Cargar las imagenes y crear displays
  CImg<double> imagen( argv[1] ), grafico(256,256,1,3,0);
  CImgDisplay disp_imag(imagen,"Imagen"), disp_graf(grafico,"Perfil de intensidad");

  int x0,y0,x1,y1;
  const double r [] = { 1,0,0 }, g [] = {0,1,0}, b[] = {0,0,1};
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
	      
	      if ( x0==x1 && y0==y1 ) continue;

	      grafico.fill(0);
	      grafico+=grafico.get_fill(0).draw_graph(
                               perfil_intensidad( imagen,x0,y0,x1,y1,0),r,1,1,1,0,0,true );
	      grafico+=grafico.get_fill(0).draw_graph(
			       perfil_intensidad( imagen,x0,y0,x1,y1,1),g,1,1,1,0,0,true );
	      grafico+=grafico.get_fill(0).draw_graph(
			       perfil_intensidad( imagen,x0,y0,x1,y1,2),b,1,1,1,0,0,true );
	      grafico.display(disp_graf);

	      click_es_2do_punto = false;
	    }
	  }
      }
  }
  return 0;
}


