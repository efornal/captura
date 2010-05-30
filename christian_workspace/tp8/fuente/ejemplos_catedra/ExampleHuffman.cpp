// ================== Example  ==========================
//
// This example uses "huffmanCodification()" from "HuffmanBinaryTreeOptimized.h"
// To execute, p.e.: 
// ./ExampleHuffman 50 15 36 14 
//
// Enrique Marcelo Albornoz
// Date: 2009-05-07
// Catedra de Procesamiento Digital de Im�genes
// Centro de I+D en Se�ales, Sistemas e Inteligencia Computacional (SINC),
// Dpto. Inform�tica, Facultad de Ingenier�a y Cs H�dricas,
// Universidad Nacional del Litoral, Santa Fe (Argentina)
// web: http://fich.unl.edu.ar/sinc/
//
// ==========================================================
#include <iostream>
#include "../lib8/HuffmanBinaryTreeOptimized.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc <= 3) {
		cout << endl
				<< "********************************************************************************"
				<< endl;
		cout
				<< "To execute, include an array of double with simbol probabilities or occurrences."
				<< endl;
		cout << "This array could be the image histogram." << endl;
		cout
				<< "To reproduce the example in page 543 from Gonzales & Woods (3rd Edition),"
				<< endl;
		cout << "Run: ./ExampleHuffman 0.1 0.4 0.06 0.1 0.04 0.3" << endl;
		cout << endl
				<< "********************************************************************************"
				<< endl;

	} else {
		double AvgWord, Entropy, CompRate;
		double SumAll = 0;
		int dSize = argc - 1;
		double data[dSize];
		string HuffmanInfo[dSize];

		for (int n = 0; n < dSize; n++) {
			data[n] = atof(argv[n + 1]);
			SumAll = SumAll + data[n];
		}

		huffmanCodification(data, HuffmanInfo, Entropy, AvgWord, CompRate,
				dSize);
		CompRate = (log(dSize) / log(2)) / AvgWord;

		// // // // // // // // // // // // // // // // // // // // // // // // // // // //
		// // //                     SHOW RESULTS
		// // // // // // // // // // // // // // // // // // // // // // // // // // // //
		for (int n = 0; n < dSize; n++) {
			cout << n << ":     initial value: " << data[n];
			cout << "     probability: " << (data[n] / SumAll);
			if (data[n] > 0) {
				cout << "     Huffman code: " << HuffmanInfo[n];
			}
			cout << endl;
		}
		cout << endl << "Entropy:             " << Entropy;
		cout << endl << "Average word length: " << AvgWord;
		cout << endl << "Compression Rate:    " << CompRate << endl << endl;
		// // // // // // // // // // // // // // // // // // // // // // // // // // // //
		// // // // // // // // // // // // // // // // // // // // // // // // // // // //
	}

	return (0);
}
