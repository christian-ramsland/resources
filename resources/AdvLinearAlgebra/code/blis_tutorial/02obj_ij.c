#include <stdio.h>
#include <stdlib.h>
#include "blis.h"
#include <tensorflow/c/c_api.h>

void init_dmatrix_by_rows(dim_t m, dim_t n, double* a, inc_t rs, inc_t cs);
void init_dmatrix_by_cols(dim_t m, dim_t n, double* a, inc_t rs, inc_t cs);
void init_dobj_by_cols(obj_t* a);
void init_zobj_by_cols(obj_t* a);

int main(int argc, char** argv) {
	printf("Hello from TensorFlow C library version %s\n", TF_Version());



    obj_t a1, a2, a3;
    num_t dt;
    dim_t m, n;
    inc_t rs, cs;
    dim_t i, j;

    printf("example 1: create an object and then individually access/view some of its elements.\n");
    dt = BLIS_DOUBLE;
    m = 4, n = 5; rs = 1; cs = m;
    double* p1 = malloc(m * n * sizeof(double));
    init_dmatrix_by_cols(m, n, p1, rs, cs);
    bli_obj_create_with_attached_buffer(dt, m, n, p1, rs, cs, &a1);

    printf("printing matrix first:\n");
    bli_printm("matrix 'a1' (initial state)", &a1, "%5.1f", "");

    // access individual elements by specifying their offsets. broken up into real and imaginary components.
    i = 1; j = 3;
    double alpha_r, alpha_i;
    bli_getijm(i, j, &a1, &alpha_r, &alpha_i);

    // alpha_r, alpha_i are what are "returned by bli_getijm()"

    printf( "element (%2d,%2d) of matrix 'a1' (real + imag): %5.1f + %5.1f\n", ( int )i, ( int )j, alpha_r, alpha_i );

    printf("example 2: modify individual elements of an existing matrix.\n");
    alpha_r = -3.0; alpha_i = 0.0; i = 1; j = 3;
    bli_setijm(alpha_r, alpha_i, i, j, &a1);

    bli_printm("matrix a1 (modified)", &a1, "%5.1f", "");
    printf("create a regular object with a buffer and initialize its elements using bli_setijm()");
    bli_obj_create(dt, m, n, rs, cs, &a2);
    init_dobj_by_cols(&a2);
    printf("a2 was initialized in the same way as a1, so it should print as the same initial state (unnecessary remark?)\n");
    bli_printm( "matrix 'a2'", &a2, "%5.1f", "" );

    printf("example 3: modify elements of complex matrix\n");
    dt = BLIS_DCOMPLEX;
	bli_obj_create( dt, m, n, rs, cs, &a3 );

	init_zobj_by_cols( &a3 );

    bli_printm( "matrix 'a3' (initial state)", &a3, "%5.1f", "" );

    i = 3; j = 0;
	bli_getijm( i, j, &a3, &alpha_r, &alpha_i );
	alpha_r *= -1.0; alpha_i *= -1.0;
	bli_setijm( alpha_r, alpha_i, i, j, &a3 );

	bli_printm( "matrix 'a3' (modified state)", &a3, "%5.1f", "" );
    printf("so the real and complex portions at r0, c3 were both multiplied by 1.\n");
    
    free( p1 );

    bli_obj_free( &a2 );
	bli_obj_free( &a3 );
    return 0;
}


void init_dmatrix_by_rows( dim_t m, dim_t n, double* a, inc_t rs, inc_t cs )
{
	dim_t  i, j;

	double alpha = 0.0;

	// Step through a matrix by rows, assigning each element a unique
	// value, starting at 0.
	for ( i = 0; i < m; ++i )
	{
		for ( j = 0; j < n; ++j )
		{
			double* a_ij = a + i*rs + j*cs;

			*a_ij = alpha;

			alpha += 1.0;
		}
	}
}

void init_dmatrix_by_cols( dim_t m, dim_t n, double* a, inc_t rs, inc_t cs )
{
	dim_t  i, j;

	double alpha = 0.0;

	// Step through a matrix by columns, assigning each element a unique
	// value, starting at 0.
	for ( j = 0; j < n; ++j )
	{
		for ( i = 0; i < m; ++i )
		{
			double* a_ij = a + i*rs + j*cs;

			*a_ij = alpha;

			alpha += 1.0;
		}
	}
}

void init_dobj_by_cols( obj_t* a )
{
	dim_t m = bli_obj_length( a );
	dim_t n = bli_obj_width( a );
	dim_t i, j;

	double alpha = 0.0;

	// Step through a matrix by columns, assigning each element a unique
	// value, starting at 0.
	for ( j = 0; j < n; ++j )
	{
		for ( i = 0; i < m; ++i )
		{
			bli_setijm( alpha, 0.0, i, j, a );

			alpha += 1.0;
		}
	}
}

void init_zobj_by_cols( obj_t* a )
{
	dim_t m = bli_obj_length( a );
	dim_t n = bli_obj_width( a );
	dim_t i, j;

	double alpha = 0.0;

	// Step through a matrix by columns, assigning each real and imaginary
	// element a unique value, starting at 0.
	for ( j = 0; j < n; ++j )
	{
		for ( i = 0; i < m; ++i )
		{
			bli_setijm( alpha, alpha + 1.0, i, j, a );

			alpha += 2.0;
		}
	}
}
