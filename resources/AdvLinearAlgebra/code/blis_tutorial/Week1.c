#include<stdio.h>
#include<stdlib.h>
#include "blis.h"

void Problem1111();

int main(int argc, char** argv) {
    Problem1111();
    return 0;
}

void Problem1111() {
    // Example 1: Perform a general matrix-matrix multiply (gemm) operation.
    dim_t m, n, k;
	inc_t rsa, csa;
	inc_t rsb, csb;
	inc_t rsc, csc;
    double* a;
	double* b;
	double* c;
	double  alpha, beta;
    obj_t matA, matB, matC;
    
    num_t dt = BLIS_DOUBLE;

    // Create some matrix and vector operands to work with.
    m = 3; n = 3; k = 1;
	rsc = 1; csc = m;
	rsa = 1; csa = m;
	rsb = 1; csb = k;
    inc_t rs = 1, cs = m;

	c = malloc( m * n * sizeof( double ) );
	a = malloc( m * k * sizeof( double ) );
	b = malloc( k * n * sizeof( double ) );

    double aValues[9] = {1.0, -2.0, 1.0, 0, -1.0, -1.0, 0, 0, 2.0};
    double bValues[3] = {-1.0, 2.0, 1.0};

    bli_obj_create( dt, m, n, rs, cs, &matA );
	bli_obj_create( dt, m, k, rs, cs, &matB );

    bli_obj_attach_buffer(aValues, rs, cs, 0, &matA);
    bli_obj_attach_buffer(bValues, rs, cs, 0, &matB);

	bli_dprintm( "matrix A: ", m, k, a, rsa, csa, "%4.1f", "" );
    bli_dprintm( "matrix B: ", m, k, a, rsa, csa, "%4.1f", "" );

    // Set the scalars to use.
	alpha = 1.0;
	beta  = 1.0;




}