#ifndef ROW_H
#define ROW_H

#include "fraction.h"

void simplify_fractions_of_row(struct fraction *row , int qtd_column);
void multiply_row_by_fraction(struct fraction *row  , struct fraction *row_res , struct fraction fraction_to_multiply , int qtd_column);
void sum_row(struct fraction *row_1 , struct fraction *row_2 , struct fraction *row_res , int qtd_column);

#endif
