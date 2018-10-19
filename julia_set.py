xmin = -4	
xmax = 1.5
ymin = -1.5 
ymax = 1.5

c_value = 3
iterations = 30		# positive integer
p = 3j 			# parameter
threshold = 2 


dynamic = False
pausetime = 0.05 	# sec

xresolution = 1+2000

#Note: spyder users need to enter the following command(without '#') before running the code 
# %matplotlib auto

# yresolution can be set such that spaceing is same as of x or custiom can be commented out
yresolution = 1+ int( (xresolution-1)*abs(ymax-ymin)/abs(xmax-xmin) )
#yresolution = 1 + 1000

import numpy as np 
import matplotlib.pyplot as plt 


# swaping maximum and minimum if correct values are not entered 
if xmax<xmin:
	xmax,xmin = xmin,xmax
if ymax<ymin:
	ymax,ymin = ymin,ymax

# Trying to make a complex plane
x = np.linspace(xmin,xmax,xresolution)
y = np.linspace(ymin,ymax,yresolution)

mgx , mgy = np.meshgrid(x,y)

z = mgx + mgy * 1j
c = z*c_value


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
		flag = np.logical_not(flag) 	# this is flag for the set
		
		# first term :- NaN values in zabs are set max possible value
		# second term:- non NaN values and not in set values are taken unaltered. Yet nan_to_num is used to remove NaN values. nan*0 = nan 
		# therd term :- terms in set are assigned one and later log(1) = 0 while plotting			
		m = np.nan_to_num(np.inf)*nanflag.astype(float) + np.nan_to_num(zabs)*(1-nanflag.astype(float))*(1-flag.astype(float)) + flag.astype(float)

		plt.clf()
		# doing a log plot 
		plt.imshow(np.log(m),extent=[xmin,xmax,ymin,ymax])
		
		# for boolean plot of set comment above plot statement and uncomment below 
		#plt.imshow(flag.astype(float),extent=[xmin,xmax,ymin,ymax])
		plt.xlabel("Real axis")
		plt.ylabel("Complex axis")
		plt.title("iteration number :"+str(i))
		plt.show(block=False)
		plt.pause(pausetime)

if not dynamic:
	zabs = np.absolute(z) 		# calculating the absolute value
	nanflag = np.isnan(zabs)	# checking for infinite values (NaN)
	thresholdflag = (zabs>threshold)# if absolute value threshold is reached
	# NaN values are considered to be greater than threshold
	flag = np.logical_or(nanflag,thresholdflag) 
	flag = np.logical_not(flag) 	# this is flag for the set

	# first term :- NaN values in zabs are set max possible value
	# second term:- non NaN values and not in set values are taken unaltered. Yet nan_to_num is used to remove NaN values. nan*0 = nan 
	# therd term :- terms in set are assigned one and later log(1) = 0 while plotting			
	m = np.nan_to_num(np.inf)*nanflag.astype(float) + np.nan_to_num(zabs)*(1-nanflag.astype(float))*(1-flag.astype(float)) + flag.astype(float)
	
	plt.clf()
	# doing a log plot
	plt.imshow(np.log(m),extent=[xmin,xmax,ymin,ymax])
	
	# for boolean plot of set comment above plot statement and uncomment below 
	#plt.imshow(flag.astype(float),extent=[xmin,xmax,ymin,ymax])
	plt.xlabel("Real axis")
	plt.ylabel("Complex axis")
	plt.title("iteration number :"+str(i))

plt.show()
