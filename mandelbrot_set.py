xmin = -2	
xmax = 1 
ymin = -2 
ymax = 2 

xresolution = 15
yresolution = 21
iterations = 8		# positive integer
p = 2 			# parameter
threshold = 2 

import numpy as np 

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
i = 0
while i < iterations : 
	z = iter(z,c,p)
	zabs = np.absolute(z) 		# calculating the absolute value
	flag = zabs>threshold
	i = i+1

print(flag.astype(float))	
