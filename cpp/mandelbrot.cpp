
#include<iostream>
using namespace std;

void my_product(long double* pc , long double* pa , long double* pb , unsigned int* pxres , unsigned int* pyres ); 
void input_check(float* pxmin , float* pxmax , float* pymin , float* pymax , unsigned int* pxres , unsigned int* pyres , long double* pzr , long double* pzi) ; 
void prepare(long double* pc , unsigned int* pxres , unsigned int* pyres , float* pxmin , float* pxmax , float* pymin , float* pymax);	

int main(){

	float xmin = 1 ;
	float xmax = -3  ;
	float ymin = -1 ; 
	float ymax = 2  ;
	unsigned int xres = 3 ; 
	long double zr = 0 ;
	long double zi  = 0 ; 
	unsigned int yres; 
	
	input_check( &xmin , &xmax , &ymin , &ymax , &xres , &yres , &zr , &zi);
	

	yres = float(xres)*(ymax-ymin)/(xmax-xmin);
	cout<<"\tThe range is"<<'\t'<<xmin<<'\t'<<xmax<<'\t'<<ymin<<'\t'<<ymax<<endl;	
	cout<<"\tThe resolutions for x and y are "<<xres<<" and "<<yres<<endl;

	long double c[yres][xres][2] ;
	long double* pc = &c[0][0][0] ;
	

	prepare(pc , &xres, &yres , &xmin , &xmax , &ymin , &ymax);


	cout<<endl<<endl;
	for(unsigned int j = 0 ;  j < yres ; j++ ){
		for(unsigned int i = 0 ; i < xres ; i++ ){
			cout<< '\t'<<c[j][i][0]<<'\t'<<c[j][i][1] << endl;
		}
	}

	my_product(pc,pc,pc,&xres,&yres);	

	cout<<endl<<endl;
	for(unsigned int j = 0 ;  j < yres ; j++ ){
		for(unsigned int i = 0 ; i < xres ; i++ ){
			cout<< '\t'<<c[j][i][0]<<'\t'<<c[j][i][1] << endl;
		}
	}

}



void my_product(long double* pc , long double* pa , long double* pb , unsigned int* pxres , unsigned int* pyres ) { 
/*	
	long double ar , ai , br , bi , cr , ci ;
	cr = ar*br - ai*bi; 
	ci = ar*bi + br*ai; 
	return cr , ci;
*/
	unsigned int xres = *pxres , yres = *pyres ; 
	long double a[yres][xres][2] , b[yres][xres][2] , c[yres][xres][2] ; 
	
	long double ar , ai , br , bi , cr , ci ;

	for(unsigned int j = 0 ;  j < yres ; j++ ){
		for(unsigned int i = 0 ; i < xres ; i++ ){
			// *(pc + xres*2*j + 2*i + 0)
			ar = *(pa + xres*2*j + 2*i + 0);
			ai = *(pa + xres*2*j + 2*i + 1); 
			br = *(pb + xres*2*j + 2*i + 0);
			bi = *(pb + xres*2*j + 2*i + 1); 
			
		//	cout<<"a is "<<'\t'<<ar<<'\t'<<ai<<endl;
		//	cout<<"b is "<<'\t'<<br<<'\t'<<bi<<endl;
			cr = ar*br - ai*bi; 
			ci = ar*bi + ai*br;
			
		//	cout<<"c is "<<'\t'<<cr<<'\t'<<ci<<endl;
	
			*(pc + xres*2*j + 2*i + 0) = cr; 
			*(pc + xres*2*j + 2*i + 1) = ci;  
		}
	} 	
}


void input_check(float* pxmin , float* pxmax , float* pymin , float* pymax , unsigned int* pxres , unsigned int* pyres , long double* pzr , long double* pzi) {

	cout<<"\tchecking "<<endl;
	//cout<<"\tThe range is"<<'\t'<<*pxmin<<'\t'<<*pxmax<<'\t'<<*pymin<<'\t'<<*pymax<<endl;

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
}

void prepare(long double* pc , unsigned int* pxres , unsigned int* pyres , float* pxmin , float* pxmax , float* pymin , float* pymax){	
	unsigned int xres = *pxres , yres = *pyres ;
	float xmin = *pxmin , xmax = *pxmax , ymin = *pymin , ymax = *pymax ; 
	cout<<"\tThe range is"<<'\t'<<xmin<<'\t'<<xmax<<'\t'<<ymin<<'\t'<<ymax<<endl;	
	cout<<"\tThe resolutions for x and y are "<<xres<<" and "<<yres<<endl;
	for(unsigned int j = 0 ;  j < yres ; j++ ){
		for(unsigned int i = 0 ; i < xres ; i++ ){
			
			// *(pc + xres*2*j + 2*i + 0)
			*(pc + xres*2*j + 2*i + 0) = xmin + (i)*(xmax-xmin)/float(xres-1); 
			*(pc + xres*2*j + 2*i + 1) = ymax - (j)*(ymax-ymin)/float(yres-1); 
		//	cout<< *(pc + xres*2*j + 2*i + 0) ; 
		//	cout<< '\t'<< *(pc + xres*2*j + 2*i + 1) << endl;
		}
	}
} 

// pointer arthematic 
