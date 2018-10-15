x_range = 2		# positive
y_range = 2 		# positive

resolution = 5	 	# positive integer

iterations = 3		# positive integer
p = 2 			# parameter

import numpy as np 

# Trying to make a complex plane

x = np.linspace(-x_range,y_range,resolution)
y = np.linspace(-y_range,y_range,resolution)

mgx , mgy = np.meshgrid(x,y)

c = mgx + mgy * 1j
z = c*0



def iter(z,c,p):
	return z**p+c

i = 0
while i < iterations : 
	z = iter(z,c,p)
	print(z)
	i = i+1 

