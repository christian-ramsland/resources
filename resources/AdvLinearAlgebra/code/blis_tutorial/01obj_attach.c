

#include<stdio.h>
#include<stdlib.h>
#include "blis.h"

void init_dmatrix_by_rows( dim_t m, dim_t n, double* a, inc_t rs, inc_t cs);
void init_dmatrix_by_cols( dim_t m, dim_t n, double* a, inc_t rs, inc_t cs);

int main( int argc, char** argv) {
    obj_t a1, a2;
    num_t dt;
    dim_t m, n;
    inc_t rs, cs;

    // demonstrates interfacing external or existing buffers with BLIS objects.

    printf("example 1: create bufferless object and then attach an external buffer to it, specifying column storage.\n");

    dt = BLIS_DOUBLE;
    m = 4; n = 5; rs = 1; cs = m;
    double* p1 = malloc(m * n * sizeof(double));
    init_dmatrix_by_cols(m, n, p1, rs, cs);

    // this is an alternative to bli_obj_create, which automatically create an array large enough to hold all the elements
    // can also create a "bufferless" object and attach our own buffer to that object.
    // if you're interfacing blis objects with an existing application that produces its own matrix arrays/buffers
    bli_obj_create_without_buffer(dt, m, n, &a1);
    // bli_printm( "matrix 'a1' contents:", &a1, "%4.1f", "" ); 
    // just seeing what will happen ^ error "encountered object with non-zero dimensions containing null buffer
    
    // not sure what's going to happen here.
    bli_obj_attach_buffer(p1, rs, cs, 0, &a1);

    // so if there's an imaginary stride that's the fourth arg for the function below, always specify as 0
    // then we're supposed to print

    bli_printm( "matrix 'a1', initialized by columns:", &a1, "%5.1f", "" );
    
    printf("example 2: create a bufferless object and then attach an external buffer to it, specifying row storage\n");
    double* p2 = malloc(m * n * sizeof(double)); // forgot malloc haha
    init_dmatrix_by_rows(m, n, p2, rs, cs);

    // the function below is just a convenience function for bli_obj_create_without_buffer(..., &a0) and bli_obj_attach_buffer(..., 0, &a0) 
    bli_obj_create_with_attached_buffer(dt, m, n, p2, rs, cs, &a2);
    // and then print our new a2 object
    bli_printm( "matrix 'a2', initialized by rows:", &a2, "%5.1f", "" );

    free(p1);
    free(p2);

	// Please note that after creating an object via either of:
	// - bli_obj_create_without_buffer(), or
	// - bli_obj_create_with_attached_buffer()
	// we do NOT free it! That's because these functions merely initialize the
	// object and do not actually allocate any memory.

    // bli_obj_free( &a1 );
	// bli_obj_free( &a2 );
    /* so I guess what I tried to do above is wrong? */

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
