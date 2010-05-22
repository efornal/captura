#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/estanbul.tif",
                                         "ruta archivo imagen" );
    int umbral = cimg_option( "-u", 127, "umbral" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7, disp8;
    
    CImg<double> img ( filename ), gx, gy, gxy, gyx;
    img.channel(0);
    img.display(disp);

    gx = img.get_convolve( masks::prewite_gx() );

    gy = img.get_convolve( masks::prewite_gy() );

    gxy = img.get_convolve( masks::prewite_gxy() );

    gyx = img.get_convolve( masks::prewite_gyx() );

    CImgList<double> list ( gx, gy, gxy ,gyx );
    list.display(disp3);
    disp3.set_title("deteccion de bordes: prewite gx - gy - gxy - gyx");

    (gx+gy+gxy+gyx).normalize(0,255).display(disp4);
    disp4.set_title("deteccion de bordes: prewite gx + gy + gxy + gyx");

    CImgList<double> list2 ( gx.get_normalize(0,255).get_threshold( umbral ),
                             gy.get_normalize(0,255).get_threshold( umbral ),
                             gxy.get_normalize(0,255).get_threshold( umbral ),
                             gyx.get_normalize(0,255).get_threshold( umbral ) );

    list2.display(disp7);
    disp7.set_title("prewite umbral: gx - gy - gxy - gyx");

    CImgList<double> list3 ( masks::prewite_gx().resize(100,100),
                             masks::prewite_gy().resize(100,100),
                             masks::prewite_gxy().resize(100,100),
                             masks::prewite_gyx().resize(100,100) );
    list3.display(disp8);
    disp8.set_title("masks prewite: gx - gy - gxy - gyx");

    
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
