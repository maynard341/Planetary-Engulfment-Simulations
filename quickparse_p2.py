#Setup
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime
import fileinput
import math
#import tkinter
#import matplotlib
#matplotlib.use('TkAgg') #TkAgg for graphs

  	
eccs = np.zeros(shape=(6,1))
peris = np.zeros(shape=(6,1))
ecount = 0    
Rstar = 0.010337989;

writefile = open("testp2.txt", "w")
for num in range(1, 1001):
    # Generate the file name based on the numerical pattern
        file_name = f"./output{num}/output{num}_p2.txt"

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

        e_check = np.amax(x_twocol) #What is the maximum eccentricity?
        p_check = np.min(x_eightcol) #What is the minimum pericenter distance?
        timelen = len(x_zerocol) #What is the time of cutoff?

        eccs[ecount] = e_check #Store list of min pericenters and max eccs
        peris[ecount] = p_check
        print(e_check)
        lasttime = x_zerocol[timelen - 1] #What is the ending time?
        #print(f"{str(num)}:\t")
        #print(f"{str(num)}:\t", file=writefile)
        if (e_check < 1.0 and p_check > Rstar):
          print(f"{str(num)}\tSemistable\n")
          print(f" {str(num)}\tSemistable\n", file=writefile)
        elif (p_check < Rstar):
          print(f"{str(num)}\tPlanet likely engulfed at time {lasttime}\n")
          print(f"{str(num)}\tPlanet likely engulfed at time {lasttime}\n", file=writefile)
        elif (e_check > 1.0):
          print(f"{str(num)}\tPlanet likely ejected\n")
          print(f"{str(num)}\tPlanet likely ejected\n", file=writefile)

