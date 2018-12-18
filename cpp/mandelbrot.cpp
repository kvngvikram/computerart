
float xmin = 1 ;
float xmax = -3  ;
float ymin = -1 ; 
float ymax = 2  ;
unsigned int xres = 100 ; 
long double zr = 0 ;
long double zi  = 0 ; 



#include<iostream>

unsigned int yres; 

using namespace std;

void my_product(long double * pc , long double * pa , long double * pb ) ; 
void input_check(float * pxmin , float * pxmax , float * pymin , float * pymax , unsigned int * pxres , unsigned int * pyres , long double * pzr , long double * pzi) ; 

int main(){

	input_check( &xmin , &xmax , &ymin , &ymax , &xres , &yres , &zr , &zi);

	
	yres = float(xres)*(ymax-ymin)/(xmax-xmin);
	cout<<"\tThe resolutions for x and y are "<<xres<<" and "<<yres<<endl;

	long double c[yres][xres][2] ;
	long double * pc = &c[0][0][0] ;

	my_product(pc,pc,pc); 








/*
	long double a[3][2]={{1,4},{3,5},{6,7}} , b[3]={1,2,3}  ; 
	long double * pa = &a[0][0] , * pb = &b[0] ;
	cout<<*(pa+1)<<endl;
	long double * pc = myfunc( pa, pb);
	cout<<*(pc+3)<<endl;


	*(pc+3) = *(pc+3) + 2 ; 

	cout<<*(pc+3)<<endl;
	cout<<a[2][1]<<endl;

	
	//long double pc =  c ; 
	//c  = my_complex_multiply(c,c);
*/ 
}



void my_product(long double * pc , long double * pa , long double * pb ) { 
/*	
	long double ar , ai , br , bi , cr , ci ;
	cr = ar*br - ai*bi; 
	ci = ar*bi + br*ai; 
	return cr , ci;
*/
	long double a[yres][xres][2] , b[yres][xres][2] , c[yres][xres][2] ; 
	
	long double ar , ai , br , bi , cr , ci ;

	for(unsigned int j = 0 ;  j < yres ; j++ ){
		for(unsigned int i = 0 ; i < xres ; i++ ){

			ar = *(pa + i + j*i);
			ai = *(pa + i + j*i + xres*yres); 
			br = *(pb + i + j*i);
			bi = *(pb + i + j*i + xres*yres);
			
			cr = ar*br - ai*bi; 
			ci = ar*bi + ai*br;
			
			*(pc + i + j*i) = cr; 
			*(pc + i + j*i + xres*yres) = ci;  
		}
	} 	
}


void input_check(float * pxmin , float * pxmax , float * pymin , float * pymax , unsigned int * pxres , unsigned int * pyres , long double * pzr , long double * pzi) {

	cout<<"\tchecking "<<endl;

	cout<<"\tThe range is"<<'\t'<<*pxmin<<'\t'<<*pxmax<<'\t'<<*pymin<<'\t'<<*pymax<<endl;

	if (*pymin>*pymax){
		*pymax = *pymax + *pymin ; 
		*pymin = *pymax - *pymin ;
		*pymax = *pymax - *pymin ; 
		
		cout<<"\tY range swapped"<<endl;
	}
	
	if (*pxmin>*pxmax){
		*pxmax = *pxmax + *pxmin ; 
		*pxmin = *pxmax - *pxmin ;
		*pxmax = *pxmax - *pxmin ;
		
		cout<<"\tX range swapped"<<endl;	
	}
	
	cout<<"\tThe range is"<<'\t'<<*pxmin<<'\t'<<*pxmax<<'\t'<<*pymin<<'\t'<<*pymax<<endl;
	
} 
