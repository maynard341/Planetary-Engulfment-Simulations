#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
int main(int argc, char* argv[]) {

//Randgen for PLANET 2
//TOI-5882
//Run this file AFTER randgen_p1! It needs an already-made directory to work.

//Seed random time
srand(time(NULL));
FILE* file;
int j;
FILE* massfile;
FILE* distfile;
massfile = fopen("p2_masses.txt", "a");
distfile = fopen("p2_percentdist.txt", "a");

//Create unique input files, and put them into a unique directory
for (j = 1; j < 1001; j++) {
char name[20];
char outname[20];
char filename[20];
sprintf(name, "rand%d_p2.in", j);
sprintf(outname, "output%d", j);
//mkdir(outname, 0777);
sprintf(filename, "./%s/%s", outname, name);
file = fopen (filename, "w");

if (file == NULL) {
	printf("Output file %s failed to open.", name);
}

printf("\nPLANET 2 RANDOM VALUES:");

//Mass
//NEW: Calculated masses with different percentages of heavy element mass 
//fractions, from P2mass and masscalcnew.c

double max = 0.019843;
double min = 0.000661;
double m = ((double)rand()/RAND_MAX)* (max - min) + min;
printf("\nMass: %f", m);
fprintf(file, "%f\n", m);
fprintf(massfile, "\n%d\t%f", j, m);
double copym = m;

//Radius
//Converted from FORTRAN file, used in Symba, from Seth.

double r = 0;
m = m * 333030.; //Converts to Earth Masses
m = m / 333304.; //Converts to Symba units
m = m * 4. * pow(M_PI,2.); //Converts to Symba units - will give radius output in AU
if (m <= 1.1855e-6) {
        r = 1.01854e-3*pow(m, 0.333333); //0.01 Earth masses
}
else if (m <= 2.37108e-4) {
        r = 6.34540e-4*pow(m,0.298657); //2.0 Earth masses
}
else if (m <=6.82761e-4) {
        r = 4.31273e-4*pow(m,0.252394); //5.8 Earth masses
}
else if (m <= 1.08189e-2) {
        r=1.55290e-2*pow(m,0.744031);  //91 Earth masses
}
else if (m <= 2.2943) {
        r=4.49484e-4*pow(m,-0.038559); //20000 Earth masses
}
else {
        r=2.18062e-4*pow(m,0.832465); //Star mass
}

printf("\nRadius: %f", r);
fprintf(file, "%f\n", r);

//Semimajor axis
//Taken from Obertas et al (2017) and Gladman (1993). 

double lower = 0.9;
double upper = 1.2;
double percent = ((double)rand()/RAND_MAX)* (upper - lower) + lower;
printf("\nPercent of Hill radius: %f", percent);
fprintf(distfile, "\n%d\t%f", j, percent);

double m1 = 0.023311049; //Mass of first planet (surviving), solar masses
double m2 = copym; //Mass of second planet (engulfed), solar masses
double mstar = 1.554; //Mass of star, solar masses
double a_1 = 0.0845; //Semimajor axis of outer star, AU
double mu_1 = m1/mstar; //Planet-star ratio (planet 1)
double mu_2 = m2/mstar; //Planet-star ratio (planet 2)

double interm = (mu_1 + mu_2)/3.; //Intermediate calc for X
double X = 0.5* pow(interm, 1./3.); //X coefficient
double intc = 2. * pow(3.,1./6.) * pow((mu_1 + mu_2),1./3.); //Critical sep. value, AU
double c = intc * a_1;

//EDIT POINTNINE FOR CHANGES IN DELTA
//PLANET 2 AS INNER PLANET 
double pointnine = percent * c * X; 
double equals = (pointnine *a_1) - a_1; //Intermedate calculations for final a_2
double a_2 = equals/(-1. - pointnine);

/*
//PLANET 2 AS OUTER PLANET
double pointnine = percent * c * X;
double equals = (pointnine *a_1) + a_1;
double a_2 = equals/(1. - pointnine);
*/

printf("\nSemimajor axis: %f", a_2);
fprintf(file, "%f\n", a_2);

//Eccentricity
double e = 0; //Set equal to 0 for initial conditions
printf("\nEccentricity: %f", e);
fprintf(file, "%f\n", e);

//Inclination
double i = 0; //Set equal to 0 for initial conditions
printf("\nInclination: %f", i);
fprintf(file, "%f\n", i);

//Longitude (Omega)
double co = (double)rand() / RAND_MAX;
co = co * 2 * M_PI;
printf("\nLongitude of ascending node: %f", co);
fprintf(file, "%f\n", co);

//Pericenter (omega)
double om = (double)rand() / RAND_MAX;
om = om * 2 * M_PI;
printf("\nArg of pericenter: %f", om);
fprintf(file, "%f\n", om);

//Anomaly (f)
double f = (double)rand() / RAND_MAX;
f  = f * 2 * M_PI;
printf("\nAnomaly: %f", f);
fprintf(file, "%f\n", f);

}
return 0;

}








