#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fraction.h"
#include "row.h"


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


	for(int column = 0 ; column < (qtd_column - 1) ; column++){//-1 para remover a última coluna dos resultados


		for(int row = 0 ; row < qtd_row ; row++){

			if(row == column){//pivô


                //transformando pivô no nômero 1
                //pivô = pixô * 1/pivô , assim pivô == 1
				fraction_to_multiply_row.denominador = matriz[row][column].numerador;
				fraction_to_multiply_row.numerador = matriz[row][column].denominador;
				fraction_to_multiply_row = simplify_fraction(fraction_to_multiply_row);

				multiply_row_by_fraction(matriz[row]  , matriz[row] , fraction_to_multiply_row , qtd_column);
				simplify_fractions_of_row(matriz[row] , qtd_column);

                memmove(row_pivo , matriz[row] , sizeof(struct fraction) * qtd_column);//"salvando" linha que apresenta o pivô


				print_matriz(qtd_row , qtd_column , matriz);

			}else if(row > column && matriz[row][column].numerador != 0){//matriz inferior

                fraction_to_multiply_row.numerador = -(matriz[row][column].numerador);
                fraction_to_multiply_row.denominador = matriz[row][column].denominador;

                multiply_row_by_fraction(row_pivo  , row_res , fraction_to_multiply_row , qtd_column);


                sum_row(row_res , matriz[row] , matriz[row] , qtd_column);

                simplify_fractions_of_row(matriz[row] , qtd_column);

                print_matriz(qtd_row , qtd_column , matriz);

			}



		}


	}




	return 0;
}
