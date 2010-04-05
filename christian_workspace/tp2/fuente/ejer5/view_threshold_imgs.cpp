/*
 * view_threshold.cpp
 *
 *  Created on: 05/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../ejer1/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	 CImg<unsigned char> img1("../../imagenes/letras2.tif");
	    CImgDisplay disp, disp2, disp3;
	    int cont = 0;

	    img1.display(disp);
	    img1.get_threshold(127).normalize(0,255).display(disp2);

	    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
	        disp.wait();

	        if (cont > 127) cont = 127;
	        if (cont < -127) cont = -127;

	        if (  disp.is_keyARROWDOWN() ) {
	            img1.get_threshold((cont--)+127).normalize(0,255).display(disp2);
	        } else if (  disp.is_keyARROWUP() ) {
	            img1.get_threshold((cont++)+127).normalize(0,255).display(disp2);
	        }
	        cout<<"Threshold: "<<cont<<endl;
	    }
return 0;
}
