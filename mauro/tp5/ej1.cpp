#define UNICODE
#include <CImg.h>
#include <iostream>
#include "comun.cpp"


using namespace cimg_library;
//using namespace std;

int main(int argc, char *argv[]) {

  CImg<float> linea_h = gen_linea_horizontal<float>(),
    linea_v = gen_linea_vertical<float>(),
    cuadrado_c = gen_rectangulo<float>(),
    cuadrado_desc = gen_rectangulo<float>(256,256,32,32,-100,-20),
    circulo_c = gen_circulo<float>(),
    circulo_desc = gen_circulo<float>(256,256,32,-80,50);


  CImgList<float> lineas( linea_h, calcular_magnitud_fft(linea_h, 1, 0),
			  linea_v, calcular_magnitud_fft(linea_v, 1, 0) );
  lineas.display("horizontal / TDF horizontal / vertical / TDF vertical");

  linea_h.rotate(30,1);
  float borde = (linea_h.width()-256)/2.0;
  linea_h.crop( borde, borde, linea_h.width()-borde-1, linea_h.height()-borde-1);

  linea_v.rotate(20,1);
  borde = (linea_v.width()-256)/2.0;
  linea_v.crop( borde, borde, linea_v.width()-borde-1, linea_v.height()-borde-1);


  CImgList<float> lineas_r( linea_h, calcular_magnitud_fft(linea_h, 1, 0),
			    linea_v, calcular_magnitud_fft(linea_v, 1, 0) );
  lineas_r.display("h rotada 30° / TDF / v rotada 20° / TDF");

  CImgList<float> cuadrados( cuadrado_c, calcular_magnitud_fft(cuadrado_c),
			     cuadrado_desc, calcular_magnitud_fft(cuadrado_desc) );
  cuadrados.display("cuadrado centrado / TDF centrado / descentrado / TDF descentrado");

  CImgList<float> circulos( circulo_c, calcular_magnitud_fft(circulo_c),
			    circulo_desc, calcular_magnitud_fft(circulo_desc) );
  circulos.display("circulo centrado / TDF centrado / descentrado / TDF descentrado");


  return 0;
}
