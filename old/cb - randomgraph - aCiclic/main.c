#include <stdio.h>
#include <stdlib.h>


//starile pe care nodurile din graph le pot avea
#define initial 1
#define visited 2
#define finished 3
#define INFINITY 9999

struct graph{
	int no_elems;

//matricea de adiacenta in loc de 1 va contine distanta drumului care va fi mai mare si diferita fata de 0
	int *ad_matrix;
};

int convert_mat_array( int coord_1, int coord_2, int max_size ){
    return coord_1 * max_size + coord_2;
}

void dijkstra( struct graph graph1, int start_node, int final_node ){

    int *cost = (int *) malloc(graph1.no_elems * sizeof(int));
    int *distance = (int *) malloc(graph1.no_elems * sizeof(int));
    int *pred = (int *) malloc(graph1.no_elems * sizeof(int));
    int *vis = (int *) malloc(graph1.no_elems * sizeof(int));
    int count;
    int min_distance;
    int next_node;
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

    //initialieaza pred,distance si vis
    for( iterator_1 = 0; iterator_1 < graph1.no_elems; iterator_1++ ){
        distance[iterator_1] = cost[convert_mat_array(start_node, iterator_1, graph1.no_elems)];
        pred[iterator_1] = start_node;
        vis[iterator_1] = 0;
    }

    distance[start_node] = 0;
    vis[start_node] = 1;
    count = 1;

    while(count < graph1.no_elems - 1){
        min_distance = INFINITY;

        //next_node gives the node at minimum distance
        for( iterator_1 = 0; iterator_1 < graph1.no_elems; iterator_1++ )
            if( distance[iterator_1] < min_distance && !vis[iterator_1] )
            {
                min_distance = distance[iterator_1];
                next_node = iterator_1;
            }

            //verifica daca exista un drum mai eficient in jurul altor noduri
            vis[next_node] = 1;
            for( iterator_1 = 0; iterator_1 < graph1.no_elems; iterator_1++ )
                if( !vis[iterator_1] )
                    if( min_distance + cost[convert_mat_array(start_node, iterator_1, graph1.no_elems)] < distance[iterator_1] ){
                        distance[iterator_1] = min_distance + cost[convert_mat_array(start_node, iterator_1, graph1.no_elems)];
                        pred[iterator_1] = next_node;
                    }
        count++;
    }

    //print the path and distance of each node
    if( distance[final_node] < 9999){
        printf("\nDistance of node%d=%d", final_node, distance[final_node]);
        printf("\nPath=%d", final_node);

        iterator_2 = final_node;
        do
        {
            iterator_2 = pred[iterator_2];
            printf("<-%d", iterator_2);
        }while( iterator_2 != start_node );
    } else{
        printf("No path to this node.");
    }
}

int DF_Traversal(struct graph graph1, int *state)
{
	int iterator;

	//initializeaza state
	for( iterator = 0; iterator < graph1.no_elems; iterator++ ){
       state[iterator] = initial;
	}

	//incepe dfs din nodul 0;
	if( !DFS( graph1, 0, state ) );

	for( iterator = 0; iterator < graph1.no_elems; iterator++ )
	{
	    //in cazul in care nodul nu a fost vizitat sau nu formeaza sfarsit de graph, se aplica dfs
		if( state[iterator] == initial ){
			return DFS( graph1, iterator, state );
		}
	}

	return 0;
}

int DFS( struct graph graph1, int start_node, int *state)
{
	int iterator;
	state[start_node] = visited;

	//se parcurge graph ul
	for( iterator = 0; iterator < graph1.no_elems; iterator++ ){
		if( graph1.ad_matrix[start_node * graph1.no_elems + iterator] ){
            //daca nodul nu a fost vizitat, se continua dfs
			if( state[iterator] == initial ){
				DFS( graph1, iterator, state );
			} else if( state[ iterator ] == visited )
			{
			    //daca nodul a mai fost vizitat, inseamna ca este graph ciclic si se returneaza 1
				return 1;
			}
		}
	}

    //daca nu este ciclic, returneaza 0 si marcheaza nodul de start ca finit
	state[start_node] = finished;

    return 0;

}/*End of DFS()*/


void random_graph( struct graph* graph1){
	int iterator_1;
	int iterator_2;
	int flag;
	//state = starea fiecarui nod din graph
    int *state;
    state = malloc(graph1->no_elems * sizeof(int));

	//parcurge randurile si coloanele matricei de adiacenta
	for( iterator_2 = 0; iterator_2 < graph1 -> no_elems; iterator_2++ ){
		for( iterator_1 = 0; iterator_1 < graph1 -> no_elems; iterator_1++){
			//verifica daca pozitia actuala este pe diagonala principala
			if( iterator_2 == iterator_1) continue;
			//flag: exista drum/nu exista drum
			flag = rand() % 2;
			//in cazul in care exista drum, iar acesta nu a fost alocat deja si nu are sens invers (pt a nu forma cicluri)
			//se da valoare
			if(flag && graph1 -> ad_matrix[iterator_2 * graph1 -> no_elems + iterator_1] == 0 && graph1 -> ad_matrix[iterator_1 * graph1 -> no_elems + iterator_2] == 0){
				graph1 -> ad_matrix[iterator_2 * graph1 -> no_elems + iterator_1] = rand() % 10 + 1;

			}
		}
	}

	free(state);
}

void print_ad_mat( struct graph graph1 ){
    int iterator;

    printf("\n");
    for( iterator = 0; iterator < graph1.no_elems * graph1.no_elems; iterator++){
		printf("%d ", graph1.ad_matrix[iterator]);

		if(iterator % graph1.no_elems + 1 == graph1.no_elems){
			printf("\n");
		}
	}
}

int main(int argc, char const *argv[])
{
	struct graph graph1;
	int iterator;

	//numarul elemente si aloca memoria
	printf("graph_no_elems= ");
	scanf("%d", &graph1.no_elems);
	graph1.ad_matrix = (int *)calloc(graph1.no_elems * graph1.no_elems, sizeof(int));

    srand(time(NULL));
	random_graph(&graph1);
    dijkstra(graph1, 0, 60);

	//afiseaza matricea
	print_ad_mat(graph1);

	free(graph1.ad_matrix);
	system("pause");
	return 0;
}
