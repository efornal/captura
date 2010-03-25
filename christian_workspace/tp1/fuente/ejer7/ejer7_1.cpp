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

//porque no se ven como circulos!!!????
void generar_patron(int tamanio=3, int radio=0.5) {

	CImg<int> imagen(tamanio, tamanio, 1, 1, 1); //inicializamos los pixeles a 0 (fondo blanco)
	 int centro = (int) (abs(tamanio) / 2);

	 unsigned char color[]={0,0,0}; //color negro
	if (radio > centro ){
		radio = centro;
		imagen.draw_circle(centro, centro, abs(radio), color,1);

		imagen.display();

	} else { // dibujar con los parametros tal cual...
		imagen.draw_circle(centro, centro, abs(radio), color,1);
		imagen.display();

	}
}

void generar_mediostonos(CImg <unsigned char> imagen_tonodegrises){

}

int main(int argc, char *argv[]) {
	unsigned char negro[]={0,0,0};
	unsigned char blanco[]={255,0,0};
	generar_patron();

	/*float* ptr = image->ptr();
	cimg_forXYZ(S, x, y, z){
	    *ptr = *ptr + 10;
	    ++ptr;
	}*/


	return 0;
}
