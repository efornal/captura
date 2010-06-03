/**
 * El objetivo del ejercicio es verificar la propiedad de convolucion
 * En continuo, la propiedad:
 *                      f * g = F . G
 * se verifica, pero en discreto, mediante la fft NO, ya que lo que hacemos
 * es la cirular:       f @ g = F . G
 *
 * Para calcular la conv lineal mediante la circular, hacemos el zero-padding
 *
 * -> x1      ->     x1z   ->   X1z  \         (ifft)
 *        (zero padd)     (fft)      -> X1z.X2z  ->  x1z @ x2z = x1 * x2
 * -> x2      ->     x2z   ->   X2z  /
 *
 */
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>

//#include "../lib5/lib5.h"
#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename1 =
			cimg_option( "-f1", "../../imagenes/clown.jpg",
					"ruta archivo imagen" );
	const char *filename2 =
			cimg_option( "-f2", "../../imagenes/clown.jpg",
					"ruta archivo imagen" );

	CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7;

	CImg<double> f(filename1), h(filename2);
	f.resize(101, 101); //f.resize(21,21);
	h.resize(101, 101); //h.resize(21,21);
	h = get_PB_gauss<double> (101, 101, 1.0);
	CImg<double> fz(f.width() * 2 - 1, f.height() * 2 - 1, 1, 1, 0), hz(
			h.width() * 2 - 1, h.height() * 2 - 1, 1, 1, 0);

	cimg_forXY(f,x,y)
			fz(x, y) = f(x, y);
	cimg_forXY(h,x,y)
			hz(x, y) = h(x, y);

	CImg<double> g = f.get_convolve(h);

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

	// (a+bi)(c+di) = (ac-bd)+(ad+bc)i = (f0.h0-f1.h1) + (f0.h1+f1.h0)i
	// si es por el conjugado:
	// (a+bi)(-c-di) = -ac -adi -cbi -bdi^2
	//      = -ac+bd -adi -cbi = (bd-ac)-(ad+bc)i = (f1.h1-f0h0)-(f0h1+f1h0)i

	CImgList<double> Fz = fz.get_FFT();
	CImgList<double> Hz = hz.get_FFT();
	CImgList<double> Gz(Fz[0], Fz[1]);

	Fz = realimag2magfase(Fz);
	Hz = realimag2magfase(Hz);

	cimg_forXY(Fz[0],x,y)
		{
			Gz[0](x, y) = Fz[0](x, y) * Hz[0](x, y);
			Gz[0](x, y) = 0;
		}

	Fz = magfase2realimag(Fz);
	Hz = magfase2realimag(Hz);

	CImg<double> g2z = Gz.get_FFT(true)[0].crop(0, 0, f.width() - 1, f.height()
			- 1);

	CImgList<double> list6(fz.get_normalize(0, 255),
			get_magnitud(fz, true).log().normalize(0, 255),
			get_fase(fz).normalize(0, 255));
	list6.display(disp6);
	disp6.set_title("fz - modulo log - fase");

	CImgList<double> list7(hz.get_normalize(0, 255),
			get_magnitud(hz, true).log().normalize(0, 255),
			get_fase(hz).normalize(0, 255));
	list7.display(disp7);
	disp7.set_title("hz - modulo log - fase");

	CImgList<double> list5(g2z.get_normalize(0, 255),
			get_magnitud(g2z, true).log().normalize(0, 255),
			get_fase(g2z).normalize(0, 255));
	list5.display(disp4);
	disp4.set_title("g2=f*h - modulo log - fase");

	while ((!disp.is_closed() && !disp.is_keyQ())) {
		disp.wait();
	}
	return 0;
}
