#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>

int main() {
double m1 = 0.02300558; //Mass of first planet (surviving), solar masses
double m2 = 0.012565; //Mass of second planet (engulfed), solar masses
double mstar = 1.531; //Mass of star, solar masses
double a_1 = 0.0841; //Semimajor axis of outer star, AU
double mu_1 = m1/mstar; //Planet-star ratio (planet 1)
double mu_2 = m2/mstar; //Planet-star ratio (planet 2)

double interm = (mu_1 + mu_2)/3.; //Intermediate calc for X
double X = 0.5* pow(interm, 1./3.); //X coefficient
double c = 2. * pow(3.,1./6.) * pow((mu_1 + mu_2),1./3.); //Critical sep. value, AU
double diffc = 2.4 * pow((mu_1 + mu_2), 1./3.);
double div = a_1 * c;
//EDIT POINTNINE FOR CHANGES IN DELTA
////PLANET 2 AS INNER PLANET
double pointnine = 0.1 * c * X;
double equals = (pointnine *a_1) - a_1; //Intermedate calculations for final a_2
double a_2 = equals/(-1. - pointnine);

printf("\nCrit separation distance: %f", c);
printf("\nNew diffc:%f", diffc);
printf("\nSemimajor axis: %f", a_2);
printf("\nScaled: %f", div);

}
