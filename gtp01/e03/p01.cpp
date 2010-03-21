/*
  CImg ( dx, dy, dz, dc, T val)
    dx Desired size along the X-axis, i.e. the width of the image.
    dy Desired size along the Y-axis, i.e. the height of the image.
    dz Desired size along the Z-axis, i.e. the depth of the image.
    dc Desired size along the C-axis, i.e. the number of image channels spectrum.
    val Default value for image pixels.
  FIXME: tomar un canal de una imagen de varios canales no significa que esa imagen
    va a ser de intensidad?
*/

#include <CImg.h>

using namespace cimg_library;

int main() {
    CImg<unsigned char> img1(400,200,1,1);
    img1.display("Imagen de intensidad");

    CImg<unsigned char> img2("../../imagenes/earth.bmp");
    img2.display("Imagen de archivo");

    CImg<unsigned char> img3("../../imagenes/earth.bmp");
    img3.channels(0,0);
    img3.display("Imagen de intensidad de archivo - un canal");

    return 0;
}
