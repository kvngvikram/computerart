xmin = -3	
xmax = 1 
ymin = -1.5 
ymax = 1.5

xresolution = 1+2000
yresolution = 1+1500
iterations = 40		# positive integer
p = 2 			# parameter
threshold = 2 


import numpy as np 
import matplotlib.pyplot as plt 

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
	
	zabs = np.absolute(z) 		# calculating the absolute value
	nanflag = np.isnan(zabs)
	thresholdflag = (zabs>threshold)
	flag = np.logical_or(nanflag,thresholdflag)
	
	plt.clf()
	plt.imshow(flag.astype(float),extent=[xmin,xmax,ymin,ymax])
	plt.xlabel("Real axis")
	plt.ylabel("Complex axis")
	plt.title("iteration number :"+str(i))
	plt.show(block=False)
	plt.pause(0.1)
	


plt.imshow(flag.astype(float),extent=[xmin,xmax,ymin,ymax])
plt.show()
