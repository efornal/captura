//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

//http://usuarios.multimania.es/explorar/halfto/halfto.htm
#include <CImg.h>
#include <iostream>
#include "../lib1/med_ton.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

	CImg<unsigned char> im1, im2, im3;
	im1.load("../../imagenes/huang1.jpg");
	im2.load("../../imagenes/huang2.jpg");
	im3.load("../../imagenes/huang3.jpg");
	CImgList<unsigned char> listaimg(im1, im2, im3);
	listaimg.display();
	pasar_a_medios_tonos(im1, 0).save("./huang1_not_resized.jpg").display("haung 1 sin reducir");
	pasar_a_medios_tonos(im2, 0).save("./huang2_not_resized.jpg").display("haung 2 sin reducir");
	pasar_a_medios_tonos(im3, 0).save("./huang3_not_resized.jpg").display("haung 3 sin reducir");

	pasar_a_medios_tonos(im1, 1).save("./huang1_resized.jpg").display("haung 1 reducida");
	pasar_a_medios_tonos(im2, 1).save("./huang2_resized.jpg").display("haung 2 reducida");
	pasar_a_medios_tonos(im3, 1).save("./huang3_resized.jpg").display("haung 3 reducida");

	return 0;
}
