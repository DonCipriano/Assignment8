#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tools.c"

#define INFINITY 9999

void dijkstra( struct graph graph, int start_node, int final_node )
{
 
    int *value_mat = (int*) malloc(graph.no_elems * graph.no_elems * sizeof(int));
    int *distance = (int*) malloc(graph.no_elems * sizeof(int));
    int *pred = (int*) malloc(graph.no_elems * sizeof(int));
    int *visited = (int*) calloc(graph.no_elems, sizeof(int));;
    int count;
    int minimum_distance;
    int next_node;
    int iterator_1;
    int iterator_2;
    
    //pred stocheaza predecesorul fiecarui nod
    //count memoreaza numarul de noduri vizitate 
    

    //prelucram matricea de cost
    for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
        for( iterator_2 = 0; iterator_2 < graph.no_elems; iterator_2++ ){
            if( graph.ad_matrix[convert_mat_array(iterator_1, iterator_2, graph.no_elems)] == 0 ){
                value_mat[convert_mat_array(iterator_1, iterator_2, graph.no_elems)] = INFINITY;
            } else {
                value_mat[convert_mat_array(iterator_1, iterator_2, graph.no_elems)] = graph.ad_matrix[convert_mat_array(iterator_1, iterator_2, graph.no_elems)];
            }
        }
    }
    
    //initializeaza pred, distance si visited
    for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
        distance[iterator_1] = value_mat[convert_mat_array(start_node, iterator_1, graph.no_elems)];
        pred[iterator_1] = start_node;
    }
    
    distance[start_node] = 0;
    visited[start_node] = 1;
    count = 1;
    
    while( count < graph.no_elems - 1 ){
        minimum_distance=INFINITY;
        
        //next_node retine nodul cu distanta minima
        for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
            if( distance[iterator_1] < minimum_distance && !visited[iterator_1] ){
                minimum_distance = distance[iterator_1];
                next_node = iterator_1;
            }
        }
            
        //verifica daca exista o cale mai eficienta          
        visited[next_node] = 1;
        for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
            if(!visited[iterator_1]){
                if(minimum_distance + value_mat[convert_mat_array(next_node, iterator_1, graph.no_elems)]<distance[iterator_1]){
                    distance[iterator_1]=minimum_distance+value_mat[convert_mat_array(next_node, iterator_1, graph.no_elems)];
                    pred[iterator_1]=next_node;
                }
            }
        }

        count++;
    }

//printeaza distanta si calea pentru nodul dorit
    if( final_node != start_node ){
        if( distance[final_node] < 9999 ){
            printf("\nDistance dintre nodurile %d si %d = %d ", start_node, final_node, distance[final_node]);
            printf("\nPath: %d ",final_node);
        
            iterator_1 = final_node;

            do{
               iterator_1 = pred[iterator_1];
               printf("<- %d ", iterator_1);
                } while( iterator_1 != start_node );
            
        } else {
            printf("\nNu exista legatura intre cele doua noduri.");
        }

    } else {
        printf("\nDistance = 0");
    }

}

void bellman_ford(struct graph* graph, int src){
    int *dist = (int *) malloc( graph -> no_elems * sizeof(int) );
 	int iterator_1;
 	int iterator_2;
 	int weight_1;
	int source_1;
	int destination_1;

 	create_edges(graph);

    // Step 1: Initializeaza toate legaturile de la sursa la celelalte noduri ca
    // INFINITE
    for ( iterator_1 = 0; iterator_1 < graph -> no_elems; iterator_1++ ){
        dist[iterator_1] = INFINITY;
    }

    dist[src] = 0;
 
    // Step 2: Verifica toate lagaturile de no_edges - 1 ori. Un drum tipic 
    // de la sursa catre oricare alt nod poate avea maxim no_nodes - 1
    // legaturi

    for ( iterator_1 = 1; iterator_1 <= graph -> no_elems-1; iterator_1++ ){
        for ( iterator_2 = 0; iterator_2 < graph -> no_edges; iterator_2++ ){
            source_1 = graph->edge[iterator_2].source;
            destination_1 = graph->edge[iterator_2].destination;
            weight_1 = graph->edge[iterator_2].weight;

            if ( dist[source_1] != INFINITY && dist[source_1] + weight_1 < dist[destination_1] ){
                dist[destination_1] = dist[source_1] + weight_1;
            }
        }
    }
 
    // Step 3: Verfica daca exista cicluri de cost negativ
    //metoda de mai sus functioneaza doar in cazul in care graful nu are cicluri de cost negativ
    for ( iterator_1 = 0; iterator_1 < graph -> no_edges; iterator_1++ ){
        source_1 = graph->edge[iterator_1].source;
        destination_1 = graph->edge[iterator_1].destination;
        weight_1 = graph->edge[iterator_1].weight;

        if ( dist[source_1] != INFINITY && dist[source_1] + weight_1 < dist[destination_1] )
            printf("Graph contains negative weight cycle");
    }
 
    print_array(dist, graph -> no_elems);
}

int main(int argc, char const *argv[])
{
	struct graph graph;
	graph.no_elems = 10;
	graph.ad_matrix = (int *)calloc(graph.no_elems * graph.no_elems, sizeof(int));

    srand(time(NULL));
	random_graph(&graph);

    print_ad_mat(graph);

    bellman_ford(&graph, 0);

    printf("\n");

    dijkstra(graph, 0, 1);

    printf("\n");
	free(graph.ad_matrix);
	system("pause");
	return 0;
}
