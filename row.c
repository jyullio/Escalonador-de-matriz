#include "row.h"


void simplify_fractions_of_row(struct fraction *row , int qtd_column){

    for(int column = 0 ; column < qtd_column ; column++){

		row[column] = simplify_fraction(row[column]);
        

    }


}




void multiply_row_by_fraction(struct fraction *row  , struct fraction *row_res , struct fraction fraction_to_multiply , int qtd_column){

	for(int column = 0 ; column < qtd_column ; column++){


        row_res[column] = multiply_fraction_by_fraction(row[column] , fraction_to_multiply);
		
	}

}




void sum_row(struct fraction *row_1 , struct fraction *row_2 , struct fraction *row_res , int qtd_column){

	for(int column = 0 ; column < qtd_column ; column++){

     	row_res[column] = sum_fraction(row_1[column] , row_2[column]);
		

	}

}

