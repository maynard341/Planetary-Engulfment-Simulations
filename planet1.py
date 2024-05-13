#Setup
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime 
import fileinput
import math
import tkinter
import matplotlib
matplotlib.use('TkAgg') #TkAgg for graphs

#mod360 function definition, for variables 
def mod360(x):
    if x > 360.:
        return mod360(x - 360.)
    elif x < 0.:
        return mod360(x + 360.)
    else:
        return x

#Declare variables
#Needs to CHANGE with each star system. 
n0 = 5.1  #Mean motion - 2pi/period
wdot = -n0*(3./2.*16298e-6/3./3.) #Angular velocity

for num in range(85, 1001):
    # Generate the file name based on the numerical pattern
	file_name = f"./output{num}/output{num}_p1.txt"

#Load input from a.txt to numpy arrays
	x_data = np.loadtxt(file_name, dtype = float)
#x_data = np.loadtxt(string_default, dtype = float)

	x_zerocol = x_data[:,0] #time
	x_onecol = x_data[:,1] #a
	x_twocol = x_data[:,2] #e
	x_thrcol = x_data[:,3] #i
	x_fourcol = x_data[:,4] #Omega
	x_fivecol = x_data[:,5] #omega
	x_sixcol = x_data[:,6] #f
	x_sevcol = x_data[:,7] #distance from planet to star
	x_eightcol = x_data[:,8] # distance to pericenter

	#Make figure
	fig, ax  = plt.subplots(2, 4)
	plt.legend()
	plt.suptitle("Orbital Parameters for TOI-5882 System - Planet 1 (Known Exoplanet)")
	#plt.suptitle(file_name)
	#plt.text(0.5, 0.92, file_name, fontsize=40, ha='center', va='center', transform=plt.gca().transAxes)

	#Longitude Sim
	ax[0,0].set_title("Simulation of Longitude of Ascending Node")
	ax[0,0].plot(x_zerocol, x_fourcol, label = "Longitude", linewidth = 1, color = "purple");
	ax[0,0].set_xlabel("Time (years)")
	ax[0,0].set_ylabel("Longitude (deg)")
	ax[0,0].set_ylim(0, 370)
	#ax[0,0].legend(bbox_to_anchor=(1.05, 1), loc='lower right', borderaxespad=0)
	
	#Semimajor Axis
	ax[1,0].set_title("Simulation of Semimajor Axis")
	ax[1,0].plot(x_zerocol, x_onecol, label = "Semimajor Axis", linewidth = 1, color = "darkblue");
	ax[1,0].set_xlabel("Time (years)")
	ax[1,0].set_ylabel("Semimajor axis (AU)")
	#ax[1,0].set_xlim(0,1)
	#ax[1,0].set_ylim(0,1)
	
	#Eccentricity
	ax[1,1].plot(x_zerocol, x_twocol, label = "Eccentricity", linewidth = 1, color = "gold");
	ax[1,1].set_title("Simulation of Eccentricity")
	ax[1,1].set_xlabel("Time (years)")
	ax[1,1].set_ylabel("Eccentricity")
	#ax[1,1].set_xlim(0,1)
	#ax[1,1].set_ylim(0,1)
	
	#Inclination
	ax[0,1].plot(x_zerocol, x_thrcol, label = "Inclination", linewidth = 1, color = "green");
	ax[0,1].set_title("Simulation of Inclination")
	ax[0,1].set_xlabel("Time (years)")
	ax[0,1].set_ylabel("Inclination (deg)")
	#ax[0,1].set_ylim(80, 90)
	#ax[0,1].set_xlim(0,1)
	
	#Argument of pericenter
	ax[0,2].plot(x_zerocol, x_fivecol, label = "Argument of Pericenter", linewidth = 1, color = "orange");
	ax[0,2].set_title("Simulation of Arg. of Pericenter")
	ax[0,2].set_xlabel("Time (years)")
	ax[0,2].set_ylabel("Argument of Pericenter (deg)")
	#ax[0,2].set_ylim(0, 1)
	#ax[0,2].set_ylim(0, 360)
	
	#True anomaly
	ax[1,2].plot(x_zerocol, x_sixcol, label = "f", linewidth = 1, color = "red");
	ax[1,2].set_title("Simulation of True Anomaly")
	ax[1,2].set_xlabel("Time (years)")
	ax[1,2].set_ylabel("True Anomaly (deg)")
	#ax[1,2].set_xlim(0,0.2)

	#Distance from planet to star
	ax[0,3].plot(x_zerocol, x_sevcol, label = "r", linewidth = 1, color = "magenta");
	ax[0,3].set_title("Simulation of Distance from Planet to Star")
	ax[0,3].set_xlabel("Time (years)")
	ax[0,3].set_ylabel("Distance (AU) ")
	#ax[0,3].set_xlim(0,0.2)
	#ax[0,3].set_ylim(0,1)'''
	
	#Pericenter distance 
	ax[1,3].plot(x_zerocol, x_eightcol, label = "r", linewidth = 1, color = "pink");
	ax[1,3].set_title("Simulation of Pericenter Distance")
	ax[1,3].set_xlabel("Time (years)")
	ax[1,3].set_ylabel("Pericenter Distance (AU)")
	#ax[1,3].set_ylim(0,1)
	plt.show(block=True)







