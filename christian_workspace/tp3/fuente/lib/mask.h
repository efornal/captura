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
	CImg<T> imagen (3,3,1,1);
	imagen(0, 0) = 1 * (1 / 9.0);
	imagen(0, 1) = 1 * (1 / 9.0);
	imagen(0, 2) = 1 * (1 / 9.0);
	imagen(1, 0) = 1 * (1 / 9.0);
	imagen(1, 1) = 1 * (1 / 9.0);
	imagen(1, 2) = 1 * (1 / 9.0);
	imagen(2, 0) = 1 * (1 / 9.0);
	imagen(2, 1) = 1 * (1 / 9.0);
	imagen(2, 2) = 1 * (1 / 9.0);
	return imagen;
}

template <class T>
CImg<T> mascara3x3_no_simetrica() {
	CImg<T> imagen (3,3,1,1);
	imagen(0, 0) = 1 * (1 / 10.0);
	imagen(0, 1) = 2 * (1 / 10.0);
	imagen(0, 2) = 1 * (1 / 10.0);
	imagen(1, 0) = 1 * (1 / 10.0);
	imagen(1, 1) = 1 * (1 / 10.0);
	imagen(1, 2) = 1 * (1 / 10.0);
	imagen(2, 0) = 1 * (1 / 10.0);
	imagen(2, 1) = 1 * (1 / 10.0);
	imagen(2, 2) = 1 * (1 / 10.0);
	return imagen;
}
