#include "tools.c"

/*struct edge
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
};*/

int convert_mat_array( int coord_1, int coord_2, int max_size );
void create_edges(struct graph * graph);
void random_graph( struct graph* graph );
void print_ad_mat( struct graph graph);
void print_array(int arr[], int n);