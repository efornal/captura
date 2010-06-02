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
  CImg<T> imagen( w, h, 1, 1, 0);
  T blanco=(T)1;
  imagen.draw_circle( (int)(floor(w/2)+offset_h),
		      (int)(floor(h/2)+offset_v),
		      radio, &blanco);
  return imagen;
}

/**
 * 
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
 * 
 */
template <class T>
CImgList<T> realimag2magfase ( const CImgList<T> &realimag ) {
  CImg<T> magnitud = (realimag[0].get_sqr() + realimag[1].get_sqr()).sqrt();
  CImg<T> fase = realimag[1].get_div( realimag[0] + 0.01).atan2();
  return CImgList<T>( magnitud, fase );;
}

/**
 * 
 */
template <class T>
CImgList<T> magfase2realimag ( const CImgList<T> &magfase ) {
  CImg<T> real = magfase[1].get_cos().mul( magfase[0] );
  CImg<T> imag = magfase[1].get_sin().mul( magfase[0] );
  return CImgList<T>( real, imag );;
}
