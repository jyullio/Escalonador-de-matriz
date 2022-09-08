#ifndef FRACTION_H
#define FRACTION_H

struct fraction{

	int numerador;
	int denominador;

};


struct fraction multiply_fraction_by_fraction(struct fraction fraction_1 , struct fraction fraction_2);
struct fraction sum_fraction(struct fraction fraction_1 , struct fraction fraction_2);
int find_mdc(int num1 , int num2);
struct fraction simplify_fraction(struct fraction fraction);

#endif
