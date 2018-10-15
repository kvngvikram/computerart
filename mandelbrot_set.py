x_range = 2		# positive
y_range = 2 		# positive

resolution = 5	 	# positive integer

iterations = 3		# positive integer
p = 2 			# parameter
threshold = 2 

import numpy as np 

# Trying to make a complex plane

x = np.linspace(-x_range,y_range,resolution)
y = np.linspace(-y_range,y_range,resolution)

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
