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

		disp.set_title("reconstruccion");
	}

	//-------------------------------------------------------
	//TODO: esta provisorio.. ver como graficar de mejor forma esto:
	double ejex[8];
	double ejey[8]; // ejey[0] es el error en reconstruir la imagen con un solo plano el 0

	cout
			<< "LINEA PARA OCTAVE (0-1-2...) - cantidad de planos tomados para la reconstruccion, error cuadratico medio"
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

	cout << endl << endl
			<< "LINEA PARA OCTAVE (inverso 7-6-5....) - cantidad de planos tomados para la reconstruccion, error cuadratico medio"
			<< endl;
	cout << "plot([ ";
	for (int i = 0; i < 7; i++) {
		cout << ejex[i] << ", ";
	}
	cout << ejex[7] << " ], ";

	cout << "[ ";
	for (int i = 7; i > 0; i--) {
		ejey[7 - i] = imagen.MSE(get_until_plan(imagen, i, 7)); //ejey[0] va a tener el MSE con el plano 7 solo
		cout << ejey[i] << ", "; //ejey[1] va a tener el MSE con el plano 7+plano6..etc.
	}
	ejey[7] = imagen.MSE(get_until_plan(imagen, 0, 7));
	cout << ejey[7];
	cout << " ])";

	/* FIXME:
	 * ver el cout que hago en consola, copiar tal cual lo que tira donde dice Linea octave (inversa...) eso hace el grafico
	 * del error caudratico medio y la imagen en x=0 del grafico esta el error cuadratico medio de reconstruccion solo con el
	 * plano 7 (bit mas significativo)
	 * notar que da 0 --> usando 1 solo plano (el mas significativo da 0! porque???)
	 * en x=1 del grafico esta el MSE de la reconstruccion entre la imagen original y los planos 7+6 y asi sucesivamente...
	 *  porque cuando sumo los planos 7+6+5+4 segun la grafica el error cuadratico medio vuelve a ser cero??
	 *
	 *  TODO: Conceptualmente no debe dar así, correcto? El error cuadrático no puede ser cero salvo que sea la misma imagen.
	 *  Debe haber un error, proba haciendo el MSE a pata en un pedacito chiquito de la imagen donde puedas conocer los valores
	 *  y hacer a pata el cálculo.
	 * */

	return 0;
}
