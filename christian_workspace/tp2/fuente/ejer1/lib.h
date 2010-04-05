#include<CImg.h>
using namespace std;
using namespace cimg_library;

int clipp(int valor) {
	if (valor > 255)
		return 255;
	else if (valor < 1)
		return 0;
	else
		return valor;
}

CImg<unsigned char> lut(CImg<unsigned char> original, int a = 1, int c = 0,
		bool clip = 1) {
	/*	entrada_r imagen de entrada sobre la cual se aplica la transformacion
	 a: factor de ganancia
	 c: offset
	 clip=1 implica que corte en 0 y 255 los valores - por defecto clipea
	 retorna una imagen  modificada linealmente*/

	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);
	int valor;
	cimg_forXY( modificada, x, y )
		{
			valor = a * original(x, y) + c;
			if (clip) {
				valor = clipp(valor);
			}

			modificada(x, y) = valor;
		}
	return modificada;
}

CImg<unsigned char> obtener_grafica_mapeo(int a, int c) {
	/* retorna en una imagen la grafica de la fucion de mapeo segun los
	 * coeficientes a y c que se pasan por paremtro
	 * */
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = lut(mapeo, a, c, false);
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}

CImg<unsigned char> negativo(CImg<unsigned char> & img1) { //retorna el negativo de una imagen
	int a = -1;
	unsigned char c = img1.max(); // maximo de la imagen
	return lut(img1, a, c, 1);
}

CImg<unsigned char> lut_tramos(CImg<unsigned char> original, int x0, int x1,
		bool clip, int factor) {
	/* compresion lineal por tramos
	 * factor = factore de compresion o estiramiento segun su valor
	 *
	 * */
	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);
	cimg_forXY(original, x, y)
		{
			switch (1 + (x > x0) + (x > x1)) {
			case 1: // esta entre 0 y x1
				modificada(x, y) = original(x, y);
				break;
			case 2: //es mayor que x1 y menor que x2
				modificada(x, y) = original(x, y) * factor;
				break;
			case 3: //es mayor que x2
				modificada(x, y) = original(x, y);
				break;
			}
		}
	return modificada;
}

CImg<unsigned char> obtener_grafica_mapeo_tramos(int x0, int x1, int factor) {
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = lut_tramos(mapeo, x0, x1, 1, factor);
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}

/*FUNCIONES EJERCICIO2
 * */
CImg<unsigned char> logaritmo(CImg<unsigned char> original, int factor = 1) {
	// transforacion logaritmica
	// por defecto clipea
	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);

	cimg_forXY(original,x,y)
		{
			modificada(x, y) = log(1 + original(x, y)) * factor;
		}

	return modificada;
}

//FIXME: va con clip o sin clip??
CImg<unsigned char> potencia(CImg<unsigned char> original, int exp, int factor =
		1) {
	// transforacion de potencia
	// por defecto clipea
	CImg<unsigned char> modificada(original.width(), original.height(), 1, 1);
	cimg_forXY(original,x,y)
		{
			modificada(x, y) = clipp(pow(original(x, y), exp)) * factor;
		}
	return modificada;
}

CImg<unsigned char> obtener_grafica_mapeo_logaritmo(int factor) {
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = (logaritmo(mapeo, factor));
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}

CImg<unsigned char> obtener_grafica_mapeo_potencia(int exponente) {
	unsigned char blanco[] = { 255, 255, 255 };
	CImg<unsigned char> mapeo(255, 1, 1, 1, 0);
	CImg<unsigned char> mapeo_disp(255, 255, 1, 1, 0);
	cimg_forX( mapeo, x ) {
		mapeo(x) = x; //escala de 0 a 255
	}
	CImg<unsigned char> mapeado = potencia(mapeo, exponente);
	return mapeo_disp.draw_graph(mapeado, blanco, 1, 1, 1, 255, 0);
}

//ejercicio 3:
//1a-
//suma
template<class T>
T sumar(T primer_termino, T segundo_termino, bool normalizado = true) {
	//funcion que retorna la suma de 2 terminos...
	// para llamarla por ejemplo : sumar<double>(l,m);
	/*XXX: return (normalizado)? (primer_termino+segundo_termino)/2 : primer_termino+segundo_termino;*/// no entiendo porque de esta forma no anda
	if (normalizado) //FIXME: normalizado o clipp?
		return (primer_termino + segundo_termino) / 2;
	return (primer_termino + segundo_termino);
}

//resta
template<class T>
T restar(T primer_termino, T segundo_termino, bool normalizado = true) {
	//funcion que retorna la resta de 2 terminos... segundo_termino-primer_termino
	// para llamarla por ejemplo :restar<double>(l,m);

	T imagen = primer_termino - segundo_termino;
	if (normalizado) { // FIXME: seria normalizado o clip?
		cimg_forXY(imagen, x,y)
			{ //FIXME: esto de sumar por 255 y divir por 2 es lo que pide: ?? porque? no entiendo
				imagen(x, y) = (imagen(x, y) + 255) / 2;
			}
		return imagen;
	}
	return (primer_termino - segundo_termino);
}

template<class T>
T clipp_im(T imagen) {
	cimg_forXY(imagen, x, y)
		{
			if ((imagen(x, y)) > 255)
				imagen(x, y) = 255;
			if (imagen(x, y) < 0)
				imagen(x, y) = 0;
		}
	return imagen;
}

//multiplicacion
//*****************************************************************************
CImg<unsigned char> multiplicar(CImg<unsigned char> im1,
		CImg<unsigned char> im2, bool normalizar) {
	CImg<unsigned char> imagen(im1.width(), im1.height(), 1, 1);

	cimg_forXY(im1, x, y)
		{
			imagen(x, y) = im1(x, y) * im2(x, y);
		}
	if (normalizar)
		return imagen.normalize();
	else
		return imagen;
}
//*****************************************************************************
//divicion
CImg<unsigned char> dividir(CImg<unsigned char> im1, CImg<unsigned char> im2,
		bool normalizar) {
	CImg<unsigned char> imagen(im1.width(), im1.height(), 1, 1);

	cimg_forXY(im1, x, y)
		{
			if (floor(im2(x, y)) == 0)
				imagen(x, y) = im1(x, y); //TODO: dejo el original --->que hago que es lo correcto?
			else
				imagen(x, y) = im1(x, y) / im2(x, y);
		}
	if (normalizar)
		return imagen.normalize();
	else
		return imagen;
}

//FIXME: varias cosas en todas las fucniones.. confusion entre normalizado y clipp. en vez de hacer el clipp no puedo hacer el
//normalizado y listo?


//WBB: no se que esta mal!
CImg<unsigned char> emboss(CImg<unsigned char> im1, int c, bool normalizado =
		true) { //TODO: hacer para que corte la imagen segun el desplazamiento
	/*	funcion que aplica un filtro emboss a una imagen
	 im1: imagen a la que se le aplica el filtro
	 * c:	parametro de desplazamiento salida=entrada+c
	 * normalizado: true (por defecto) -> la imagen se corta si el valor del pixel es menor que 0 o mayor que 255
	 * LA FUNCION RETORNA LA IMAGEN CON EL FILTRO APLICADO*/

	//CImg<unsigned char> imagen(im1.width()-c, im1.height(), 1, 1);
	if (normalizado)
		return sumar(im1, lut(negativo(im1), 1, c, false)).normalize(); //FIXME: ver lo del false normalizado=clipp hay que sacarlo sino
	return sumar(im1, lut(negativo(im1), 1, c, false));
}
