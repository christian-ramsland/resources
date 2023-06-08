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
	obj_t v1;
	num_t dt;
	dim_t m, n;
	inc_t rs, cs;

	dt = BLIS_DOUBLE;
	m = 4; n = 3;
	rs = 1; cs = 6;
	bli_obj_create( dt, m, n, rs, cs, &a1);
	inspect_matrix(a1);
	return 0;
}

