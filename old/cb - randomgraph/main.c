#include <stdio.h>
#include <stdlib.h>

#define INFINITY 9999

struct graph{
	int no_elems;

//matricea de adiacenta in loc de 1 va contine distanta drumului care va fi mai mare si diferita fata de 0
	int *ad_matrix;
};

int convert_mat_array( int coord_1, int coord_2, int max_size ){
    return coord_1 * max_size + coord_2;
}

void dijkstra( struct graph graph1, int start_node ){

    int *cost = (int *)malloc(graph1.no_elems * sizeof(int));
    int *distance = (int *)malloc(graph1.no_elems * sizeof(int));
    int *pred = (int *)malloc(graph1.no_elems * sizeof(int));

    int *visited = (int *)malloc(graph1.no_elems * sizeof(int));
    int count;
    int mindistance;
    int nextnode;
    int iterator_1;
    int iterator_2;

    //pred retine predecesorul fiecarui nod
    //count retine numarul de noduri de care este nevoie

    //copiaza matricea de cost in *cost si o adapteaza pentru algoritm
    for( iterator_1 = 0; iterator_1 < graph1.no_elems; iterator_1++ )
        for( iterator_2 = 0; iterator_2 < graph1.no_elems; iterator_2++)
            if( graph1.ad_matrix[convert_mat_array(iterator_1, iterator_2, graph1.no_elems)] == 0 )
                cost[convert_mat_array(iterator_1, iterator_2, graph1.no_elems)]=INFINITY;
            else
                cost[convert_mat_array(iterator_1, iterator_2, graph1.no_elems)]=graph1.ad_matrix[convert_mat_array(iterator_1, iterator_2, graph1.no_elems)];

    //initialieaza pred,distance si visited
    for( iterator_1 = 0; iterator_1 < graph1.no_elems; iterator_1++ ){
        distance[iterator_1] = cost[convert_mat_array(start_node, iterator_1, graph1.no_elems)];
        pred[iterator_1] = start_node;
        visited[iterator_1] = 0;
    }

    distance[start_node] = 0;
    visited[start_node] = 1;
    count = 1;

    while(count < graph1.no_elems - 1){
        mindistance = INFINITY;

        //nextnode gives the node at minimum distance
        for( iterator_1 = 0; iterator_1 < graph1.no_elems; iterator_1++ )
            if( distance[iterator_1] < mindistance && !visited[iterator_1] )
            {
                mindistance = distance[iterator_1];
                nextnode = iterator_1;
            }

            //verifica daca exista un drum mai eficient in jurul altor noduri
            visited[nextnode] = 1;
            for( iterator_1 = 0; iterator_1 < graph1.no_elems; iterator_1++ )
                if( !visited[iterator_1] )
                    if( mindistance + cost[convert_mat_array(start_node, iterator_1, graph1.no_elems)] < distance[iterator_1] ){
                        distance[iterator_1] = mindistance + cost[convert_mat_array(start_node, iterator_1, graph1.no_elems)];
                        pred[iterator_1] = nextnode;
                    }
        count++;
    }

    //print the path and distance of each node
    for( iterator_1 = 0; iterator_1 < graph1.no_elems; iterator_1++ )
        if( iterator_1 != start_node )
        {
            printf("\nDistance of node%d=%d", iterator_1, distance[iterator_1]);
            printf("\nPath=%d", iterator_1);

            iterator_2 = iterator_1;
            do
            {
                iterator_2 = pred[iterator_2];
                printf("<-%d",iterator_2);
            }while(iterator_2 != start_node);
    }
}

void random_graph( struct graph* graph1 ){
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
			if( flag && graph1 -> ad_matrix[convert_mat_array(k, i, graph1 -> no_elems)] == 0 && graph1 -> ad_matrix[convert_mat_array(i, k, graph1 -> no_elems)] == 0){
				graph1 -> ad_matrix[convert_mat_array(k, i, graph1 -> no_elems)] = rand() % 10 + 1;
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

    dijkstra(graph1, 0);

	free(graph1.ad_matrix);
	system("pause");
	return 0;
}
