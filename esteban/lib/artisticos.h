#include <CImg.h>
#include <lut.h>

using namespace cimg_library;
using namespace std;

/**
 * retorna la imagen repujada.
 * @relieve si es interno=0 o externo=1
 * crea imagen -corrida- inicialmente en negro=0, entonces luego 
 * al sumar con la negada no afecta.
 * retorna la corrida negada y sumada con la original, repujada.
*/
CImg<unsigned char> repujado ( CImg<unsigned char> img, 
                               int dx=1, 
                               int dy=1, 
                               int relieve=1 ){
    CImg<unsigned char> corrida( img.width(), img.height(), 1, 1, 0 );
    cimg_forXY( img, x, y ){
        if ( ( (x+dx) < img.width() && (x+dx) >= 0 )
             && ( (y+dy) < img.height() && (y+dy) >= 0 ) ) {
            corrida( x+dx, y+dy ) = img(x,y); 
        }
    }
    if ( relieve == 1) {
        return lut( corrida, -1, 0 ) + img;
    } else {
        return lut( img, -1, 0 ) + corrida;
    }
}
