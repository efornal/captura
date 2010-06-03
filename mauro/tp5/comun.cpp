#include <CImg.h>
using namespace cimg_library;
/**
 * 
 */
template<class T>
CImg<T> gen_linea_horizontal( short w=256, short h=256, short offset_v=0 ){
  CImg<T> imagen( w, h, 1, 1, 0);
  T blanco=(T) 1;
  imagen.draw_line(0,(int)(floor(h/2)+offset_v),w-1,(int)(floor(h/2)+offset_v),&blanco);
  return imagen;
}

/**
 * 
 */
template <class T>
CImg<T> gen_linea_vertical( short w=256, short h=256, short offset_h=0 ){
  CImg<T> imagen( w, h, 1, 1, 0);
  T blanco= (T)1;
  imagen.draw_line((int)(floor(w/2)+offset_h),0,(int)(floor(w/2)+offset_h),h-1,&blanco);
  return imagen;
}

/**
 * 
 */
template <class T>
CImg<T> gen_rectangulo( short w=256, short h=256, short ext_h=32, short ext_v=32,
			  short offset_h=0, short offset_v=0 ){
  CImg<T> imagen( w, h, 1, 1, 0);
  T blanco= (T)1;
  imagen.draw_rectangle( (int)(floor(w/2)-floor(ext_h/2)+offset_h),
			 (int)(floor(h/2)-floor(ext_v/2)+offset_v),
			 (int)(floor(w/2)+floor(ext_h/2)+offset_h),
			 (int)(floor(h/2)+floor(ext_v/2)+offset_v),
			 &blanco);
  return imagen;
}

/**
 * 
 */
template <class T>
CImg<T> gen_circulo( short w=256, short h=256, short radio=32,
			 short offset_h=0, short offset_v=0 ){
  CImg<T> imagen( w, h, 1, 1, (T)0);
  T blanco=(T)1;
  imagen.draw_circle( (int)(floor(w/2)+offset_h),
		      (int)(floor(h/2)+offset_v),
		      radio, &blanco);
  return imagen;
}

/**
 * devuelve una CImg<T> con la magnitud de la FFT de la imagen imagen.
 * @param imagen: la imagen de la que se calcula la FFT.
 * @param shift: indica si shiftear o no la FFT
 * @param log: indica si aplicar logaritmo o no a la salida
 * @param normalize: indica si normalizar el resultado en (0,1)
 */
template <class T>
CImg<T> calcular_magnitud_fft ( const CImg<T> &imagen, bool shift=true, bool log=true, bool normalize=true ) {
  CImgList<T> fft = imagen.get_FFT();
  CImg<T> magnitud = (fft[0].get_sqr() + fft[1].get_sqr()).sqrt();

   if (shift) magnitud.shift( (int)floor(imagen.width()/2), (int)floor(imagen.height()/2), 0, 0, 2);

   if (log) magnitud.log();

   if (normalize) magnitud.normalize(0,1);

  return magnitud;
}

/**
 * realimag2magfase recibe una CImgList { real, imaginario } y devuelve otra
 * { modulo, fase }
 */
template <class T>
CImgList<T> realimag2magfase ( const CImgList<T> &realimag ) {
  CImg<T> magnitud = (realimag[0].get_sqr() + realimag[1].get_sqr()).sqrt();
  CImg<T> fase = realimag[1].get_atan2( realimag[0] + 0.01);
  return CImgList<T>( magnitud, fase );;
}

/**
 * magfase2realimag recibe una CImgList { modulo, fase } y devuelve otra
 * { real, imaginario }
 */
template <class T>
CImgList<T> magfase2realimag ( const CImgList<T> &magfase ) {
  CImg<T> real = magfase[1].get_cos().mul( magfase[0] );
  CImg<T> imag = magfase[1].get_sin().mul( magfase[0] );
  return CImgList<T>( real, imag );;
}

/**
 * filtro pb ideal
 */
template<class T>
CImg<T> filtro_pb_ideal ( short w, short h, T wc, bool centrar=true ) {
  if ( !centrar )
    return gen_circulo<T>( w, h, wc, 0, 0 ).shift( w/2, h/2, 0, 0, 2);
  return gen_circulo<T>( w, h, wc, 0, 0 );  
}

/**
 * filtro pa ideal
 */
template<class T>
CImg<T> filtro_pa_ideal ( short w, short h, T wc, bool centrar=true ) {
  return (( filtro_pb_ideal<T>(w,h,wc,centrar) -1 )*(-1.0));
}

/**
 * filtro pb rectangular
 */
template<class T>
CImg<T> filtro_pb_rectang ( short w, short h, T wcx, T wcy, bool centrar=true ) {
  if ( !centrar )
    return gen_rectangulo<T>( w, h, 2*wcx, 2*wcy, 0, 0 ).shift( w/2, h/2, 0, 0, 2);
  return gen_rectangulo<T>( w, h, 2*wcx, 2*wcy, 0, 0 );  
}

/**
 * filtro pa rectangular
 */
template<class T>
CImg<T> filtro_pa_rectang ( short w, short h, T wcx, T wcy, bool centrar=true ) {
  return ( filtro_pb_rectang<T>(w,h,wcx,wcy,centrar) -1 ).mul(-1.0);
}

/**
 * filtro pb gaussiano isotrópico
 */
template<class T>
CImg<T> filtro_pb_gauss ( short w, short h, T var, bool centrar=true ) {
  CImg<T> H(w,h,1,1,(T)0);
  T blanco = (T)1.0;
  if ( !centrar )
    return H.draw_gaussian(w/2.0,h/2.0,var,&blanco).shift( w/2, h/2, 0, 0, 2);
  return H.draw_gaussian(w/2.0,h/2.0,var,&blanco);  
}

/**
 * filtro pa gaussiano isotrópico
 */
template<class T>
CImg<T> filtro_pa_gauss ( short w, short h, T var, bool centrar=true ) {
  return (( filtro_pb_gauss<T>(w,h,var,centrar)-1 )*(-1.0));
}

/**
 * filtro pb gaussiano anisotrópico con matriz de covariancia
 */
template<class T>
CImg<T> filtro_pb_gauss ( short w, short h, CImg<T> var, bool centrar=true ) {
  CImg<T> H(w,h,1,1,(T)0);
  T blanco = (T)1.0;
  if ( !centrar )
    return H.draw_gaussian(w/2.0,h/2.0,var,&blanco).shift( w/2, h/2, 0, 0, 2);
  return H.draw_gaussian(w/2.0,h/2.0,var,&blanco);  
}

/**
 * filtro pa gaussiano anisotrópico con matriz de cov
 */
template<class T>
CImg<T> filtro_pa_gauss ( short w, short h, CImg<T> var, bool centrar=true ) {
  return ( (filtro_pb_gauss(w,h,var,centrar)-1 )*(-1.0));
}

/**
 * distancia euclídea
 */
template<class T, class U>
U d2 ( T x, T y, U x0, U y0 ) {
  return sqrt( pow((U)x-x0,2.0)+pow((U)y-y0,2.0) );
}

/**
 * distancia mahátan
 */
template<class T, class U>
U d1 ( T x, T y, U x0, U y0 ) {
  return ( abs((U)x-x0)+abs((U)y-y0) );
}

/**
 * filtro pb butterworth de orden n
 */
template<class T>
CImg<T> filtro_pb_butter ( short w, short h, T wc, T n=(T)2.0, bool centrar=true ) {
  CImg<T> H(w,h,1,1,(T)0);
  unsigned x, y;
  T cx = (T)w/2, cy = (T)h/2;
  cimg_forXY( H, x, y ) {
    H(x,y) = pow( 1+pow(d2(x,y,cx,cy)/wc,2*n), -1.0);
  }
  if ( !centrar )
    return H.shift( w/2, h/2, 0, 0, 2);
  return H;
}

/**
 * filtro pa butterworth de orden n
 */
template<class T>
CImg<T> filtro_pa_butter ( short w, short h, T wc, T n=(T)2.0, bool centrar=true ) {
  return ( (filtro_pb_butter(w,h,wc,n,centrar)-1 )*(-1.0));
}

/**
 * filtro homomórfico
 */
template<class T>
CImg<T> filtro_homo ( short w, short h, T gl, T gh, T D0, T c=(T)2.0, bool centrar=true ) {
  CImg<T> H(w,h,1,1,(T)0);
  unsigned x,y;
  T cx=w/2.0, cy=h/2.0;
  cimg_forXY( H, x, y ) {
    H(x,y) = (gh-gl) * ( 1-exp( -c*(d2(x,y,cx,cy)/pow(D0,2.0)) ) ) + gl;
  }
  if ( !centrar )
    return H.shift( w/2, h/2, 0, 0, 2);
  return H;
}

/**
 * filtrar con filtro homomórfico
 */
template<class T>
CImg<T> filtrar_homo ( const CImg<T> &imag, T gl, T gh, T D0, T c=(T)2.0 ) {
  short w = imag.width(), h=imag.height();

  CImgList<T> fft = (imag.get_channel(0) + 1.0).get_log().get_FFT();

  CImg<T> filtro = filtro_homo( w, h, gl, gh, D0, c,false );

  fft = realimag2magfase ( fft );

  cimg_forXY( filtro, x, y ) {
    fft[0](x,y) *= filtro(x,y);
  }

  fft = magfase2realimag ( fft );

  return fft.get_FFT(true)[0].exp();
}

/**
 * filtro alta potencia
 */
template<class T>
CImg<T> filtro_ap ( const CImg<T> &filtro_pa, T A ) {

  return CImg<T>( filtro_pa+(A-1.0) );
}


/**
 * filtro énfasis de alta frecuencia
 */
template<class T>
CImg<T> filtro_eaf ( const CImg<T> &filtro_pa, T a, T b ) {
  return CImg<T>( ((filtro_pa*b)+a) );
}

/**
 * imagen para convertir una imagen de 3 canales a una CImglist con 3 imagenes grises
 */
template<class T>
CImgList<T> canales_a_lista ( const CImg<T> &imag ) {
  CImgList<T> salida;
  unsigned c;
  cimg_forC(imag, c) {
    salida.push_back(imag.get_channel(c));
  }
  return salida;
}

/**
 * imagen para convertir una CImgList deimagenes grises a una imagen compuesta por n canales
 */
template<class T>
CImg<T> lista_a_canales ( const CImgList<T> &lista ) {
  CImg<T> salida( lista[0].width(), lista[0].height(), 1, lista.size());
  unsigned x,y,c;
  cimg_forXYC(salida, x,y,c) {
    salida(x,y,0,c)=lista[c](x,y);
  }
  return salida;
}

/**
 * imagen para filtrar genérica -- SOLO FILTRA UN CANAL!
 */
template<class T>
CImg<T> filtrar ( const CImg<T>& imag, const CImg<T> &filtro, bool filtro_esta_centrado=true ) {
  short w = imag.width(), h=imag.height();
  CImgList<T> fft;
  unsigned x, y;
  fft = realimag2magfase ( imag.get_FFT() );
  CImg<T> fil = filtro;
  if( filtro_esta_centrado)
    fil.shift(w/2, h/2, 0, 0,2 ); 
  
  cimg_forXY( filtro, x, y ) {
    fft[0](x,y) *= fil(x,y);
  }
  fft = magfase2realimag ( fft );
  return fft.get_FFT(true)[0];
}

// esta intenté hacerla para lograr filtrar las imagenes color... pero bue no anda
// template<class T>
// CImg<T> filtrarNOUSAR ( const CImg<T>& imag, const CImg<T> &filtro, bool filtro_esta_centrado=true ) {
//   short w = imag.width(), h=imag.height();
//   CImgList<T> lista = canales_a_lista (imag);
//   CImgList<T> canales;
//   CImgList<T> fft;
//   unsigned x, y;
//   CImg<T> fil = filtro;
//   if( filtro_esta_centrado)
//     fil.shift(w/2, h/2, 0, 0,2 );
//   for(unsigned i=0; i<lista.size(); i++) {
//     fft = lista[i].get_FFT();
//     fft = realimag2magfase ( fft );
//     cimg_forXY( filtro, x, y ) {
//       fft[0](x,y) *= filtro(x,y);
//     }
//     fft = magfase2realimag ( fft );
//     canales.push_back( fft.get_FFT(true)[0] );
//   }
//   return lista_a_canales ( canales );
// }

