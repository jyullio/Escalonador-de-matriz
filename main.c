#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct fraction{

	int numerador;
	int denomidador;

};

float *sum_temp_row_1 = NULL;
float *sum_temp_row_2 = NULL;
float *mul_temp_row = NULL;
float *linha_do_pivo = NULL;



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


			if(matriz[row][column].denomidador == 1){
                printf(" %d " , (matriz[row][column]).numerador);
			}else{
                printf(" %d/%d " , (matriz[row][column]).numerador , (matriz[row][column]).denomidador);
			}



		}
		printf("\n");

	}
	printf("*******************\n");

}

void simplify_fractions_of_row(struct fraction *row_to_simplify , int qtd_column){

    for(int column = 0 ; column < qtd_column ; column++){


        if(row_to_simplify[column].numerador != 0 && (row_to_simplify[column]).numerador % (row_to_simplify[column]).denomidador == 0){
            (row_to_simplify[column]).numerador /= (row_to_simplify[column]).denomidador;
            (row_to_simplify[column]).denomidador = 1;
        }

        if(row_to_simplify[column].numerador == 0){
            row_to_simplify[column].denomidador = 1;
        }

    }


}

struct fraction simplyfy_fraction(struct fraction fraction){

    if(fraction.denomidador < 0){
        fraction.denomidador *= -1;
        fraction.numerador *= -1;
    }

    return fraction;

}

void multiply_row_by_fraction(struct fraction *row_to_multiply  , struct fraction *row_res , struct fraction fraction_to_multiply_row , int qtd_column){

	for(int column = 0 ; column < qtd_column ; column++){


        (row_res[column]).numerador = row_to_multiply[column].numerador *fraction_to_multiply_row.numerador;
        (row_res[column]).denomidador = row_to_multiply[column].denomidador * fraction_to_multiply_row.denomidador;




	}

}



void sum_row(struct fraction *row_1 , struct fraction *row_2 , struct fraction *row_res , int qtd_column){

	for(int column = 0 ; column < qtd_column ; column++){

        if(row_1[column].denomidador == row_2[column].denomidador){
            row_res[column].numerador = row_1[column].numerador + row_2[column].numerador;
            row_res[column].denomidador = row_1[column].denomidador;
        }else{

            row_res[column].numerador = ((row_1[column].numerador * row_2[column].denomidador) + (row_2[column].numerador * row_1[column].denomidador));
            row_res[column].denomidador = row_1[column].denomidador * row_2[column].denomidador;

        }






	}

}

void print_row(struct fraction *row , int qtd_column){

    printf("\n\n***\n");
    for(int column = 0 ; column < qtd_column ; column++){

        printf(" %d/%d " , row[column].numerador , row[column].denomidador);
    }
    printf("\n***\n");
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

			if(scanf("%d/%d" , &(matriz[row][column].numerador) , &(matriz[row][column].denomidador)) == 1){
                matriz[row][column].denomidador = 1;
			}

		}

	}

	print_matriz(qtd_row , qtd_column , matriz);


	for(int column = 0 ; column < (qtd_column - 1) ; column++){//-1 para remover a última coluna dos resultados


		for(int row = 0 ; row < qtd_row ; row++){

			if(row == column){//pivô


                //transformando pivô no número 1
                //pivô = pixô * 1/pivô , assim pivô == 1
				fraction_to_multiply_row.denomidador = matriz[row][column].numerador;
				fraction_to_multiply_row.numerador = matriz[row][column].denomidador;
				fraction_to_multiply_row = simplyfy_fraction(fraction_to_multiply_row);

				multiply_row_by_fraction(matriz[row]  , matriz[row] , fraction_to_multiply_row , qtd_column);
				simplify_fractions_of_row(matriz[row] , qtd_column);

                memmove(row_pivo , matriz[row] , sizeof(struct fraction) * qtd_column);

                //print_row(row_pivo , qtd_column);

				print_matriz(qtd_row , qtd_column , matriz);

			}else if(row > column && matriz[row][column].numerador != 0){//inferior

                fraction_to_multiply_row.numerador = -(matriz[row][column].numerador);
                fraction_to_multiply_row.denomidador = matriz[row][column].denomidador;

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
