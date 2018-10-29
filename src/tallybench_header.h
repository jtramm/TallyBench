#ifndef __TALLYBENCH_HEADER_H__
#define __TALLYBENCH_HEADER_H__

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<omp.h>
#include<assert.h>

#define EVENT_BASED 1
#define HISTORY_BASED 2

#define SMALL 1
#define MEDIUM 2
#define LARGE 3

typedef struct{
	int  threads;
	int isotopes; // 321
	int assemblies; // 241
	int bins_per_assembly; // Small: 17 x 17 = 289 Medium: x 50 = 14,450
	int particles;
	int events_per_particle; //34
	int total_tallies;
	int simulation_method; // Event or History
	int default_problem;
} Inputs;

// Function Prototypes

// simulation.c
void run_history_based_simulation(Inputs in, double *** tallies, int * num_nucs, int ** mats, double ** concs);

// materials.c
int * load_num_nucs(long isotopes);
int ** load_mats( int * num_nucs, long isotopes );
double ** load_concs( int * num_nucs, unsigned long * seed );
int pick_mat( unsigned long * seed );

// io.c
void logo(int version);
void center_print(const char *s, int width);
void print_results( Inputs in, int mype, double runtime, int nprocs, unsigned long long vhash );
void print_inputs(Inputs in, int nprocs, int version );
void border_print(void);
void fancy_int( long a );
void print_CLI_error(void);
Inputs read_CLI( int argc, char * argv[] );

// xsutils.c
double *** d3darr_contiguous(size_t l, size_t m, size_t n);
double rn(unsigned long * seed);
int rni(unsigned long * seed);
double estimate_mem_usage( Inputs in );

#endif