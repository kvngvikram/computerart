
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void input_check(float* pxmin , float* pxmax , float* pymin , float* pymax , unsigned int* pxres , unsigned int* pyres , long double* pzr , long double* pzi) ; 
void prepare_c(long double* pc , unsigned int* pxres , unsigned int* pyres , float* pxmin , float* pxmax , float* pymin , float* pymax);	
void prepare_z(long double* pz , unsigned int* pxres , unsigned int* pyres , long double* pzr , long double* pzi );	
void prepare_false_flag(bool* pf , unsigned int* pxres , unsigned int* pyres); 

int main(){

	float xmin = 1 ;
	float xmax = -3  ;
	float ymin = -1 ; 
	float ymax = 2  ;
	unsigned int xres = 10 ; 
	long double zr = 0 ;
	long double zi = 0 ;
	long double div_lim = 100000 ; 
	unsigned int max_iter = 30 ; 
 
	unsigned int yres; 
	
	input_check( &xmin , &xmax , &ymin , &ymax , &xres , &yres , &zr , &zi);

	yres = float(xres)*(ymax-ymin)/(xmax-xmin);

	long double* p1 = (long double*) malloc(sizeof(long double[1000][34]));

	long double c[yres][xres][2]  , z[yres][xres][2] , absz[yres][xres] ;
	cout<<"defined arrays "<<endl;
	unsigned int itn[yres][xres] ; 
	bool flag1[yres][xres]  , flag2[yres][xres] ; 

	long double* pc = &c[0][0][0] , * pz = &z[0][0][0] , * pabsz = &absz[0][0] ;
	prepare_c(pc , &xres , &yres , &xmin , &xmax , &ymin , &ymax);
	prepare_z(pz , &xres , &yres , &zr , &zi );
	prepare_false_flag( &flag1[0][0] , &xres , &yres);
	prepare_false_flag( &flag2[0][0] , &xres , &yres);

	 
	//my_product(pc,pc,pc,&xres,&yres);
	//my_add(pz,pz,pc,&xres,&yres);
	
	//cout<<endl<<endl;
	
	unsigned int n = 0 ; 
	while ( n < max_iter){
		for(unsigned int j = 0 ;  j < yres ; j++ ){
				for(unsigned int i = 0 ; i < xres ; i++ ){	
				
				long double zr = *(pz + xres*2*j + 2*i + 0) , zi = *(pz + xres*2*j + 2*i + 1) ;
				long double cr = *(pc + xres*2*j + 2*i + 0) , ci = *(pc + xres*2*j + 2*i + 1) ;
				long double labs = *(pabsz + xres*j + i) ;
			//	z = z^2 + c 
				zr = pow( zr , 2) - pow( zi , 2) + cr; 
				zi = 2*zr*zi + ci;

				//cout<<'\t'<<absz[j][i] ;
				labs = pow( ( pow(zr , 2) + pow(zi ,2) ) , 0.5)*float( ! flag1[j][i]) + labs*float(flag1[j][i]);
				
				flag1[j][i] = labs > div_lim ; 
			
				if( ! flag1[j][i] && ! flag2[j][i] )itn[j][i] = n; 
				else flag2[j][i] = true; 

				cout<<itn[j][i]<<'\t';
				//cout<<flag2[j][i];
				*(pz + xres*2*j + 2*i + 0) = zr ;
				*(pz + xres*2*j + 2*i + 1) = zi ; 
				*(pabsz + xres*j + i) = labs ;  
			}
		}
		n++;
		cout<<endl;
	}
	
	cout<<endl<<endl;
	free(p1);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void prepare_false_flag(bool* pf , unsigned int* pxres , unsigned int* pyres){
	unsigned int xres = *pxres , yres = *pyres;
	for(unsigned int j = 0 ;  j < yres ; j++ ){
		for(unsigned int i = 0 ; i < xres ; i++ ){
			*(pf + xres*j + i + 0) = false; 
		}
	}
}
