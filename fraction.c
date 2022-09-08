#include "fraction.h"

struct fraction multiply_fraction_by_fraction(struct fraction fraction_1 , struct fraction fraction_2){

	struct fraction fraction_res;

	fraction_res.numerador = fraction_1.numerador * fraction_2.numerador;
	fraction_res.denominador = fraction_1.denominador * fraction_2.denominador;

	return fraction_res;
}


struct fraction sum_fraction(struct fraction fraction_1 , struct fraction fraction_2){

	struct fraction fraction_res;

	if(fraction_1.denominador == fraction_2.denominador){
		fraction_res.numerador = fraction_1.numerador + fraction_2.numerador;
		fraction_res.denominador = fraction_1.denominador;
	}else{
		fraction_res.numerador = (fraction_1.numerador * fraction_2.denominador) + (fraction_1.denominador * fraction_2.numerador);
		fraction_res.denominador = fraction_1.denominador * fraction_2.denominador;
	}

	return fraction_res;
	
	
}


int find_mdc(int num1 , int num2){

	int mdc = 1;
	int digit_to_div = 1;

	if(num1 < 0)
		num1 *= -1;
	
	
	while(digit_to_div <= num1 && digit_to_div <= num2){

		if(num1 % digit_to_div == 0 && num2 % digit_to_div == 0){
			mdc = digit_to_div;
		}

		digit_to_div++;
		
	}

	return mdc;
	
}


struct fraction simplify_fraction(struct fraction fraction){

	//ex:  0/N == 0/1 == 0
	if(fraction.numerador == 0){
		fraction.denominador = 1;
		return fraction;
	}

	//ex: -3/-2 == 3/2   ou  3/-2 == -3/2
	if(fraction.denominador < 0){
	        fraction.denominador *= -1;
	        fraction.numerador *= -1;
	}


	//ex: 4/2 == 2 ou  2/4 == 1/2 ou -4/2 == -2
	int mdc = find_mdc(fraction.numerador , fraction.denominador);

	fraction.numerador /= mdc;
	fraction.denominador /= mdc;

    

    return fraction;

}
