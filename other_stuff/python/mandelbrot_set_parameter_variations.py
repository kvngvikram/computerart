xmin = -2	
xmax = 1.5
ymin = -1.5 
ymax = 1.5

iterations = 30		# positive integer

# parameter
pmin = 2 
pmax = 8 
pres = 1+10 		# resolution in parameter vairations 

threshold = 2 

pausetime = 0.005 	# sec

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

plt.figure(0)

parameterarray = np.linspace(pmin,pmax,pres)

for p in parameterarray:
	
	z = c*0 

	# while loop for iterations
	i = 0
	while i < iterations : 
		z = iter(z,c,p)
		i = i+1
		
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
	plt.title("parameter value :"+str(p))
	plt.show(block=False)
	plt.pause(pausetime)





plt.show()
