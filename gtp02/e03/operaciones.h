#include <CImg.h>

using namespace cimg_library;
using namespace std;

CImg<unsigned char> suma( CImg<unsigned char> img1, CImg<unsigned char> img2 ) { 
    return (img1 + img2) / 2;
}
