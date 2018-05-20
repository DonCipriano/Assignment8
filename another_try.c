#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INFINITY 9999

struct graph{
	int no_elems;
    int no_edges;
//matricea de adiacenta in loc de 1 va contine distanta drumului care va fi mai mare si diferita fata de 0
	int *ad_matrix;
};

//converteste coordonatele unei matrici normale in coordonata corespunzatoare vectorului pe care il folosesc.
int convert_mat_array( int coord_1, int coord_2, int max_size );

//genereaza un graph in mod aleator.
void random_graph( struct graph* graph );


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

void print_ad_mat( struct graph graph){
    int iterator;

    for( iterator = 0; iterator < graph.no_elems * graph.no_elems; iterator++){
        printf("%d ", graph.ad_matrix[iterator]);
        if(iterator % graph.no_elems == graph.no_elems - 1){
            printf("\n");
        }
    }
}

int main(int argc, char const *argv[])
{
	struct graph graph;
	graph.no_elems = 10;
	graph.ad_matrix = (int *)calloc(graph.no_elems * graph.no_elems, sizeof(int));

    srand(time(NULL));
	random_graph(&graph);

    print_ad_mat(graph);

    dijkstra(graph, 0, 4);

    printf("\n");
	free(graph.ad_matrix);
	system("pause");
	return 0;
}

int convert_mat_array( int coord_1, int coord_2, int max_size ){
    return coord_1 * max_size + coord_2;
}

void random_graph( struct graph* graph ){
    int iterator_1;
    int iterator_2;
    int flag;

    graph -> no_edges = 0;

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
