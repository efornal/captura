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
	const char *filename = "/home/christian/Documentos/universidad/2010/captura/git_repo/captura/christian_workspace/tp1/img.jpg";
CImg <float> imagen;
imagen.load(filename);
imagen.display(); //tira info de lox pixels y demas

CImgDisplay ventana(imagen, "imagen"); //conserva el tamanio y no tira informacion alguna

//CImg <char> imagen(filename);
//CImgDisplay ventana(imagen, "earth");

/*CImgDisplay vent1(imagen, "imagen 0"), vent2(imagen1, "imagen 1"), vent3(
 imagen2, "imagen 2");*/
 while (!ventana.is_closed()) {
 }

return 0;
}
