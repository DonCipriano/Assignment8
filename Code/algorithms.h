///\file algorithms.h
///\brief C library implementation for Dijkstra algorithm and Bellman Ford algorithm.
///
/// Created by Amzuloiu Andrei-Ciprian on 03/06/18.
///
/// Implements Dijkstra algorithm and Bellman Ford algorithm used to find the minimum path between two vertexes in a weighted directed graph.


#ifndef ALGORITHMS_H
#define ALGORITHMS_H

void dijkstra( struct graph graph, int start_node, int final_node );
void bellman_ford( struct graph graph, int src, int dest );

#endif