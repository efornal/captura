#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

CImg<float> gen_linea_horizontal( short w=256, short h=256, short offset_v=0 ){
  CImg<float> imagen( w, h, 1, 1, 0);
  float blanco=1;
  imagen.draw_line(0,(int)(floor(h/2)+offset_v),w-1,(int)(floor(h/2)+offset_v),&blanco);
  return imagen;
}

CImg<float> gen_linea_vertical( short w=256, short h=256, short offset_h=0 ){
  CImg<float> imagen( w, h, 1, 1, 0);
  float blanco=1;
  imagen.draw_line((int)(floor(w/2)+offset_h),0,(int)(floor(w/2)+offset_h),h-1,&blanco);
  return imagen;
}

CImg<float> gen_rectangulo( short w=256, short h=256, short ext_h=32, short ext_v=32,
			  short offset_h=0, short offset_v=0 ){
  CImg<float> imagen( w, h, 1, 1, 0);
  float blanco=1;
  imagen.draw_rectangle( (int)(floor(w/2)-floor(ext_h/2)+offset_h),
			 (int)(floor(h/2)-floor(ext_v/2)+offset_v),
			 (int)(floor(w/2)+floor(ext_h/2)+offset_h),
			 (int)(floor(h/2)+floor(ext_v/2)+offset_v),
			 &blanco);
  return imagen;
}

CImg<float> gen_circulo( short w=256, short h=256, short radio=32,
			 short offset_h=0, short offset_v=0 ){
  CImg<float> imagen( w, h, 1, 1, 0);
  float blanco=1;
  imagen.draw_circle( (int)(floor(w/2)+offset_h),
		      (int)(floor(h/2)+offset_v),
		      radio, &blanco);
  return imagen;
}

CImg<float> calcular_magnitud_fft ( CImg<float> imagen, bool shift=true, bool log=true, bool normalize=true ) {
  CImgList<float> fft = imagen.get_FFT();
  CImg<float> magnitud = (fft[0].get_sqr() + fft[1].get_sqr()).sqrt();

   if (shift) magnitud.shift( (int)floor(imagen.width()/2), (int)floor(imagen.height()/2), 0, 0, 2);

   if (log) magnitud.log();

   if (normalize) magnitud.normalize(0,1);

  return magnitud;
}



int main(int argc, char *argv[]) {

  // if ( !argv[1] ){
  //   cout<<argv[0]<<": Ejercicio de Modelos de color.\n";
  //   cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;

  //   return 1;
  // }
 
  //

  CImg<float> linea_h = gen_linea_horizontal(),
    linea_v = gen_linea_vertical(),
    cuadrado_c = gen_rectangulo(),
    cuadrado_desc = gen_rectangulo(256,256,32,32,-100,-20),
    circulo_c = gen_circulo(),
    circulo_desc = gen_circulo(256,256,32,-80,50);





  //CImgList figuras( gen_linea_horizontal(), gen_linea_vertical() );
  //lineas.insert(lineas[0]))

  CImgList<float> lineas( linea_h, calcular_magnitud_fft(linea_h, 1, 0),
			  linea_v, calcular_magnitud_fft(linea_v, 1, 0) );
  lineas.display();

  CImgList<float> lineas_r( linea_h.rotate(30,1), calcular_magnitud_fft(linea_h, 1, 0),
			    linea_v.rotate(20,1), calcular_magnitud_fft(linea_v, 1, 0) );
  lineas_r.display();

  CImgList<float> cuadrados( cuadrado_c, calcular_magnitud_fft(cuadrado_c),
			     cuadrado_desc, calcular_magnitud_fft(cuadrado_desc) );
  cuadrados.display();

  CImgList<float> circulos( circulo_c, calcular_magnitud_fft(circulo_c),
			    circulo_desc, calcular_magnitud_fft(circulo_desc) );
  circulos.display();


  return 0;
}
