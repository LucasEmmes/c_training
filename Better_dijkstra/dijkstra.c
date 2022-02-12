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
    struct edge_t ** edges;
};

struct node_t * initialize_node(char name[12]) {
    // Make new node pointer
    struct node_t * node = malloc(sizeof(* node));
    uid_counter ++;
    
    // Initialize with empty fields
    node->uid = uid_counter;
    node->shortest_distance = -1;
    node->in_queue = 0;
    node->num_of_actual_edges = 0;
    node->num_of_edges_available = 0;
    node->best_parent = NULL;
    node->edges = NULL;
    // Copy over name
    strncpy(node->name, name, sizeof(char)*12);

    return node;
}

void add_edge(struct node_t * from, struct node_t * to, uint64_t cost) {
    // No edges allocated yet
    if (from->num_of_actual_edges == 0) {
        struct edge_t ** edge_array = malloc(sizeof(struct edge_t *) * 5);

        from->edges = edge_array;
        from->num_of_edges_available = 5;

    }
    // No more edges available, extend
    else if (from->num_of_actual_edges == from->num_of_edges_available) {

        struct edge_t ** bigger_edge_array = malloc(sizeof(struct edge_t *) * from->num_of_edges_available*2);
        memcpy(bigger_edge_array, from->edges, sizeof(from->edges));
        free(from->edges);
        from->edges = bigger_edge_array;

    }

    // Make edge
    struct edge_t * edge;
    edge->cost = cost;
    edge->node = to;

    // Add edge
    from->edges[from->num_of_actual_edges] = edge;
    from->num_of_actual_edges++;
}

void print_edges(struct node_t * node) {
    for (uint16_t i; i < node->num_of_actual_edges; i++) {
        printf("%s", node->edges[i]->node->name);
    }
}


int main(int argc, char const *argv[]) {

    struct node_t * a = initialize_node("A           ");
    struct node_t * b = initialize_node("Hello World");

    add_edge(a, b, 10);

    print_edges(a);

    return 0;
}