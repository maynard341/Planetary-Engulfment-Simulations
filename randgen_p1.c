#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
int main(int argc, char* argv[]) {

//Randgen for PLANET 1
//TOI-5882
//Run this file FIRST, before randgen_p2! P1 file MAKES A NEW DIRECTORY and P2 will just 
//add to it. 


//Seed random time
srand(time(NULL));
FILE* file;
int j;
//Create unique input files, and put them into a unique directory
for (j = 1; j < 1001; j++) {
char name[20];
char outname[20];
char filename[20];
sprintf(name, "rand%d_p1.in", j);
sprintf(outname, "output%d", j);
mkdir(outname, 0777);
sprintf(filename, "./%s/%s", outname, name);
file = fopen (filename, "w");

if (file == NULL) {
	printf("Output file %s failed to open.", name);
}

printf("\nPLANET 1 RANDOM VALUES:");

//Mass
//Known mass value, in solar masses, of TOI-5882's exoplanet.
double m = 0.023311049;
printf("\nMass: %f", m);
fprintf(file, "%f\n", m);
double copym = m;

//Radius
//Known radius value, in AU, of TOI-5882's exoplanet.
double r = 0.00046212398;
printf("\nRadius: %f", r);
fprintf(file, "%f\n", r);

//Semimajor axis
//Known SM axis value, in AU, of TOI-5882's exoplanet.
double a_2 = 0.0845;
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

//The following are randomly drawn from 0 to 2pi radians.
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








