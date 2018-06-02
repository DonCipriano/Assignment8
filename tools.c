#include <stdlib.h>
#include <stdio.h>
#include <time.h>



struct edge
{
    int source;
    int destination;
    int weight;
};

struct graph{
	int no_elems;
    int no_edges;
	//matricea de adiacenta in loc de 1 va contine distanta drumului care va fi mai mare si diferita fata de 0
	int *ad_matrix;

	struct edge *edge;
};



int convert_mat_array( int coord_1, int coord_2, int max_size ){
    return coord_1 * max_size + coord_2;
}

void create_edges(struct graph * graph){
	int iterator;
	int iterator_edge = 0;

	graph -> edge = (struct edge*) malloc( graph -> no_edges * sizeof( struct edge ) );

	for( iterator = 0; iterator < graph -> no_elems * graph -> no_elems; iterator++ ){
		if( graph -> ad_matrix[iterator] != 0){
			graph -> edge[iterator_edge].source = iterator / graph -> no_elems;
			graph -> edge[iterator_edge].destination = iterator % graph -> no_elems;
			graph -> edge[iterator_edge].weight = graph -> ad_matrix[iterator];

			iterator_edge++;
		}
	}
}

void random_graph( struct graph* graph ){
    int iterator_1;
    int iterator_2;
    int flag;
    
    graph -> no_elems = rand() % 500 + 2;
    graph -> no_edges = 0;

    graph -> ad_matrix = (int *)calloc(graph -> no_elems * graph -> no_elems, sizeof(int));

    //parcurge randurile si coloanele matricei de adiacenta
    for( iterator_1 = 0; iterator_1 < graph -> no_elems; iterator_1++ ){
        for( iterator_2 = 0; iterator_2 < graph -> no_elems; iterator_2++){
            //verifica daca pozitia actuala este pe diagonala principala
            if( iterator_1 == iterator_2) continue;
            //flag: exista drum/nu exista drum
            flag = rand() % 2;
            //in cazul in care exista drum, iar acesta nu a fost alocat deiterator_2a si nu are sens invers (pt a nu forma cicluri)
            //se da valoare
            if( flag ){
                graph -> no_edges++;

                if(graph -> ad_matrix[convert_mat_array(iterator_2, iterator_1, graph -> no_elems)] == 0){
                    graph -> ad_matrix[convert_mat_array(iterator_1, iterator_2, graph -> no_elems)] = rand() % 10 + 1;
                }
            } 
        }
    }
}


void print_ad_mat( struct graph graph){
	FILE *f_write;
    int iterator;

    f_write = fopen("graph.txt", "w");
    fprintf(f_write, "Number of vertices: %d\nAdjacency matrix with cost on each edge: \n", graph.no_elems);
    for( iterator = 0; iterator < graph.no_elems * graph.no_elems; iterator++){
        fprintf(f_write, "%d ", graph.ad_matrix[iterator]);
        if(iterator % graph.no_elems == graph.no_elems - 1){
            fprintf(f_write, "\n");
        }
    }

    fclose(f_write);
}

void read_input( int *var_1, int *var_2){
	FILE *f_read;

	f_read = fopen("input.txt", "r");
	fscanf(f_read, "%d%d", var_1, var_2);

	fclose(f_read);
}
