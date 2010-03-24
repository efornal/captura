//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	const char *filename =
			"/home/christian/Documentos/universidad/2010/captura/imagenes/huang.jpg";
	/*CImg<char>
	 original_image(
	 "/home/christian/Documentos/universidad/2010/captura/imagenes/huang.jpg"); //cargo imagen*/


	CImg<float> imagen(filename);
	imagen.channel(0); //canal 0
	imagen.crop(37, 14, 52, 32, false);

	string ext[6] = { "img.jpg", "img.tif", "img.gif", "img.png", "img.bmp" };
	CImg<char> temp;

	for (int i = 0; i < 5; ++i) {
		imagen.save(ext[i].c_str()); //grabo imagenes en disco
		temp.clear();
		temp.load(ext[i].c_str());
		cout << ext[i] << ": size: " << temp.size() << ":::: Height: "
				<< temp._height << ":::: Width: " << temp._width
				<< ":::: depth: " << temp._depth << "" << ":::: Spectrum: "
				<< temp._spectrum << endl; // esta clarisimo en la salida que la bmp usa 3 veces mas!
	}
	cout << endl
			<< "Ancho x Alto x Spectrum +54 de cabecera= tamanio en bytes de la imagen bmp: "
			<< temp.size() + 54;
	CImgDisplay vent1(imagen, "cropeada");
	while (!vent1.is_closed()) {
	}

	return 0;
}
