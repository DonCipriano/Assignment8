#include <stdio.h>
#include <stdlib.h>

struct graph{
	int no_elems;

//matricea de adiacenta in loc de 1 va contine distanta drumului care va fi mai mare si diferita fata de 0
	int *ad_matrix;
};

void random_graph( struct graph* graph1){
	int i;
	int k;
	int flag;

	//parcurge randurile si coloanele matricei de adiacenta
	for( k = 0; k < graph1 -> no_elems; k++ ){
		for( i = 0; i < graph1 -> no_elems; i++){
			//verifica daca pozitia actuala este pe diagonala principala
			if( k == i) continue;
			//flag: exista drum/nu exista drum
			flag = rand() % 2;
			//in cazul in care exista drum, iar acesta nu a fost alocat deja si nu are sens invers (pt a nu forma cicluri)
			//se da valoare
			if( flag && graph1 -> ad_matrix[k * graph1 -> no_elems + i] == 0 && graph1 -> ad_matrix[i * graph1 -> no_elems + k] == 0){
				graph1 -> ad_matrix[k * graph1 -> no_elems + i] = rand() % 10 + 1;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	struct graph graph1;
	graph1.no_elems = 6;
	graph1.ad_matrix = (int *)calloc(graph1.no_elems * graph1.no_elems, sizeof(int));

    srand(time(NULL));
	random_graph(&graph1);

	for(int i = 0; i < graph1.no_elems * graph1.no_elems; i++){
		printf("%d ", graph1.ad_matrix[i]);
		if(i % graph1.no_elems - 5 == 0){
			printf("\n");
		}
	}

	free(graph1.ad_matrix);
	system("pause");
	return 0;
}
