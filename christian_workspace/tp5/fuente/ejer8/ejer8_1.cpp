#define cimg_use_fftw3
#include <CImg.h>

#include <algorithm>

#ifdef cimg_use_fftw3
extern "C" {
#include <fftw3.h>
}
#endif

#include "../lib5/filtros.h"
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

	const char *i1 = cimg_option( "-f", "../../imagenes/camaleon.tif", "imagen 1" );
	double a = cimg_option( "-a", 1.0, "parametro a de filtro EAF" );
	double b = cimg_option( "-b", 5.0, "parametro b de filtro EAF" );
	double A = cimg_option( "-A", 4.0, "parametro A de filtro AP" );
	double frec_corte =
			cimg_option( "-frec_corte", 30.0, "frec corte del filtro butter" );
	double orden = cimg_option( "-orden", 6.0, "orden del filtro butter" );

	CImg<double> imag(i1);

	CImg<double> filtro = aplicar_filtro_eaf(get_PA_Butter<double> (
			imag.width(), imag.height(), frec_corte, orden), a, b);

	CImg<double> filtroap = aplicar_filtro_alta_potencia(
			get_PA_Butter<double> (imag.width(), imag.height(), frec_corte,
					orden), A);

	CImgList<double> (imag.normalize(0, 1),
			filtrar_M<double> (imag, filtro).normalize(0, 1)).display(
			"imagen original / imagen filtrada ENFASIS DE ALTA FRECUENCIA");

	CImgList<double> (imag.normalize(0, 1),
			filtrar_M<double> (imag, filtroap).normalize(0, 1)).display(
			"imagen original / imagen filtrada ALTA POTENCIA");
	return 0;
}
