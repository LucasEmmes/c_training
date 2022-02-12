#include "dictionairy.c"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint64_t uid_counter = 0;

struct edge_t {
    struct node_t * node;
    uint64_t cost;
};

struct node_t {
    uint64_t uid;
    char name[12];
    uint64_t shortest_distance;
    struct node_t * best_parent;
    uint16_t num_of_actual_edges;
    uint16_t num_of_edges_available;
    char in_queue;
    struct edge_t edges[];
};

struct node_t * initialize_node(char name[12]) {
    // Make new node pointer
    struct node_t * node = malloc(sizeof(* node) + sizeof(struct edge_t)*5);
    uid_counter ++;
    
    // Initialize with empty fields
    node->uid = uid_counter;
    node->shortest_distance = -1;
    node->in_queue = 0;
    node->num_of_actual_edges = 0;
    node->num_of_edges_available = 5;
    node->best_parent = NULL;
    // Copy over name
    strncpy(node->name, name, sizeof(char)*12);

    return node;
}

struct node_t * add_edge(struct node_t * from, struct node_t * to, uint64_t cost) {
    // There is still space for more edges => add edge
    if (from->num_of_edges_available > from->num_of_actual_edges) {
        // Make edge
        struct edge_t new_edge;
        new_edge.node = to;
        new_edge.cost = cost;
        // Add struct to array
        from->edges[from->num_of_actual_edges] = new_edge;
        // Add 1 to counter
        from->num_of_actual_edges++;

        return from;
    }
    // There are no more spaces => double num of possible edges, then add
    else {
        struct node_t * larger_node = malloc(sizeof(* larger_node) + sizeof(struct edge_t)*from->num_of_edges_available*2);
        memcpy(larger_node, from, sizeof(*from));
        larger_node->num_of_edges_available = from->num_of_edges_available*2;
        free(from);

        // Make edge struct
        struct edge_t new_edge;
        new_edge.node = to;
        new_edge.cost = cost;

        // Add struct to array
        larger_node->edges[larger_node->num_of_actual_edges] = new_edge;

        // Add 1 to counter
        larger_node->num_of_actual_edges++;

        return larger_node;
    }
}

int main(int argc, char const *argv[]) {

    struct node_t * n = initialize_node("Hello World");

    return 0;
}