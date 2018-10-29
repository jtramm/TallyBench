#include "tallybench_header.h"

double pairwise_sum_dbl( double * v, long len )
{
	double sum = 0;
	if( len <= 16 )
	{
		for( long i = 0; i < len; i++ )
			sum += v[i];
	}
	else
	{
		long left_len = len / 2;
		long right_len = len - left_len;
		double left_sum = pairwise_sum_dbl( v, left_len );
		double right_sum = pairwise_sum_dbl( v+left_len, right_len );
		sum += left_sum + right_sum;
	}
	return sum;
}

double *** d3darr_contiguous(size_t l, size_t m, size_t n)
{
    int i, j;
    double *inner = calloc(l*m*n,sizeof(double));
	assert(inner != NULL );
    double **middle = malloc(l*m*sizeof(double*));
	assert(middle != NULL);
    double ***matrix = malloc(l*sizeof(double**));
	assert(matrix != NULL);

    for(i=0; i<l; i++){
        matrix[i] = middle;
        middle += m;
        for(j=0; j<m; j++){
            matrix[i][j] = inner;
            inner += n;
        }
    }
    return matrix;
}

// Park & Miller Multiplicative Conguential Algorithm
// From "Numerical Recipes" Second Edition
double rn(unsigned long * seed)
{
	double ret;
	unsigned long n1;
	unsigned long a = 16807;
	unsigned long m = 2147483647;
	n1 = ( a * (*seed) ) % m;
	*seed = n1;
	ret = (double) n1 / m;
	return ret;
}

int rni(unsigned long * seed)
{
	int ret;
	unsigned long n1;
	unsigned long a = 16807;
	unsigned long m = 2147483647;
	n1 = ( a * (*seed) ) % m;
	*seed = n1;
	ret = n1 % m;
	return ret;
}

unsigned int hash(char *str, int nbins)
{
	unsigned int hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c;

	return hash % nbins;
}

double estimate_mem_usage( Inputs in )
{
	// Number of tally elements
	size_t memtotal = (size_t) in.assemblies * (size_t) in.bins_per_assembly * (size_t) in.isotopes;

	// In bytes
	memtotal *= sizeof(double);

	// In MB
	double MB = (double) memtotal / 1024.0 / 1024.0 ;

	return MB;
}
