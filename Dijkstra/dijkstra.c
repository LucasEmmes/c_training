#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct node_t;

struct edge_t {
    struct node_t * node;
    uint32_t cost;
};


struct node_t {
    uint32_t id;
    uint64_t shortest_distance;
    uint32_t best_parent;
    uint8_t in_queue;
    uint16_t num_of_actual_edges;
    uint16_t num_of_edges_available;
    struct edge_t edges[];
};



struct node_t * create_node(uint32_t id) {
    struct node_t * new_node = malloc(sizeof(* new_node) + sizeof(struct edge_t)*10);
    
    new_node->id = id;
    new_node->shortest_distance = -1;
    new_node->best_parent = 0;
    new_node->in_queue = 0;
    new_node->num_of_actual_edges = 0;
    new_node->num_of_edges_available = 10;

    return new_node;
}

struct node_t * add_edge(struct node_t * from, struct node_t * to, uint32_t cost) {
    // If there is still space for more edges without expanding
    if (from->num_of_edges_available > from->num_of_actual_edges) {
        // Make edge struct
        struct edge_t new_edge;
        new_edge.node = to;
        new_edge.cost = cost;

        // Add struct to array
        from->edges[from->num_of_actual_edges] = new_edge;

        // Add 1 to counter
        from->num_of_actual_edges++;

        return from;
    }
    // If there are no more spaces: double available
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

int comp_nodes(const void * a, const void * b) {
    struct node_t * node_a = *(struct node_t * * ) a;
    struct node_t * node_b = *(struct node_t * * ) b;

    return node_b->shortest_distance - node_a->shortest_distance;
}

int dijkstra(){
    // add start node to queue
    // counter for queue length

    // while queue is not empty
        
        // POP (IN C)
        // copy last element in list
        // overwrite as NULL

        // IS NODE GOAL? => DONE
        // if node.id == goal.id
            // break

        // EXPAND NODE (IN C)
        // for i in range(node.numofactual)
            // n = node.edge[i].node
            // if n.shortest_path > node.shortest + edge.cost
                // n.shortest = node.shortest + edge.cost
                // n.best_parent = node
                // if not n.in_queue
                    // last ++;
                    // queue[last] = n
        
        // SORT QUEUE
        // qsort

    // DO SOME SHID
};


void print_data(struct node_t * a) {
    printf("Id: %d\n", a->id);
    printf("Shortest path: %d\n", a->shortest_distance);
    printf("Best parent: %d\n", a->best_parent);
    printf("Actual edges: %d\n", a->num_of_actual_edges);
    printf("Edges available: %d\n", a->num_of_edges_available);
}

int main(int argc, char const *argv[])
{

    struct node_t * a;
    a = create_node(0);
    a->shortest_distance = 12;

    struct node_t * b;
    b = create_node(1);
    b->shortest_distance = 11;

    // a = add_edge(a, b, 69);

    struct node_t * p[] = {a, b};
    printf("%d, %d\n", p[0]->shortest_distance, p[1]->shortest_distance);
    qsort(p, 2, sizeof(struct node_t *), comp_nodes);
    printf("%d, %d\n", p[0]->shortest_distance, p[1]->shortest_distance);


    return 0;
}