///\file tools.h
///\brief C library implementation for some functions used in algorithms or used for input/output.
///
/// Created by Amzuloiu Andrei-Ciprian on 03/06/18.


#ifndef TOOLS_H
#define TOOLS_H

#define INFINITY 9999

struct edge
{
    int source;
    int destination;
    int weight;
};

struct graph{
	int no_elems;
    int no_edges;
	int *ad_matrix;

	struct edge *edge;
};

int convert_mat_array( int coord_1, int coord_2, int max_size );
void create_edges(struct graph * graph);
void random_graph( struct graph* graph );
void print_ad_mat( struct graph graph );
void read_input( int *var_1, int *var_2);
void init_dijkstra( struct graph graph, int *value_mat, int *distance, int *pred, int start_node);
void print_results_dijkstra( int start_node, int final_node, int* distance, int* pred );
void init_bellman_ford( int* dist, int** path, int no_elems );
int negative_cycle_check( struct graph graph, int* dist );
void print_results_bellman_ford( int src, int dest, int* dist, int** path );

#endif