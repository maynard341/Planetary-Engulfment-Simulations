#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "/mnt/research/planets/olivia/rebound/rebound/rebound.h"
#include "/mnt/research/planets/olivia/reboundx/reboundx/reboundx.h"

//Global variables
const double J2 = 4.27134E-6;
const double Rstar = 0.010337989;
const double tmax = 1000;
const double tout = 0.0005;
const double ObliquityStar = 0;
const char* outname;

int main(int argc, char* argv[]) {

//Timing, to clock time for SLURM script: 
clock_t begin = clock();

//Random seed for random parameter generation
srand(time(NULL));

struct reb_simulation* r = reb_create_simulation();

//Two arguments are passed in through command line arguments.
char* inname;
inname = malloc((strlen(argv[1]) + 10) * sizeof(char));
inname = argv[1]; //The first arg is the name of the input file.
char* outchar;
outchar = malloc((strlen(argv[2]) + 10) * sizeof(char));
outchar = argv[2]; //The second arg is the name of the output files - extension of "p1.txt" and "p2.txt" is added later.
outname = outchar;
char p1inname[20];
char p2inname[20];
sprintf(p1inname, "./%s/%s_p1.in", outname, inname); //Filepath created for the planet 1 input file.
sprintf(p2inname, "./%s/%s_p2.in", outname, inname); //Filepath created for the planet 2 input file.
printf("\n"); printf("-------------------------------------------------------"); printf("\n");
printf("\nPlanet 1 file name: \n%s", p1inname);
printf("\nPlanet 2 file name: \n%s", p2inname);

//Star variables (Body 1)
	FILE *file1;
	file1 = fopen("star.in", "r"); //Open file
	if (file1 == NULL) {
		printf("Star file could not open.\n");
		return 0;
	}
	int j = 0;
	float array[30] = {0};
	float number = 0;
	printf("\nStar parameters:");
	while (!feof(file1)) { //Print float values to array
		fscanf(file1, "%f", &number);
		array[j] = number;
		//printf("%.4f\n", array[j]);
		j++;
	}
	fclose(file1);
        double Mstar = array[0]; //Mass, solar mass
        double Rstar = array[1]; //Radius, AU
	//Print statements to be useful
	printf("\nMass of star: %f", Mstar);
	printf("\nRadius of star: %f", Rstar);
	printf("\n");
//Planet 1 variables (Body 2)
	FILE *file2;
	file2 = fopen(p1inname, "r");
	if (file2 == NULL) {
                printf("Planet 1 file could not open.\n");
                return 0;
        }
	j = 0;
	number = 0;
	printf("\nP1 parameters:\n");
	while (!feof(file2)) {
		fscanf(file2, "%f", &number);
		array[j] = number;
		//printf("%.4f\n", array[j]);
		j++;
	}
	fclose(file2);
        double M_1 = array[0]; //Mass, solar mass
        double R_1 = array[1]; //Radius, AU
	double a_1 = array[2]; //Semimajor axis, AU
        double e_1 = array[3]; //Eccentricity, unitless
        double i_1 = array[4]*M_PI/180.; //Inclination, input as degrees and converted to radians
        double co_1 = array[5]; //Longitude of ascending node, in radians
        double om_1 = array[6]; //Argument of pericenter, in radians
        double f_1 = array[7]; //True anomaly, in radians
	
	printf("\nMass of first planet: %f", M_1);
	printf("\nRadius of first planet: %f", R_1);
	printf("\nSemimajor axis of first planet: %f", a_1);
	printf("\nEcc: %f", e_1);
	printf("\nInclination: %f", i_1);
	printf("\nLong: %f", co_1);
	printf("\nPeri: %f", om_1);
	printf("\nAnomaly: %f", f_1);
	printf("\n");
	
//Planet 2 variables (Body 3)
	FILE *file3;
	file3 = fopen(p2inname, "r");
	if (file3 == NULL) {
                printf("Planet 2 file could not open.\n");
                return 0;
        }
	j = 0;
	number = 0;
	printf("\nP2 parameters:\n");
	while (!feof(file3)) {
		fscanf(file3, "%f", &number);
		array[j] = number;
		//printf("%.4f\n", array[j]);
		j++;
	}
	fclose(file3);
        double M_2 = array[0]; //Mass, solar mass
        double R_2 = array[1]; //Radius, AU
	double a_2 = array[2]; //Semimajor axis, AU
	//a_2 = a_2 * 2; //Just doubling it to see what happens
        double e_2 = array[3]; //Eccentricity, unitless
        double i_2 = array[4]*M_PI/180.; //Inclination, input as degrees and converted to radians
	double co_2 = array[5]; //Longitude of ascending node, in radians
        double om_2 = array[6]; //Argument of pericenter, in radians
        double f_2 = array[7]; //True anomaly, in radians

         printf("\nMass of second planet: %f", M_2);
         printf("\nRadius of second planet: %f", R_2);
         printf("\nSemimajor axis of second planet: %f", a_2);
         printf("\nEcc: %f", e_2);
         printf("\nInclination: %f", i_2);
         printf("\nLong: %f", co_2);        
	 printf("\nPeri: %f", om_2);
         printf("\nAnomaly: %f", f_2);
	 printf("\n");
//Declare functions
	void heartbeat(struct reb_simulation* r); //Prints to the screen
	void force_J2(struct reb_simulation* r); //Gets J2 external force

//Declare simulation parameters
	r->integrator = REB_INTEGRATOR_IAS15; //IAS15
	r->dt = 1e-8;
	r->N_active = 3;
	r->G = 4*(pow(M_PI,2.));

//Adding simulation elements
	reb_add_fmt(r, "m r", Mstar, Rstar); //Star - particles[0]
	reb_add_fmt(r, "m r a e inc Omega omega f", M_1, R_1, a_1, e_1, i_1, co_1, om_1, f_1); //First planet - particles[1]
	reb_add_fmt(r, "m r a e inc Omega omega f", M_2, R_2, a_2, e_2, i_2, co_2, om_2, f_2); //Second planet - particles[2]


//General Relativity

	struct rebx_extras* rebx = rebx_attach(r);
	struct rebx_force* gr = rebx_load_force(rebx, "gr");
	rebx_add_force(rebx, gr);
	rebx_set_param_double(rebx, &gr->ap, "c", 63240.2);
	double* c = rebx_get_param(rebx, gr->ap, "c");
	//printf("%f\n", *c);

//Deleting files (doesn't currently work because of weird file permissions; working on it.)
	char planet1out[20];
        char planet2out[20];
        sprintf(planet1out, "./%s/%s_p1.txt", outname, outname);
        sprintf(planet2out, "./%s/%s_p2.txt", outname, outname);
	/*system(planet1out); //Deletes old file
	system(planet2out);
	remove(planet1out);
	remove(planet2out);*/
	
//Integration
	reb_move_to_com(r); //Move to center of mass
	r->heartbeat = heartbeat; //Add functions
	r->additional_forces = force_J2;
	reb_integrate(r, tmax);
	reb_free_simulation(r); //Free memory
	rebx_free(rebx);

//End timing for run
clock_t end = clock();
double time = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\nTIME FOR RUN: %f seconds\n", time);


}

void force_J2(struct reb_simulation* r) {
	/*double J2 = r->J2;
	double Rstar = r->Rstar;
	double ObliquityStar = r->ObliquityStar;*/
 
       if (J2==0) return;

        const struct reb_particle star = r->particles[0]; //Star            // cache
        const int N = r->N; //Number of particles in the system ?
#pragma omp parallel for //Code segment will be executed by multiple threads
        for (int i=1;i<N;i++){
                const struct reb_particle p = r->particles[i];  // cache
                const double sprx = p.x-star.x;
                const double spry = p.y-star.y;
                const double sprz = p.z-star.z;
                const double prx  = sprx*cos(-ObliquityStar) + sprz*sin(-ObliquityStar);
                const double pry  = spry;
                const double prz  =-sprx*sin(-ObliquityStar) + sprz*cos(-ObliquityStar);
                const double pr2  = prx*prx + pry*pry + prz*prz;                // distance^2 relative to planet
                const double fac  = 3.*r->G*J2*star.m*Rstar*Rstar/2./pow(pr2,3.5);

                const double pax  = fac*prx*(prx*prx + pry*pry - 4.*prz*prz);
                const double pay  = fac*pry*(prx*prx + pry*pry - 4.*prz*prz);
                const double paz  = fac*prz*(3.*(prx*prx + pry*pry) - 2.*prz*prz);

                r->particles[i].ax += pax*cos(ObliquityStar) + paz*sin(ObliquityStar);
                r->particles[i].ay += pay;
                r->particles[i].az +=-pax*sin(ObliquityStar) + paz*cos(ObliquityStar);
        }
}

void heartbeat(struct reb_simulation* r){

	if(reb_output_check(r, (tmax/100))){                           //Triggers output at regular time intervals.  output something to screen

                reb_output_timing(r, tmax);

        }
        if(reb_output_check(r, tout)){                           // output semimajor axis to file
		
		char planet1out[20]; //Create arrays
		char planet2out[20];

		sprintf(planet1out, "./%s/%s_p1.txt", outname, outname); //Create file names
		sprintf(planet2out, "./%s/%s_p2.txt", outname, outname);
		
		FILE* file1 = fopen(planet1out, "a"); //Open files to append data 
		FILE* file2 = fopen(planet2out, "a");
                
		const struct reb_particle star = r->particles[0]; //Set up simulation
                const int N = r->N;

		struct reb_orbit p1 = reb_tools_particle_to_orbit(r->G, r->particles[1],star);
                float p1_dist = sqrt(pow(r->particles[1].x, 2) + pow(r->particles[1].y, 2) + pow(r->particles[1].z, 2));
		float p1_peridist = p1.a*(1. - p1.e);
                fprintf(file1,"%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",r->t,p1.a,p1.e,p1.inc*(180./M_PI), p1.Omega*(180./M_PI), p1.omega*(180./M_PI), p1.f*(180./M_PI), p1_dist, p1_peridist);

		struct reb_orbit p2 = reb_tools_particle_to_orbit(r->G, r->particles[2],star);
		float p2_dist = sqrt(pow(r->particles[2].x, 2) + pow(r->particles[2].y, 2) + pow(r->particles[2].z, 2));
		float p2_peridist = p2.a*(1. - p2.e);
                fprintf(file2,"%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\t%.15e\n",r->t,p2.a,p2.e,p2.inc*(180./M_PI), p2.Omega*(180./M_PI), p2.omega*(180./M_PI), p2.f*(180./M_PI), p2_dist, p2_peridist);
		

			//1. Current sim time //2. Semimajor axis //3. Eccentricity //4. Inclination
			//5. Inclination of ascending node //6. Argument of pericenter //7. True anomaly
			//4, 5, 6 and 7 are converted to degrees for output            
		fclose(file1);
		fclose(file2);
	 }
}
