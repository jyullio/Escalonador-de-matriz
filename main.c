#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct fraction{

	int numerador;
	int denomidador;

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


			if(matriz[row][column].denomidador == 1 || matriz[row][column].numerador == 0){
			
                printf(" %d " , (matriz[row][column]).numerador);
                
			}else{
			
                printf(" %d/%d " , (matriz[row][column]).numerador , (matriz[row][column]).denomidador);
                
			}



		}
		printf("\n");

	}
	printf("*******************\n");

}


void multiply_row_by_fraction(struct fraction *row_to_multiply  , struct fraction *row_res , struct fraction fraction_to_multiply_row , int qtd_column){

	for(int column = 0 ; column < qtd_column ; column++){

        (row_res[column]).numerador = row_to_multiply[column].numerador *fraction_to_multiply_row.numerador;
        (row_res[column]).denomidador = row_to_multiply[column].denomidador * fraction_to_multiply_row.denomidador;

	}

}

void simplify_fractions_of_row(struct fraction *row_to_simplify , int qtd_column){

    for(int column = 0 ; column < qtd_column ; column++){


        if(row_to_simplify[column].numerador != 0 && (row_to_simplify[column]).numerador % (row_to_simplify[column]).denomidador == 0){
        
            (row_to_simplify[column]).numerador /= (row_to_simplify[column]).denomidador;
            (row_to_simplify[column]).denomidador = 1;
            
        }

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


int main(){


	int qtd_row , qtd_column;

	printf("quantidade de linhas :");
	scanf("%d" , &qtd_row);
	printf("quantidade de colunas :");
	scanf("%d" , &qtd_column);



	struct fraction **matriz = create_matriz(qtd_row , qtd_column);
	struct fraction fraction_to_multiply_row;
	struct fraction *row_res = (struct fraction *)malloc(sizeof(struct fraction) * qtd_column);
	
   	
	for(int row = 0 ; row < qtd_row ; row++){

		for(int column = 0 ; column < qtd_column ; column++){

			printf("matriz[%d][%d] = " , row , column);

			if(scanf("%d/%d" , &(matriz[row][column].numerador) , &(matriz[row][column].denomidador)) == 1){
                matriz[row][column].denomidador = 1;
			}

		}

	}

	print_matriz(qtd_row , qtd_column , matriz);



	int row_of_pivo;
	for(int column = 0 ; column < (qtd_column - 1) ; column++){//-1 para remover a �ltima coluna dos resultados


		for(int row = 0 ; row < qtd_row ; row++){

			if(row == column){//piv�


                //transformando piv� no n�mero 1
                //piv� = pix� * 1/piv� , assim piv� == 1
				fraction_to_multiply_row.denomidador = matriz[row][column].numerador;
				fraction_to_multiply_row.numerador = matriz[row][column].denomidador;
				multiply_row_by_fraction(matriz[row]  , matriz[row] , fraction_to_multiply_row , qtd_column);
				simplify_fractions_of_row(matriz[row] , qtd_column);

                row_of_pivo = row;//salvando linha que o pivô se encontra
                

				print_matriz(qtd_row , qtd_column , matriz);

			}else if(row > column && matriz[row][column].numerador != 0){//inferior

                fraction_to_multiply_row.numerador = -(matriz[row][column].numerador);
                fraction_to_multiply_row.denomidador = matriz[row][column].denomidador;

                multiply_row_by_fraction(matriz[row_of_pivo]  , row_res , fraction_to_multiply_row , qtd_column);

                sum_row(row_res , matriz[row] , matriz[row] , qtd_column);

                simplify_fractions_of_row(matriz[row] , qtd_column);

                print_matriz(qtd_row , qtd_column , matriz);

			}



		}


	}




	return 0;
}
