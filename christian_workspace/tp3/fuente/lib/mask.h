/*
 * mask.h
 *
 *  Created on: 16/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

template<class T>

CImg<T> mascara3x3() {
	CImg<T> imagen;
	imagen(0, 0) = 1 * (1 / 9);
	imagen(0, 1) = 1 * (1 / 9);
	imagen(0, 2) = 1 * (1 / 9);
	imagen(1, 0) = 1 * (1 / 9);
	imagen(1, 1) = 1 * (1 / 9);
	imagen(1, 2) = 1 * (1 / 9);
	imagen(2, 0) = 1 * (1 / 9);
	imagen(2, 1) = 1 * (1 / 9);
	imagen(2, 2) = 1 * (1 / 9);
	return imagen;
}
