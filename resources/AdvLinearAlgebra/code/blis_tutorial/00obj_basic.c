#include <stdio.h>
#include "blis.h"

void inspect_matrix(obj_t a8) {
	printf( "datatype            %s\n", bli_dt_string( bli_obj_dt( &a8 ) ) );
	printf( "datatype size       %d bytes\n", ( int )bli_dt_size( bli_obj_dt( &a8 ) ) );
	printf( "m dim (# of rows):  %d\n", ( int )bli_obj_length( &a8 ) );
	printf( "n dim (# of cols):  %d\n", ( int )bli_obj_width( &a8 ) );
	printf( "row stride:         %d\n", ( int )bli_obj_row_stride( &a8 ) );
	printf( "col stride:         %d\n", ( int )bli_obj_col_stride( &a8 ) );
}

int main(int argc, char** argv) {
	obj_t a1;
	num_t dt;
	dim_t m, n;
	inc_t rs, cs;

	printf("example 1: 4x3 matrix of double precision floating point real elements in stored in column-major order.\n");

	dt = BLIS_DOUBLE;
	m = 4; n = 3;
	rs = 1; cs = 4;
	bli_obj_create( dt, m, n, rs, cs, &a1);
	// inspect_matrix(a1);
	
	printf("allocate extra rows beyond the lower edge of the matrix by providing cs > m\n");
	cs = 6;
	obj_t a2;
	bli_obj_create( dt, m, n, rs, cs, &a2);
	// inspect_matrix(a2);

	
	printf("example 2: 4x3 matrix in row-major order\n");
	obj_t a3;
	dt = BLIS_DOUBLE; m  = 4; n  = 3;
	rs = 3; cs = 1; 
	bli_obj_create( dt, m, n, rs, cs, &a3 );
	// inspect_matrix(a3);


	printf("allocate extra columns (five extra here) beyond the right edge of the matrix\n");
	obj_t a4;
	dt = BLIS_DOUBLE; m  = 4; n  = 3;
	rs = 8; cs = 1;
	bli_obj_create( dt, m, n, rs, cs, &a4 );
	// inspect_matrix(a4);

	printf("example 3: other floating point datatypes\n");
	obj_t a5, a6, a7;
	m  = 4; n  = 3;
	rs = 1; cs = 4; 
	bli_obj_create( BLIS_FLOAT,    m, n, rs, cs, &a5 );
	bli_obj_create( BLIS_SCOMPLEX, m, n, rs, cs, &a6 );
	bli_obj_create( BLIS_DCOMPLEX, m, n, rs, cs, &a7 );


	printf("example 4: default column storage that avoids row and column stride\n");
	obj_t a8;
	bli_obj_create( BLIS_FLOAT, 3, 5, 0, 0, &a8 );
	printf("example 5: the 3x5 matrix created as a8 may have row stride greater than 3, check with my inspect matrix function\n");
	inspect_matrix(a8);

	printf("example 6: not interesting\n");

	
	printf("example 7: initialize an object's elements to random values and then print the matrix\n");
	obj_t a9;
	bli_obj_create( BLIS_DOUBLE,   3, 5, 0, 0, &a9 );
	bli_randm(&a9);
	bli_printm( "matrix 'a9' contents:", &a9, "%4.1f", "" );


	printf("example 8: randomize and then print an object containing a complex matrix\n");
	obj_t a11;
	bli_obj_create( BLIS_DCOMPLEX, 3, 5, 0, 0, &a11 );
	bli_randm(&a11);
	bli_printm( "matrix 'a11' contents (complex):", &a11, "%4.1f", "" );


	printf("example 9: create, randomize and print vector objects\n");
	obj_t v1, v2;
	bli_obj_create( BLIS_DOUBLE, 4, 1, 0, 0, &v1 );
	bli_obj_create( BLIS_DOUBLE, 1, 6, 0, 0, &v2 );
	// bli_randm would work just as well since any vector is also a matrix
	bli_randv( &v1 );
	bli_randv( &v2 );

	bli_printm( "vector 'v1' contents:", &v1, "%5.1f", "" );
	bli_printm( "vector 'v2' contents:", &v2, "%5.1f", "" );

	// oh I forgot about this shit
	bli_obj_free( &a1 );
	bli_obj_free( &a2 );
	bli_obj_free( &a3 );
	bli_obj_free( &a4 );
	bli_obj_free( &a5 );
	bli_obj_free( &a6 );
	bli_obj_free( &a7 );
	bli_obj_free( &a8 );
	bli_obj_free( &a9 );
	bli_obj_free( &a11 );
	bli_obj_free( &v1 );
	bli_obj_free( &v2 );


	return 0;
}

