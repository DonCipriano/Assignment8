///\file algorithms.c
///\brief C file implementation for Dijkstra algorithm and Bellman Ford algorithm.
///
/// Created by Amzuloiu Andrei-Ciprian on 03/06/18.
///
/// Implements Dijkstra algorithm and Bellman Ford algorithm used to find the minimum path between two vertexes in a weighted directed graph.

#include <stdlib.h>///>malloc(), calloc(), free()
#include <stdio.h>///>printf()
#include <time.h>///>clock()
#include "tools.h"///>init_dijkstra(), print_results_dijkstra(), create_edges(), init_bellman_ford(), negative_cycle_check(), print_results_bellman_ford()

void dijkstra( struct graph graph, int start_node, int final_node ){
    ///\fn void dijkstra()
        ///\brief Find the minimum path between two vertexes and print them in console screen.
        ///\param graph A structure variable that contains the details about the graph that will be used.
        ///\param start_node The source vertex.
        ///\param final_node The destination vertex.
        ///\var alg_time A variable used to find the execution time of the function.
        ///\var *value_mat A copy of *ad_matrix modified for dijkstra algorithm.
        ///\var *distance An array used to store the distance between source vertex and any other vertex in graph.
        ///\var *pred An array used to store the predecessor of each node.
        ///\var *visited An array used to check if a node was visited or not.
        ///\var count Gives the number of nodes seen so far.
        ///\var minimum_distance Gives the shortest distance found so far.
        ///\var next_node Gives the node at minimum distance.
        ///\var iterator_1 Just a variable used for iteration.
        ///\var iterator_1 Just a variable used for iteration.

    clock_t alg_time;
    alg_time = clock();

    int *value_mat = (int*) malloc(graph.no_elems * graph.no_elems * sizeof(int));
    int *distance = (int*) malloc(graph.no_elems * sizeof(int));
    int *pred = (int*) malloc(graph.no_elems * sizeof(int));
    int *visited = (int*) calloc(graph.no_elems, sizeof(int));
    int count;
    int minimum_distance;
    int next_node;
    int iterator_1;
    int iterator_2;
    
    init_dijkstra(graph, value_mat, distance, pred, start_node);
    
    distance[start_node] = 0;
    visited[start_node] = 1;
    count = 1;
    
    while( count < graph.no_elems - 1 ){
        minimum_distance = INFINITY;
        
        for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
            if( distance[iterator_1] < minimum_distance && !visited[iterator_1] ){
                minimum_distance = distance[iterator_1];
                next_node = iterator_1;
            }
        }
                    
        visited[next_node] = 1;
        for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
            if( !visited[iterator_1] ){
                if( minimum_distance + value_mat[convert_mat_array(next_node, iterator_1, graph.no_elems)] < distance[iterator_1] ){
                    distance[iterator_1] = minimum_distance + value_mat[convert_mat_array(next_node, iterator_1, graph.no_elems)];
                    pred[iterator_1] = next_node;
                }
            }
        }

        count++;
    }

    print_results_dijkstra(start_node, final_node, distance, pred);

    alg_time = clock() - alg_time;
    double time_taken = ((double) alg_time) / CLOCKS_PER_SEC;

    printf("\nExecution time of the function: %lf\n", time_taken);

    free(value_mat);
    free(distance);
    free(pred);
    free(visited);
}

void bellman_ford( struct graph graph, int start_node, int final_node ){
    ///\fn void bellman_for( struct graph graph, int start_node, int final_node )
        ///\brief Find the minimum path between two vertexes and print them in console screen.
        ///\param graph A structure variable that contains the details about the graph that will be used.
        ///\param start_node The source vertex.
        ///\param final_node The destination vertex.
        ///\var alg_time A variable used to find the execution time of the function.
        ///\var *dist An array used to store the distance between source vertex and any other vertex in graph.
        ///\var **path A matrix used to store the path between the source vartex and all others vertexes.
        ///\var weight A variable used to store the weight of an edge.
        ///\var source A variable used to store the source vertex of an edge.
        ///\var destination A variable used to store the destination vertex of an edge.

    clock_t alg_time;
    alg_time = clock();

    int *dist = (int*) malloc(graph.no_elems * sizeof(int));
    int iterator_1;
    int iterator_2;
    int iterator_3;
    int weight;
    int source;
    int destination;
    int **path = (int**) malloc(graph.no_elems * sizeof(int*));

    for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
        path[iterator_1] = (int*) malloc(graph.no_elems * sizeof(int));
    }

    create_edges(&graph);

    init_bellman_ford( dist, path, graph.no_elems );
    dist[start_node] = 0;

    for ( iterator_1 = 1; iterator_1 <= graph.no_elems - 1; iterator_1++ ){
        for ( iterator_2 = 0; iterator_2 < graph.no_edges; iterator_2++ ){
            source = graph.edge[iterator_2].source;
            destination = graph.edge[iterator_2].destination;
            weight = graph.edge[iterator_2].weight;

            if ( dist[source] != INFINITY && dist[source] + weight < dist[destination] ){
                dist[destination] = dist[source] + weight;

                path[destination][0] = path[source][0] + 1;
                for( iterator_3 = 1; iterator_3 < path[destination][0]; iterator_3++ ){
                    path[destination][iterator_3] = path[source][iterator_3];
                }
                path[destination][ path[destination][0] ] = source;
            }
        }
    }
 
    if( !negative_cycle_check(graph, dist) ){
        print_results_bellman_ford(start_node, final_node, dist, path);
    }

    alg_time = clock() - alg_time;
    double time_taken = ((double) alg_time) / CLOCKS_PER_SEC;

    printf("\nExecution time of the function: %lf\n", time_taken);

    free(dist);
    for( iterator_1 = 0; iterator_1 < graph.no_elems; iterator_1++ ){
        free(path[iterator_1]);
    }
    free(path);
    free(graph.edge);
}