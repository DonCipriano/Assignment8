///\file main.c
///\brief C program for finding the minimum length path between two vertexes in a weighted directed graph.
///
/// Created by Amzuloiu Andrei-Ciprian on 03/06/18.



#include <stdio.h>///>printf(), scanf()
#include <stdlib.h>///>free()
#include <time.h>///>srand()
#include "tools.h"///>random_graph(), print_ad_mat(), read_input()
#include "algorithms.h"///>bellman_ford(), dijkstra()

int main(){
    ///\fn int main()
    ///\brief Main function.
    /// Function calls random_graph, print_ad_mat, read_input imported from tools.h to generate a random graph, write it in a file and read the input from the user.
    /// Function calls of bellman_ford, dijkstra imported from algorithms.h
    ///\var graph A structure variable containing the details about the graph.
    ///\var vertex_1 A variable used to read the source vertex from user.
    ///\var vertex_2 A variable used to read the destination vertex from the user.
    ///\var keep_open A variable used to keep open the program while the user check the generated graph and choose the two vertexes.

    struct graph graph;
    int vertex_1;
    int vertex_2;
    int keep_open;

    srand((unsigned) time(NULL));

    random_graph(&graph);
    print_ad_mat(graph);

    printf("A graph was generated in graph.txt.\nType two vertexes in input.txt to find the minimum path between them.\n");
    printf("After you check the files, type any number to contnue.\n");
    read_input(&vertex_1, &vertex_2);
    scanf("%d", &keep_open);

    printf("Bellman Ford: ");
    bellman_ford(graph, vertex_1, vertex_2);

    printf("\n");

    printf("Dijkstra: ");
    dijkstra(graph, vertex_1, vertex_2);

    printf("\n");
    free(graph.ad_matrix);

    printf("After you check the results, type any number to close the program.\n");
    scanf("%d", &keep_open);
    return 0;
}