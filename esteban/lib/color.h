#define pdi_color 1

#include <CImg.h>
#include <string>
#include <vector>
#include <math.h>

#ifndef MAX_LINE_LENGTH
#include <CPDSI_functions.h>
#endif

using namespace std;
using namespace cimg_library;

/**
 * carga una paleta con nombre_paleta la aplica a la imagen 
 *pasada como parametro y devuelve la imagen con la paleta aplicada
 * @paleta=1 -> paletas/bone.pal
 * @paleta=2 -> paletas/cool.pal
 * @paleta=3 -> paletas/copper.pal
 * @paleta=4 -> paletas/gray.pal
 * @paleta=5 -> paletas/hot.pal
 * @paleta=6 -> paletas/hsv.pal
 * @paleta=7 -> paletas/jet.pal
 * @paleta=8 -> paletas/pink.pal
 */
CImg<float> aplicar_paleta(CImg<float> img, int nro_paleta=1) {
    vector< vector<float> > paleta;
    switch ( nro_paleta ) {
    case 1: cargar_paleta (paleta, "../../lib/paletas/bone.pal");   break;
    case 2: cargar_paleta (paleta, "../../lib/paletas/cool.pal");   break;
    case 3: cargar_paleta (paleta, "../../lib/paletas/copper.pal"); break;
    case 4: cargar_paleta (paleta, "../../lib/paletas/gray.pal");   break;
    case 5: cargar_paleta (paleta, "../../lib/paletas/hot.pal");    break;
    case 6: cargar_paleta (paleta, "../../lib/paletas/hsv.pal");    break;
    case 7: cargar_paleta (paleta, "../../lib/paletas/jet.pal");    break;
    case 8: cargar_paleta (paleta, "../../lib/paletas/pink.pal");   break;
    default: break;
    }

    CImg<float> result( img.width(), img.height(), 1, 3 );
    cimg_forXY( img, x, y) {
        result (x, y, 0, 0) = paleta[(int)img(x, y)][0]; //canal rojo
        result (x, y, 0, 1) = paleta[(int)img(x, y)][1]; //canal verde
        result (x, y, 0, 2) = paleta[(int)img(x, y)][2]; //canal azul
    }
    return result;
}

/**
 * toma la distancia entre dos puntos 3D
 * usado para segmentacion de color, esfera.
 */
int distancia (int x0, int y0, int c0, int x1, int y1, int c1){
    int x=(x0-x1), y(y0-y1), c=(c0-c1);
    return sqrt(x*x + y*y + c*c);
}

/**
 * genera una mascara binaria de la imagen en RGB
 * tomando la poisicion del punto x0,y0 (de la imagen)
 * para obtener las coordenadas RGB de la imagen:
 * img(x0,y0,0) = R
 * img(x0,y0,1) = G
 * img(x0,y0,2) = B
 * donde P=(R,G,B) representa el punto en el cubo 3D 
 * del modelo RGB
*/
CImg<unsigned char> gen_mascara_segmentacion_rgb( CImg<unsigned char> img, 
                                              int x0, int y0,
                                              int radio ){
    CImg<unsigned char> mask ( img.width(), img.height(), 1, 1, 0 );
    cimg_forXY( img,x,y){
        mask(x,y,0,0) = ( distancia (img(x0,y0,0,0),
                                     img(x0,y0,0,1),
                                     img(x0,y0,0,2),
                                     img(x,y,0,0),
                                     img(x,y,0,1),
                                     img(x,y,0,2) ) > radio ) ? 0 : 1; 
    }
    return mask;
}

