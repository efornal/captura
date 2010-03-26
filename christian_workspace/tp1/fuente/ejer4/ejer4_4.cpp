//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================
/*
 * cuando despliego las imagenes por separado parecen iguales aunque los valores no lo son
 * para que la matriz tome colores entre 0 y 255 si tiene valores de 100 x 100 hay que normalizarla?! conclusion
 * cuando los pongo en la lista se nota la diferencia .. que onda?
 * */
#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

bool generar_imagen(int tamanio, int radio) {
	//retorna true si los parametros fueron aceptados
	//retorna false si el radio y tamanio tuvieron que ajustarse para poder dibujarse

	CImg<int> imagen(tamanio, tamanio, 1, 1, 0); //inicializamos los pixeles a 0 (fondo negro)
	 int centro = (int) (abs(tamanio) / 2);

	 unsigned char color[]={255,0,0};
	if (radio > centro) {
		radio = centro;
		imagen.draw_circle(centro, centro, abs(radio), color,1);
		cout<<"OJO: Se adapto el radio del circulo!!!!!!!!";
		imagen.display();
		return false;
	} else { // dibujar con los parametros tal cual...
		imagen.draw_circle(centro, centro, abs(radio), color,1);
		imagen.display();
		return true;
	}
}

int main(int argc, char *argv[]) {
	generar_imagen(500,251);
	return 0;
}
