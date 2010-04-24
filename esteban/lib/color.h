#include <CImg.h>
#include <string>
#include <vector>
#include <CPDSI_functions.h>

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
