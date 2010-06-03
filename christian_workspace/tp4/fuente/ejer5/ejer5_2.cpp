/*
 * ejer5_2.cpp
 *
 *  Created on: 23/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../../../tp3/fuente/lib3/mask.h"
#include "../lib4/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	//a--------------------------------------------------------------------------------
	//generar una mascara de filtrado con suma 1
	CImg<float> mascara = generar_mascara_PA_suma1<float> (2);

	//b--------------------------------------------------------------------------------
	// cargar imagen y obtener componentes RGB
	CImg<float> camino("../../imagenes/camino.tif");
	CImgDisplay disp1(camino, "camino", 0);

	int dx = camino.width();
	int dy = camino.height();

	CImg<float> camino_R(dx, dy, 1, 3, 0.0), camino_G(dx, dy, 1, 3, 0.0), camino_B(dx,
			dy, 1, 3, 0.0);
	descomponer_rgb<float> (camino, camino_R, camino_G, camino_B, false);

	//c--------------------------------------------------------------------------------
	//procese casa componente por separado y genera una nueva imagen
	camino_R = camino_R.get_convolve(mascara);
	camino_G = camino_G.get_convolve(mascara);
	camino_B = camino_B.get_convolve(mascara);

	CImg<float> imagen_procesada = componer_imagen<float> (camino_R, camino_G,
			camino_B);
	CImgDisplay disp2(imagen_procesada,
			"imagen a la cual se le aplico la mascara por canales RGB");

	//d--------------------------------------------------------------------------------
	// obtener componentes HSI de la imagen original
	CImg<float> camino_HSI = camino.get_RGBtoHSI();
	CImg<float> camino_HSI_H = camino_HSI.get_channel(0);
	CImg<float> camino_HSI_S = camino_HSI.get_channel(1);
	CImg<float> camino_HSI_I = camino_HSI.get_channel(2);

	//e--------------------------------------------------------------------------------
	// filtrar compoennte de intensiddad y visualizar los resultados
	camino_HSI_I = camino_HSI_I.get_convolve(mascara);

	CImg<float> camino_filtrado_intensidad = (componer_imagen_hsi<float> (
			camino_HSI_H, camino_HSI_S, camino_HSI_I)).HSItoRGB();
	CImgDisplay
			disp3(
					camino_filtrado_intensidad,
					"imagen a la caul se le aplico la mascara en el canal de intensidada y se reconstruyo");
	/*POSTA: aplicar mascaras en imagenes de colores en HSI (en esta caso en intensidad)
	 * logra mejores resultados con la misma mascara no atenunando los tonos a diferencia de RGB.*/

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
