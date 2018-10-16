xmin = -2	
xmax = 0.5
ymin = -1 
ymax = 1

iterations = 30		# positive integer
p = 2 			# parameter
threshold = 2 

dynamic = True

xresolution = 1+2000
# yresolution can be set such that spaceing is same as of x or custiom can be commented out
yresolution = 1+ int( (xresolution-1)*abs(ymax-ymin)/abs(xmax-xmin) )
#yresolution = 1 + 1000

import numpy as np 
import matplotlib.pyplot as plt 

# swaping maximum and minimum if correct values are not entered 
if xmax<xmin:
	xmax,xmin = xmin,xmax
if ymax<ymin:
	ymax,ymin = yim,ymax

# Trying to make a complex plane
x = np.linspace(xmin,xmax,xresolution)
y = np.linspace(ymin,ymax,yresolution)

mgx , mgy = np.meshgrid(x,y)

c = mgx + mgy * 1j
z = c*0


# Function that calculates the next iteration
def iter(z,c,p):
	return z**p+c

# while loop for iterations
plt.figure(0)
i = 0
while i < iterations : 
	z = iter(z,c,p)
	i = i+1

	if dynamic:	
		zabs = np.absolute(z) 		# calculating the absolute value
		nanflag = np.isnan(zabs)	# checking for infinite values (NaN)
		thresholdflag = (zabs>threshold)# if absolute value threshold is reached
		# NaN values are considered to be greater than threshold
		flag = np.logical_or(nanflag,thresholdflag) 
	
		plt.clf()
		plt.imshow(flag.astype(float),extent=[xmin,xmax,ymin,ymax])
		plt.xlabel("Real axis")
		plt.ylabel("Complex axis")
		plt.title("iteration number :"+str(i))
		plt.show(block=False)
		plt.pause(0.1)
	


zabs = np.absolute(z) 		
nanflag = np.isnan(zabs)
thresholdflag = (zabs>threshold)
flag = np.logical_or(nanflag,thresholdflag)
	
plt.clf()
plt.imshow(flag.astype(float),extent=[xmin,xmax,ymin,ymax])
plt.xlabel("Real axis")
plt.ylabel("Complex axis")
plt.title("iteration number :"+str(i))
plt.show()
