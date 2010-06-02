#include <CImg.h>

using namespace cimg_library;

/**
 * orientacion devuelve 1 si imagen es horizontal, 0 si vertical
 */
template<class T>
int orientacion ( const CImg<T> & imagen ){ return (imagen.width() >= imagen.height()) ? 1 : 0; }

/**
 * idem anterior, pero con coordenadas en vez de una imagen
 */
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

// @TODO terminar esta!!!
// template<class T>
// CImg<T> perfil_intensidad_RGB ( const CImg<T> &imagen, int x0, int y0, int x1, int y1 ) {
//   CImg<T> salida( 256, 256, 3, 1 );

//   if( imagen.spectrum() < 3 )
//     return salida.empty();

//   const T r[]={(T)1,(T)0,(T)0}, g[]={(T)0,(T)1,(T)0},b[]={(T)0,(T)0,(T)1};

//   salida.fill((T)0, (T)0, (T)0);
//   salida += salida.get_fill((T)0,(T)0,(T)0).draw_graph(
// }


/**
 * pintar_grises devualve una imagen RGB con los grises en el rango [min. max)
 * pintados con el color dado por r, g y b.
 */
template<class T, class U>
CImg<U> pintar_grises ( const CImg<T> & gris, T min, T max, U r=(U)255, U g=(U)255, U b=(U)0 ) {
  CImg<U> salida( gris.width(), gris.height(), 1, 3 );
  unsigned x, y;
  cimg_forXY( gris, x, y ) {
    if ( gris(x,y) >= min && gris(x,y) < max ) {
      salida(x,y,0,0) = r;
      salida(x,y,0,1) = g;
      salida(x,y,0,2) = b;
    }
    else {
      salida(x,y,0,0) = (T)gris(x,y);
      salida(x,y,0,1) = (T)gris(x,y);
      salida(x,y,0,2) = (T)gris(x,y);
    }
  }
  return salida;
}
