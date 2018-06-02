#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tools.h"
#include "algorithms.h"

int main(){

    struct graph graph;
    int vertex_1;
    int vertex_2;


    srand((unsigned) time(NULL));


    random_graph(&graph);
    print_ad_mat(graph);

    printf("A graph was generated in graph.txt.\nType two vertices in input.txt to find the minimum path between them.\n");
    system("pause");
    read_input(&vertex_1, &vertex_2);

    printf("\nBellman ford: ");
    bellman_ford(graph, vertex_1, vertex_2);

    printf("\n");

    printf("Dijkstra: ");
    dijkstra(graph, vertex_1, vertex_2);

    printf("\n");
    free(graph.ad_matrix);
    system("pause");
    return 0;
}
