#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cerr<<"ERROR: No se ha especificado un archivo imagen.\n";
    cout<<argv[0]<<": Ensucia la imagen e intenta reducir el ruido promediando muchas imgs sucias.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    return 1;
  }

  CImg<float> original( argv[1] );

  CImgList<float> ensuciadas( 200, original );

  for ( short i=0; i<200; i++ )
    ensuciadas[i].noise(-10); //TODO el ruido tiene que ser normal/promedio 0/var 0.05 !!!

  CImgList<float> promediadas(5, original);

  srand(time(NULL));

  for (short i=1; i<5; i++)
    promediadas[i]=ensuciadas[(int)(200.0*rand()/(RAND_MAX+1.0))];


  for (short i=0; i<200; i++) {
    promediadas[4]+=ensuciadas[(int)(200.0*rand()/(RAND_MAX+1.0))];
    if ( i<100) {
      promediadas[3]+=ensuciadas[(int)(200.0*rand()/(RAND_MAX+1.0))];
      if( i<50 ) {
  	promediadas[2]+=ensuciadas[(int)(200.0*rand()/(RAND_MAX+1.0))];
  	if ( i<20 )
  	  promediadas[1]+=ensuciadas[(int)(200.0*rand()/(RAND_MAX+1.0))];
      }
    }
  }

 for (short i=0; i<5; i++)
   promediadas[i].normalize(0,255);

  promediadas.display("original, avg(20), avg(50), avg(100), avg(200)");

  return 0;
}

