#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct fraction{

	int numerador;
	int denominador;

};


struct fraction **create_matriz(int qtd_row , int qtd_column){

	struct fraction **matriz = (struct fraction **)malloc(sizeof(struct fraction *) * qtd_row);

	if(matriz == NULL){
		return NULL;
	}


	for(int i = 0 ; i < qtd_row ; i++){

		matriz[i] = (struct fraction *)malloc(sizeof(struct fraction) * qtd_column);

		if(matriz[i] == NULL){
			return NULL;
		}

	}

	return matriz;

}

void print_matriz(int qtd_row , int qtd_column , struct fraction **matriz){

	printf("\n\n*******************\n");

	for(int row = 0 ; row < qtd_row ; row++){

		for(int column = 0 ; column < qtd_column ; column++){


			if(matriz[row][column].denominador == 1){
                printf(" %d " , (matriz[row][column]).numerador);
			}else{
                printf(" %d/%d " , (matriz[row][column]).numerador , (matriz[row][column]).denominador);
			}



		}
		printf("\n");

	}
	printf("*******************\n");

}

int mdc(int num1 , int num2){

	int mdc = 1;
	int digit_to_div = 1;

	if(num1 < 0)
		num1 *= -1;
	
	
	printf("\n");
	while(digit_to_div <= num1 || digit_to_div <= num2){

		if(num1 % digit_to_div == 0 && num2 % digit_to_div == 0){
			mdc = digit_to_div;
		}

		digit_to_div++;
		
	}

	return mdc;
	
}


struct fraction simplify_fraction(struct fraction fraction){

	if(fraction.numerador == 0){
		fraction.denominador = 1;
		return fraction;
	}
	
	if(fraction.denominador < 0){
	        fraction.denominador *= -1;
	        fraction.numerador *= -1;
	}


	int num = mdc(fraction.numerador , fraction.denominador);

	fraction.numerador /= num;
	fraction.denominador /= num;

	if(fraction.numerador == 0){
		fraction.denominador = 1;
	}

    

    return fraction;

}

void simplify_fractions_of_row(struct fraction *row_to_simplify , int qtd_column){

    for(int column = 0 ; column < qtd_column ; column++){

		row_to_simplify[column] = simplify_fraction(row_to_simplify[column]);
        

    }


}



void multiply_row_by_fraction(struct fraction *row_to_multiply  , struct fraction *row_res , struct fraction fraction_to_multiply_row , int qtd_column){

	for(int column = 0 ; column < qtd_column ; column++){


        (row_res[column]).numerador = row_to_multiply[column].numerador *fraction_to_multiply_row.numerador;
        (row_res[column]).denominador = row_to_multiply[column].denominador * fraction_to_multiply_row.denominador;




	}

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

void sum_row(struct fraction *row_1 , struct fraction *row_2 , struct fraction *row_res , int qtd_column){

	for(int column = 0 ; column < qtd_column ; column++){

     	row_res[column] = sum_fraction(row_1[column] , row_2[column]);


	}

}


int main(){


	int qtd_row , qtd_column;

	printf("quantidade de linhas :");
	scanf("%d" , &qtd_row);
	printf("quantidade de colunas :");
	scanf("%d" , &qtd_column);



	struct fraction **matriz = create_matriz(qtd_row , qtd_column);
	struct fraction fraction_to_multiply_row;
	struct fraction *row_res = (struct fraction *)malloc(sizeof(struct fraction) * qtd_column);
    struct fraction *row_pivo = (struct fraction *)malloc(sizeof(struct fraction) * qtd_column);

	for(int row = 0 ; row < qtd_row ; row++){

		for(int column = 0 ; column < qtd_column ; column++){

			printf("matriz[%d][%d] = " , row , column);

			if(scanf("%d/%d" , &(matriz[row][column].numerador) , &(matriz[row][column].denominador)) == 1){
                matriz[row][column].denominador = 1;
			}

		}

	}

	print_matriz(qtd_row , qtd_column , matriz);


	for(int column = 0 ; column < (qtd_column - 1) ; column++){//-1 para remover a �ltima coluna dos resultados


		for(int row = 0 ; row < qtd_row ; row++){

			if(row == column){//piv�


                //transformando piv� no n�mero 1
                //piv� = pix� * 1/piv� , assim piv� == 1
				fraction_to_multiply_row.denominador = matriz[row][column].numerador;
				fraction_to_multiply_row.numerador = matriz[row][column].denominador;
				fraction_to_multiply_row = simplify_fraction(fraction_to_multiply_row);

				multiply_row_by_fraction(matriz[row]  , matriz[row] , fraction_to_multiply_row , qtd_column);
				simplify_fractions_of_row(matriz[row] , qtd_column);

                memmove(row_pivo , matriz[row] , sizeof(struct fraction) * qtd_column);

                //print_row(row_pivo , qtd_column);

				print_matriz(qtd_row , qtd_column , matriz);

			}else if(row > column && matriz[row][column].numerador != 0){//inferior

                fraction_to_multiply_row.numerador = -(matriz[row][column].numerador);
                fraction_to_multiply_row.denominador = matriz[row][column].denominador;

                multiply_row_by_fraction(row_pivo  , row_res , fraction_to_multiply_row , qtd_column);

                //print_row(row_res , qtd_column);

                sum_row(row_res , matriz[row] , matriz[row] , qtd_column);

                simplify_fractions_of_row(matriz[row] , qtd_column);

                print_matriz(qtd_row , qtd_column , matriz);

			}



		}


	}




	return 0;
}
