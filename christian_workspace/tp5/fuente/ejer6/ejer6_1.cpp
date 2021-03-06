/*
 * ejer6_1.cpp
 *
 *  Created on: 16/05/2010
 *      Author: christian
 */
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>

#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;
/**
 * El objetivo del ejercicio es verificar la propiedad de convolucion
 * En continuo, la propiedad:
 *                      f * g = F . G
 * se verifica, pero en discreto, mediante la fft NO, ya que lo que hacemos
 * es la cirular:       f @ g = F . G
 * para verificarlo, convolucionamos una imagen con un filtro (o dos imagenes)
 * 1- obtenemos f * h = g
 * 2- F = fft(f)    \
 *    H = fft(h)    / =>  ifft(F.H)  =   g2  distinto de  g
 *                          (porq no se cumple la prop. de conv)
 *
 * FIXME: Como hariamos si f distinto tamaño que h ?? en la convolucion
 * andaria, pero para obtener en frecuencia???
 */
int main(int argc, char **argv) {

	const char *filename1 = cimg_option( "-f1", "../../imagenes/clown.jpg",
			"ruta archivo imagen" );
	const char *filename2 = cimg_option( "-f2", "../../imagenes/clown.jpg",
			"ruta archivo imagen" );

	CImgDisplay disp, disp2, disp3, disp4, disp5;

	CImg<double> f(filename1), h(filename2);
	f.resize(101, 101); //f.resize(21,21);
	h.resize(101, 101); //h.resize(21,21);

	CImg<double> g = f.get_convolve(h);

	f.print("f");
	h.print("h");
	g.print("g");

	CImgList<double> list1(f.get_normalize(0, 255),
			get_magnitud(f, true).log().normalize(0, 255),
			get_fase(f).normalize(0, 255));
	list1.display(disp);
	disp.set_title("f - modulo log - fase");

	CImgList<double> list2(h.get_normalize(0, 255),
			get_magnitud(h, true).log().normalize(0, 255),
			get_fase(h).normalize(0, 255));
	list2.display(disp2);
	disp2.set_title("h - modulo log - fase");

	CImgList<double> list3(g.get_normalize(0, 255),
			get_magnitud(g, true).log().normalize(0, 255),
			get_fase(g).normalize(0, 255));
	list3.display(disp3);
	disp3.set_title("g=f*h - modulo log - fase");

	CImgList<double> F = f.get_FFT();
	CImgList<double> H = h.get_FFT();
	CImgList<double> G(F[0], F[1]);
	cimg_forXY(F[0],x,y)
		{
			G[0](x, y) = F[0](x, y) * H[0](x, y);
			G[1](x, y) = F[1](x, y) * H[1](x, y);
		}
	CImg<double> g2 = G.get_FFT(false)[0];

	CImgList<double> list5(g2.get_normalize(0, 255),
			get_magnitud(g2, true).log().normalize(0, 255),
			get_fase(g2).normalize(0, 255));
	list5.display(disp4);
	disp4.set_title("g2=f*h - modulo log - fase");

	while ((!disp.is_closed() && !disp.is_keyQ())) {
		disp.wait();
	}
	return 0;

}

