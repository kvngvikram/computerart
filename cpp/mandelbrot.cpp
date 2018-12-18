
#include<iostream>
using namespace std;

void my_product(long double* pc , long double* pa , long double* pb , unsigned int* pxres , unsigned int* pyres ); 
void input_check(float* pxmin , float* pxmax , float* pymin , float* pymax , unsigned int* pxres , unsigned int* pyres , long double* pzr , long double* pzi) ; 
void prepare_c(long double* pc , unsigned int* pxres , unsigned int* pyres , float* pxmin , float* pxmax , float* pymin , float* pymax);	
void prepare_z(long double* pz , unsigned int* pxres , unsigned int* pyres , long double* pzr , long double* pzi );	

int main(){

	float xmin = 1 ;
	float xmax = -3  ;
	float ymin = -1 ; 
	float ymax = 2  ;
	unsigned int xres = 3 ; 
	long double zr = 0 ;
	long double zi = 0 ; 
	unsigned int yres; 
	
	input_check( &xmin , &xmax , &ymin , &ymax , &xres , &yres , &zr , &zi);

	yres = float(xres)*(ymax-ymin)/(xmax-xmin);
	cout<<"\tThe range is"<<'\t'<<xmin<<'\t'<<xmax<<'\t'<<ymin<<'\t'<<ymax<<endl;	
	cout<<"\tThe resolutions for x and y are "<<xres<<" and "<<yres<<endl;

	long double c[yres][xres][2]  , z[yres][xres][2] ;
	long double* pc = &c[0][0][0] , * pz = &z[0][0][0];

	prepare_c(pc , &xres , &yres , &xmin , &xmax , &ymin , &ymax);
	prepare_z(pz , &xres , &yres , &zr , &zi );
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

void prepare_c(long double* pc , unsigned int* pxres , unsigned int* pyres , float* pxmin , float* pxmax , float* pymin , float* pymax){	
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

void prepare_z(long double* pz , unsigned int* pxres , unsigned int* pyres , long double* pzr , long double* pzi ) {	
	
	unsigned int xres = *pxres , yres = *pyres ;
	float zr =  *pzr , zi = *pzi ;

	for(unsigned int j = 0 ;  j < yres ; j++ ){
		for(unsigned int i = 0 ; i < xres ; i++ ){
			// *(pc + xres*2*j + 2*i + 0)
			*(pz + xres*2*j + 2*i + 0) = zr; 
			*(pz + xres*2*j + 2*i + 1) = zi; 
		//	cout<< *(pz + xres*2*j + 2*i + 0) ; 
		//	cout<< '\t'<< *(pz + xres*2*j + 2*i + 1) << endl;
		}
	}
	 
}	
/* pointer arthematic 
for a matrix M[X][Y][Z]
M[i][j][k] = *(&M[0][0][0]+(Y*Z*i+Z*j+k))
*/
