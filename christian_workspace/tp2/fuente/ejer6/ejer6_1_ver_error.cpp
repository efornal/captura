/*
 * ejer6_1_reconstruccion.cpp
 *
 *  Created on: 07/04/2010
 *      Author: christian
 */
#include <iostream>
#include <stdio.h>
#include <CImg.h>
#include "../lib/lib.h"
#include "../lib/plano_bit.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	CImg<unsigned char> imagen;
	imagen.load("../../imagenes/huang.jpg");

	CImgDisplay disp0(imagen, "imagen original", 1); // el 1 es para que normalice.


	//	cout << endl << "Plano: " << plano<<endl;
	CImg<unsigned char> resultado(imagen);
	resultado.fill(0);

	int plano_inicial = 0;
	int plano_final = 0;
	resultado = get_until_plan(imagen, plano_inicial, plano_final);
	cout << "Reconstruccion desde plano: " << plano_inicial
			<< "  hasta el plano: " << plano_final << endl;
	CImgDisplay disp(resultado, "Reconstruccion", 1);
	while (!disp.is_closed() && !disp.is_keyQ()) {
		disp.wait();
		if (disp.is_keyARROWUP() && plano_final < 7) { //aumentar plano bits
			resultado = get_until_plan(imagen, plano_inicial, ++plano_final);
		} else if (disp.is_keyARROWDOWN() && plano_final > 0) {
			resultado = get_until_plan(imagen, plano_inicial, --plano_final);
		}
		cout << "Reconstruccion desde plano: " << plano_inicial
				<< "  hasta el plano: " << plano_final << endl;
		resultado.display(disp);

		/* TODO: ver el error cuadratico entre la imagen original y la reconstruida en funcion de la cantidad de
		 * planos con los que se va reconstruyendo la imagen
		 * */

		disp.set_title("reconstruccion");
	}
	/* FIXME:tuve que hacerlo con la funcion que obtiene la reconstruccion desde el plano 0... o sea hacer un for siempre. no
	 * es que la obtiene simplemente anadiendole un termino o elimnando otro (sumando y restando respectivamente) porque
	 * si lo hacia de esa manera no me andaba del _todo bien y aveces quedaba una cosa y aveces otra.. se debera a los
	 * decimales de la potenciacion?
	 * */

	//-------------------------------------------------------
	//TODO: esta provisorio.. ver como graficar de mejor forma esto:
	double ejex[8];
	double ejey[8]; // ejey[0] es el error en reconstruir la imagen con un solo plano el 0

	cout
			<< "LINEA PARA OCTAVE - cantidad de planos tomados para la reconstruccion, error cuadratico medio"
			<< endl;
	cout << "plot([ ";
	for (int i = 0; i < 7; i++) {
		ejex[i] = i;
		cout << ejex[i] << ", ";
	}
	ejex[7] = 7;
	cout << ejex[7] << " ], ";

	cout << "[ ";
	for (int i = 0; i < 7; i++) {
		ejey[i] = imagen.MSE(get_until_plan(imagen, 0, i));
		cout << ejey[i] << ", ";
	}
	ejey[7] = imagen.MSE(get_until_plan(imagen, 0, 7));
	cout << ejey[7];
	cout << " ])";

	cout<<endl<<endl<<"LINEA PARA OCTAVE (inverso) - cantidad de planos tomados para la reconstruccion, error cuadratico medio"<<endl;
	cout << "plot([ ";
	for (int i = 0; i < 7; i++) {
		cout << ejex[i] << ", ";
	}
	cout << ejex[7] << " ], ";

	cout << "[ ";
	for (int i = 7; i > 0; i--) {
		ejey[7-i] = imagen.MSE(get_until_plan(imagen, i, 7));
		cout << ejey[i] << ", ";
	}
	ejey[7] = imagen.MSE(get_until_plan(imagen, 0, 7));
	cout << ejey[7];
	cout << " ])";

	//system("octave");
	//imagen.MSE(resultado);

/*
	FILE *archivo;El manejador de archivo
	     archivo=fopen("error_uno.m", "w");
	     if(archivo==NULL)So no lo logramos abrir, salimos
	        return 1;
	     fprintf(archivo, "Hola, mundo\n");Escribimos en el archivo
	     fclose(archivo);//Cerramos el archivo
*/

	return 0;
}
