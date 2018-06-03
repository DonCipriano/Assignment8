///\file tools.c
///\brief C file implementation for some functions used in algorithms or used for input/output.
///
/// Created by Amzuloiu Andrei-Ciprian on 03/06/18.

#include <stdlib.h>///>malloc(), calloc()
#include <stdio.h>///>printf(), fopen(), fprintf(), fscanf(), fclose()
#include <time.h>///>srand(), rand()

///\def #define INFINITY 9999
///\brief Define the maximum number possible as 9999.
#define INFINITY 9999

///\brief Structure used to store the elements of an edge.
struct edge
{
    int source;
    int destination;
    int weight;
};

///\brief Structure used to store the elements of a graph.
struct graph{
	
	int no_elems;
    int no_edges;
	int* ad_matrix;

	struct edge* edge;
};



int convert_mat_array( int coord_1, int coord_2, int max_size ){
	///\fn int convert_mat_array()
    ///\brief This function converts the coordinates of a matrix in array position.
    ///\param coord_1 The column coordinate of a matrix.
    ///\param coord_2 The row coordinate of a matrix.

	/// It returns the converted array position. 
	/// This is usefull because I used an array for ad_matrix and for other variables in dijkstra algorithm.
    return coord_1 * max_size + coord_2;
}

void create_edges(struct graph* graph){
	///\fn void create_edges()
		///\brief This function use the ad_matrix to create an array with all edges of the graph.
		///\param *graph The graph that we use in our algorithms.
		///\var iterator A variable used for iteration.
		///\var iterator_edge A variable used for iteration of edges.
	int iterator;
	int iterator_edge = 0;

	///Memory allocation of the edge array. 
	graph -> edge = (struct edge*) malloc( graph -> no_edges * sizeof( struct edge ) );

	///The only thing we need to find the edges is to check every element from ad_matrix.
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
	///\fn void random_graph()
		///\brief This function is used to generate a random graph.
		///\param *graph A struct variable that we use to generate the graph.
		///\var iterator_1 A variable used for iteration.
		///\var iterator_2 A variable used for iteration.
		///\var flag A flag variable. When flag == 1 there will be an edge, else the position in ad_matrix will be 0. 

    int iterator_1;
    int iterator_2;
    int flag;
    
    ///Generate a random number for the number of elements of the graph.
    graph -> no_elems = rand() % 500 + 2;
    ///Initialize the number of edges.
    graph -> no_edges = 0;

    ///Memory allocation of the ad_matrix. 
    graph -> ad_matrix = (int *)calloc(graph -> no_elems * graph -> no_elems, sizeof(int));

    ///Iteration of columns and rows of the ad_matrix.
    for( iterator_1 = 0; iterator_1 < graph -> no_elems; iterator_1++ ){
        for( iterator_2 = 0; iterator_2 < graph -> no_elems; iterator_2++){
            
            ///Check if the coordinates are on the main diagonal.
            if( iterator_1 == iterator_2) continue;
            
            ///Flag: Whether there is or not an edge.
            flag = rand() % 2;
            
            if( flag ){
                graph -> no_edges++;

                ///Generate the cost of the edge.
                if(graph -> ad_matrix[convert_mat_array(iterator_2, iterator_1, graph -> no_elems)] == 0){
                    graph -> ad_matrix[convert_mat_array(iterator_1, iterator_2, graph -> no_elems)] = rand() % 100 + 1;
                }
            } 
        }
    }
}


void print_ad_mat( struct graph graph ){
	///\fn void print_ad_mat()
		///\brief This function is used to print the adjacency matrix in graph.txt.
		///\param graph A structure variable that contains the details about the graph that will be used.
		///\var f_write A variable used for writing in graph.txt.
		///\var iterator A variable used for iteration.
	FILE *f_write;
    int iterator;

    f_write = fopen("graph.txt", "w");
    fprintf(f_write, "Number of vertexes: %d\nAdjacency matrix with cost on each edge: \n", graph.no_elems);
    for( iterator = 0; iterator < graph.no_elems * graph.no_elems; iterator++){
        fprintf(f_write, "%d ", graph.ad_matrix[iterator]);
        if(iterator % graph.no_elems == graph.no_elems - 1){
            fprintf(f_write, "\n");
        }
    }

    fclose(f_write);
}

void read_input( int* var_1, int* var_2 ){
	///\fn void read_input()
		///\brief This function is used to read the source vertex and the destination vertex from input.txt.
		///\param *var_1 The source vertex.
		///\param *var_2 The destination vertex.
		///\var f_write A variable used for writing in graph.txt.
	FILE *f_read;

	f_read = fopen("input.txt", "r");
	fscanf(f_read, "%d%d", var_1, var_2);

	fclose(f_read);
}

void init_dijkstra( struct graph graph, int* value_mat, int* distance, int* pred, int start_node ){
	///\fn void init_dijkstra()
		///\brief This function is used to initialize the value_mat, distace and pred arrays.
		///\param graph A structure variable that contains the details about the graph that will be used.
		///\param *value_mat A copy of *ad_matrix modified for dijkstra algorithm.
	    ///\param *distance An array used to store the distance between source vertex and any other vertex in graph.
    	///\param *pred An array used to store the predecessor of each node.	
	    ///\var iterator_1 A variable used for iteration.
    	///\var iterator_2 A variable used for iteration.
	int iterator_1;
	int iterator_2;

	for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
        for( iterator_2 = 0; iterator_2 < graph.no_elems; iterator_2++ ){
            if( graph.ad_matrix[convert_mat_array(iterator_1, iterator_2, graph.no_elems)] == 0 ){
                value_mat[convert_mat_array(iterator_1, iterator_2, graph.no_elems)] = INFINITY;
            } else {
                value_mat[convert_mat_array(iterator_1, iterator_2, graph.no_elems)] = graph.ad_matrix[convert_mat_array(iterator_1, iterator_2, graph.no_elems)];
            }
        }
    }
    
    for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
        distance[iterator_1] = value_mat[convert_mat_array(start_node, iterator_1, graph.no_elems)];
        pred[iterator_1] = start_node;
    }
}

void print_results_dijkstra( int start_node, int final_node, int* distance, int* pred ){
	///\fn void print_results_dijkstra()
		///\brief This function is used to print the minimum distance and path between two vertexes.
		///\param start_node The source vertex.
		///\param final_node The destination vertex.
		///\param *distance An array used to store the distance between the source vertex and any other vertex.
		///\param *pred An array used to store the predecessor of each node.
		///\var iterator A variable used for iteration.
		
	int iterator;

	if( final_node != start_node ){
        if( distance[final_node] < 9999 ){
            printf("\nDistance between %d and %d : %d", start_node, final_node, distance[final_node]);
            printf("\nPath: %d ", final_node);
        
            iterator = final_node;

            do{
               iterator = pred[iterator];
               printf("<- %d ", iterator);
                } while( iterator != start_node );
            
        } else {
            printf("\nNo valid path between the two vertexes.");
        }

    } else {
        printf("\nDistance between %d and %d : %d", start_node, final_node, distance[final_node]);
        printf("\nPath: %d", start_node);
    }
}

void init_bellman_ford( int* dist, int** path, int no_elems ){
	///\fn void init_bellman_ford()
		///\brief This function is used to initialize the dist array and the path matrix.
		///\param *dist An array used to store the distance between the source vertex and any other vertexes.
		///\param **path A matrix used to store the path between source vertex and any other vertexes.
		///\param no_elems The number of vertexes.
		///\var iterator A variable used for iteration.
	int iterator;

	for ( iterator = 0; iterator < no_elems; iterator++ ){
        dist[iterator] = INFINITY;
    }

    for ( iterator = 0; iterator < no_elems; iterator++ ){
        path[iterator][0] = 0;
    }
}

int negative_cycle_check( struct graph graph, int* dist ){
	///\fn int negative_cycle_check()
		///\brief This function is used to check if the graph has negative cycles.
		///\param graph A structure variable that contains the details about the graph that will be used.
		///\var source The source vertex of an edge.
		///\var destination The destination vertex of an edge.
		///\var weight The weigth of an edge.
		///\var iterator A variable used for iteration.
	int iterator;
	int source;
	int destination;
	int weight;

	for ( iterator = 0; iterator < graph.no_edges; iterator++ ){
        source = graph.edge[iterator].source;
        destination = graph.edge[iterator].destination;
        weight = graph.edge[iterator].weight;

        if ( dist[source] != INFINITY && dist[source] + weight < dist[destination] ){
            printf("Graph contains negative weight cycle! Bellman Ford algorithm is unavailable.");
        	return 1;
        }
    }

    return 0;
}

void print_results_bellman_ford( int src, int dest, int* dist, int** path ){
	///\fn void print_results_bellman_ford()
		///\brief This function is used to print the minimum distance and path between two vertexes.
		///\param src The source vertex.
		///\param dest The destination vertex.
		///\param *dist An array used to store the distance between the source vertex and any other vertexes.
		///\param **path A matrix used to store the path between the source vertex and any other vertex of the graph.
		///\var iterator A variable used for iteration.
	int iterator;

	if( dist[dest] == INFINITY){
        printf("No valid path between the two vertexes.");
    } else {
        printf("\nDistance between %d and %d : %d\n", src, dest, dist[dest]);
        printf("Path: %d ", dest);
        for( iterator = path[dest][0]; iterator > 0; iterator-- ){
            printf("<- %d ", path[dest][iterator]);
        }
    }
}
