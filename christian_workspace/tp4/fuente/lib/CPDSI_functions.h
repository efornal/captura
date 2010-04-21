/***************************************************************************
 *            CPDSI_functions
 *
 *  2008 / 02 / 20
 *  Cesar Martinez - cmartinez@bioingenieria.edu.ar
 *  Monica Larese  - mlarese@ifir.edu.ar
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "CImg.h"

using namespace std;
using namespace cimg_library;
///****************************************
///        Definiciones generales
///****************************************
#define MAX_LINE_LENGTH 16384
char linea[MAX_LINE_LENGTH];
const int NFilas256=256, NColumnas256=256;



///****************************************
/// Transformada Hough directa
/// Todavia no funciona el cuantizado del plano ro-theta
///****************************************
CImg<double> hough_directa(CImg<double> img, double dtita=1, double dro=1, bool getHist=0) {

  CImg<double> iHough(img); iHough.fill(0.0);
  const unsigned width  = img.width();
  const unsigned height = img.height();

  double scale_rho = height/(2*sqrt(pow(float(height),2)+pow(float(width),2))),
         scale_theta = width/M_PI,
         rho, theta;

  cout << "Calculando la transformada Hough..." << endl;
  for (unsigned y=0; y < height; y++)
    for (unsigned x=0; x < width; x++)
      if (img(x,y) > 0.5)
         for (unsigned t=0; t < width; t++) {
          theta=t/scale_theta-M_PI/2;
          rho=x*cos(theta)+y*sin(theta);
          unsigned r=(unsigned)(rho*scale_rho+height/2.);
          iHough(t,r)+= 1;
         }
  cout << "...listo!" << endl;
  return iHough;
}



///****************************************
/// Transformada Hough inversa
///****************************************
CImg<double> hough_inversa(CImg<double> img) {

  const double color[] = {255.f, 0.0f, 0.0f};
  CImg<double> iHoughI(img); iHoughI.fill(0.0);
  int width  = img.width(), height = img.height(),
      y0, y1;

  double scale_rho = height/(2*sqrt(pow(float(height),2)+pow(float(width),2))),
         scale_theta = width/M_PI,
         rho, theta;

  cout << "Calculando la transformada Hough inversa..." << endl;
  for (unsigned b=0; b < height; b++)
    for (unsigned a=0; a < width; a++)
      if (img(a,b) > 0.5) {
          theta=a/scale_theta-M_PI/2;
          y0=(int)(((b-(height/2.))/scale_rho)/sin(theta)); // -0/tan(theta));
          y1=(int)(((b-(height/2.))/scale_rho)/sin(theta)-width/tan(theta));
          iHoughI.draw_line(0,(int)y0,(int)width,(int)y1,color);
         }
  cout << "...listo!" << endl;
  return iHoughI;
}



///****************************************
/// Gaussian filter mask
///****************************************
CImg<double> gaussian_mask(int size, double sigma){
int ini,fin;
double aux;
CImg<double> mask(size,size);
int x,y;
 const double pi=3.14159;
ini=(int)(-1)*(size-1)/2;
fin=(int)(size-1)/2;
for (x=ini;x<fin+1;x++){
    for (y=ini;y<fin+1;y++){
        aux=((double)(x*x)+(double)y*y)/(2*sigma*sigma);
        mask(x-ini,y-ini)=1/(2*pi*sigma*sigma)*exp(-1*aux);
    }
}
CImg<> stats=mask.get_stats();
for (x=0;x<size;x++){
    for (y=0;y<size;y++){
        if (mask(x,y)<10e-5*stats(0,2)){
            mask(x,y)=0;
        }
    }
}
mask/=mask.sum();
return mask;
}



///****************************************
/// Laplacian of Gaussian filter mask
///****************************************
CImg<double> LoG_mask(int size, double sigma){
int ini,fin;
double r2;
CImg<double> mask(size,size);
int x,y;
ini=(int)(-1)*(size-1)/2;
fin=(int)(size-1)/2;
for (x=ini;x<fin+1;x++){
    for (y=ini;y<fin+1;y++){
        r2=(double)(x*x+y*y);
        mask(x-ini,y-ini)=1.0*(r2-2*pow(sigma,2))/pow(sigma,4)*exp(-1.0*r2/(2*pow(sigma,2)));
    }
}
mask/=mask.sum();
return mask;
}



///****************************************
/// Filtro ideal
///****************************************
void generar_filtro_ideal256(float m[][NFilas256], int R) {
	for (int i=0; i<NColumnas256; i++)
		for (int j=0; j<NFilas256; j++)
			if (sqrt(pow(double(i-NColumnas256/2),2)+pow(double(j-NFilas256/2),2))<R)
				m[i][j]=1;
			else m[i][j]=0;
}


///****************************************
/// Cargar paleta
///****************************************
int cargar_paleta(vector< vector< float> > &paleta, string nombre) {
	vector< float > plinea;
	string cad, rS, gS, bS;
	float r, g, b;
	int pos, nval;

	ifstream arch(nombre.c_str());
	if (arch.fail()) {
    	cerr << "ERROR al abrir el archivo " << nombre << endl;
		return 1;
	} else {
	paleta.clear();
	// lee cuantos valores por fila
	getline(arch,cad);
	nval=0;
	pos=cad.find_first_of(".");
	while (pos>0) {
		cad.erase(0,pos+1);
		pos=cad.find_first_of(".");
		nval++;
	}
	arch.close();
	arch.open(nombre.c_str());
	plinea.resize(nval);
	while (getline(arch,cad)) {
		pos=cad.find_first_not_of(" ");
		cad.erase(0,pos);
		pos=cad.find_first_of(" ");
		rS=cad.substr(0,pos);
		r=atof(rS.c_str());
		plinea[0]=r;
		cad.erase(0,pos);
		pos=cad.find_first_not_of(" ");
		cad.erase(0,pos);
		pos=cad.find_first_of(" ");
		gS=cad.substr(0,pos);
		g=atof(gS.c_str());
		plinea[1]=g;
		cad.erase(0,pos);
		pos=cad.find_first_not_of(" ");
		cad.erase(0,pos);
		pos=cad.find_first_of(" ");
		bS=cad.substr(0,pos);
		b=atof(bS.c_str());
		plinea[2]=b;
		paleta.push_back(plinea);
	}
	arch.close();
	return 0;
 }
}


///****************************************
/// Magnitud de la TDF transformada logaritmicamente
///****************************************
/*void magn_tdf(CImg<double> image,CImg<unsigned char> &magnitud_tdf,bool centrada){
CImgList<double> tf=image.get_FFT(false);  // lista con 2 imagenes: parte real e imaginaria
CImg<double> preal=tf[0], pimag=tf[1]; // partes separadas
int nn=preal.width();
int mm=preal.height();
CImg<double> magnitud(nn,mm), magnitud_paleta(nn,mm,1,3,0);
vector< vector< float> > paleta;
for (int i=0; i<nn; i++){
    for (int j=0; j<mm; j++) {
        magnitud(i,j)=log(sqrt(pow(double(preal(i,j)),2)+pow(double(pimag(i,j)),2.))+0.000001);
    }
}
magnitud.normalize(0,255);
if (centrada){
    (magnitud).translate(magnitud.width()/2,magnitud.height()/2,0,0,2); //parametros de scroll:x,y,z,v,border_condition
}
//DEVUELVE LA TDF CON LA PALETA DESEADA
if (cargar_paleta(paleta,"../CPDSI_functions/gray.pal")!=0){
    cout<<"Error al cargar la paleta."<<endl;
    exit(1);
}
for (int i=0; i<nn; i++){
    for (int j=0; j<mm; j++) {
	magnitud_paleta(i,j,0,0)=int(255*paleta[int(floor(magnitud(i,j)))][0]);
	magnitud_paleta(i,j,0,1)=int(255*paleta[int(floor(magnitud(i,j)))][1]);
	magnitud_paleta(i,j,0,2)=int(255*paleta[int(floor(magnitud(i,j)))][2]);
    }
}
magnitud_tdf=magnitud_paleta;
}*/



double MSError(CImg<float> A,CImg<float> B){
float suma=0;
CImg<float> Error(A.width(),A.height());
int i,j;
for(i=0;i<A.width();i++){
 for(j=0;j<A.height();j++){
  Error(i,j)=pow(( A(i,j)- B(i,j)),2);
  suma=suma+Error(i,j);
 }
}
return suma/(A.width()*A.height());
}

double MSError(CImg<double> A,CImg<double> B){
double suma=0;
CImg<double> Error(A.width(),A.height());
int i,j;
for(i=0;i<A.width();i++){
 for(j=0;j<A.height();j++){
  Error(i,j)=pow(( A(i,j)- B(i,j)),2);
  suma=suma+Error(i,j);
 }
}
return suma/(A.width()*A.height());
}

double MSError(CImg<unsigned char> A,CImg<unsigned char> B){
double suma=0;
CImg<double> Error(A.width(),A.height());
for(int i=0;i<A.width();i++){
 for(int j=0;j<A.height();j++){
  Error(i,j)=(double) pow(((double) A(i,j)- (double)B(i,j)),2);
  suma=suma+Error(i,j);
 }
}
return suma/(A.width()*A.height());
}

///**********************************************************************
/// Muestra una imagen en 3D, tomando la intensidad como la componente z
/// Advertencia! El eje z aparece invertido
///**********************************************************************
// // void draw_3D_image(CImg<unsigned char> imagen){
// //   // Read command line arguments
// //   const float sigma = 1.0f;
// //   const float ratioz = 0.25f;
// //   const unsigned int di = 10;
// //
// //   // Init data
// //   const CImg<unsigned char> img = imagen.blur(sigma).resize(-100,-100,1,3);
// //   const CImg<int> norm = img.get_pointwise_norm().normalize(0,255);
// // //   const CImg<unsigned char> norm = img.get_pointwise_norm().normalize(0,255);
// //   CImgList<> points, isopoints;
// //   CImgList<unsigned int> primitives, isoprimitives;
// //   CImgList<unsigned char> colors, isocolors;
// //
// //   // Compute surface with isophotes
// //   std::fprintf(stderr,"\n- Compute isophotes"); std::fflush(stderr);
// //   CImgList<unsigned int> lpoints;
// //   for (unsigned int i=0; i<255; i+=di) norm.marching_squares((float)i,lpoints,isoprimitives);
// // //   for (unsigned int i=0; i<255; i+=di) norm.marching_squares((float)i,lpoints,isoprimitives);
// //   cimglist_for(isoprimitives,l) {
// //     const unsigned int i0 = isoprimitives(l,0);
// //     const float x0 = lpoints(i0,0), y0 = lpoints(i0,1);
// //     const unsigned char
// //       r = (unsigned char)img.linear_atXY(x0,y0,0),
// //       g = (unsigned char)img.linear_atXY(x0,y0,1),
// //       b = (unsigned char)img.linear_atXY(x0,y0,2);
// // //       b = (unsigned char)img.linear_pix2d(x0,y0,2);
// //     isocolors.insert(CImg<unsigned char>::vector(r,g,b));
// //   }
// //   isopoints = lpoints.get_append('x').resize(-100,3,1,1,0).get_split('x');
// //   cimglist_for(isopoints,ll) isopoints(ll,2) = -ratioz*norm.linear_atXY(isopoints(ll,0),isopoints(ll,1));
// //
// //   // Compute surface with triangles
// //   std::fprintf(stderr,"\n- Create image surface"); std::fflush(stderr);
// //   const unsigned int w = img.width+1, h = img.height+1;
// //   points.assign(w*h,3);
// //   cimg_forXY(img,x,y) {
// //     points(x+y*w,0) = points(x+1+y*w,0) = points(x+1+(y+1)*w,0) = points(x+(y+1)*w,0) = (float)x;
// //     points(x+y*w,1) = points(x+1+y*w,1) = points(x+1+(y+1)*w,1) = points(x+(y+1)*w,1) = (float)y;
// //     points(x+y*w,2) = points(x+1+y*w,2) = points(x+1+(y+1)*w,2) = points(x+(y+1)*w,2) = -ratioz*norm(x,y);
// //     const unsigned int
// //       i0 = x + y*w, i1 = (x+1) + y*w,
// //       i2 = (x+1) + (y+1)*w, i3 = x + (y+1)*w;
// //     primitives.insert(CImg<unsigned int>::vector(i0,i1,i2,i3));
// //     const unsigned char
// //       r = (unsigned char)img(x,y,0),
// //       g = (unsigned char)img(x,y,1),
// //       b = (unsigned char)img(x,y,2);
// //     colors.insert(CImg<unsigned char>::vector(r,g,b));
// //   }
// //
// //   // Enter event loop
// //   std::fprintf(stderr,
// // 	       "\n- Enter interactive loop.\n\n"
// // 	       "Reminder : \n"
// // 	       " + Use mouse to rotate and zoom object\n"
// // 	       " + key 'F' : Toggle fullscreen\n"
// // 	       " + key 'Q' : Quit\n"
// // 	       " + Any other key : Change rendering type\n\n"); std::fflush(stderr);
// //   const char *const title = "Image viewed as a surface";
// //   CImgDisplay disp(800,600,title,0);
// //   unsigned int rtype = 2;
// //   CImg<float> pose = CImg<float>::identity_matrix(4);
// //
// //   while (!disp.is_closed) {
// //     const unsigned char white[3]={255,255,255};
// //     CImg<unsigned char> visu(disp.width(), disp.height(),1,3,0);
// //      visu.draw_text(10,10,white,0,19,1.0f,"Render : %s",
// // 		rtype==0?"Points":(rtype==1?"Lines":(rtype==2?"Faces":(rtype==3?"Flat-shaded faces":
// // 	       (rtype==4?"Gouraud-shaded faces":(rtype==5?"Phong-shaded faces":"Isophotes"))))));
// //     if (rtype==6) visu.display_object3d(isopoints,isoprimitives,isocolors,disp,true,1,-1,true,500.0f,0.05f,true,pose.ptr());
// //     else visu.display_object3d(points,primitives,colors,disp,true,rtype,-1,true,500.0f,0.05f,true,pose.ptr());
// //     switch (disp.key) {
// //     case 0: break;
// //     case cimg::keyBACKSPACE: rtype = (7+rtype-1)%7; break;
// //     case cimg::keyQ:
// //     case cimg::keyESC: disp.close(); break;
// //     case cimg::keyF:
// //       if (disp.is_fullscreen) disp.resize(800,600); else disp.resize(disp.screen_dimx(),disp.screen_height());
// //       disp.toggle_fullscreen();
// //       break;
// //     default: rtype = (rtype+1)%7; break;
// //     }
// //   }
// // }
// //
