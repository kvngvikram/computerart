x_range = 5		# should be positive
y_range = 5 		# should be positive

resolution = 11 	# should be positive



import numpy as np 

# Trying to make a complex plane

x = np.linspace(-x_range,y_range,resolution)
y = np.linspace(-y_range,y_range,resolution)

mgx , mgy = np.meshgrid(x,y)

c = mgx + mgy * 1j

print(c)

