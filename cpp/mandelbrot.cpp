#include<iostream>

using namespace std;

//long double my_complex_multiply(long double a , long double b );

int main(){

	float xmin = 1 ;
	float xmax = -3  ;
	float ymin = -1 ; 
	float ymax = 2  ;
	unsigned int xres = 100 ; 
	long double zreal = 0 ;
	long double zimg  = 0 ; 
	
	if (ymin>ymax){
		ymax = ymax + ymin ; 
		ymin = ymax - ymin ;
		ymax = ymax - ymin ; 		
	}
	
	if (xmin>xmax){
		xmax = xmax + xmin ; 
		xmin = xmax - xmin ;
		xmax = xmax - xmin ; 		
	}
	cout<<"The range is"<<'\t'<<xmin<<'\t'<<xmax<<'\t'<<ymin<<'\t'<<ymax<<endl;
	
	unsigned int yres = float(xres)*(ymax-ymin)/(xmax-xmin);
	cout<<"The resolutions for x and y are "<<xres<<" and "<<yres<<endl;

	//long double c[yres][xres][2] ;
	//long double c = 1 ; 

	//c  = my_complex_multiply(c,c);
   
}

/*
long double my_complex_multiply(long double a , long double b ){
	
	return a;	
}
*/
