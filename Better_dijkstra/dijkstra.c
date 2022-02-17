#include "dictionairy.c"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint64_t uid_counter = 0;

struct edge_t {
    uint64_t cost;
    struct node_t * node;
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

struct node_t * initialize_node(char * name) {
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

        struct edge_t ** bigger_edge_array = malloc(sizeof(struct edge_t *) * from->num_of_edges_available * 2);
        memcpy(bigger_edge_array, from->edges, sizeof(from->edges));
        free(from->edges);
        from->edges = bigger_edge_array;
        from->num_of_edges_available = from->num_of_edges_available * 2;
    }

    // Make edge
    struct edge_t * edge = malloc(sizeof(* edge));
    edge->cost = cost;
    edge->node = to;

    // Add edge
    from->edges[from->num_of_actual_edges] = edge;
    from->num_of_actual_edges++;
}

void print_edges(struct node_t * node) {
    for (uint16_t i = 0; i < node->num_of_actual_edges; i++) {
        printf("%s\n", node->edges[i]->node->name);
    }
}

void read_node_name(char * name, char divc, FILE * fp) {
    int counter = 0;
    int current_char = fgetc(fp);
    while (current_char != divc && current_char != EOF) {
        name[counter] = current_char;
        counter++;
        current_char = fgetc(fp);
    }
}

struct node_t * retrieve_node(struct dictionairy_t * node_dict, FILE * fp) {
    char node_name[12];
    memset(node_name, 0, sizeof(node_name));
    // Read name
    read_node_name(node_name, ',', fp);
    // Try to retrieve node
    struct node_t * node = (struct node_t *) search_dictionairy(node_dict, node_name);
    // If node doesn't exist, we make a new one
    if (node == NULL) {
        // Initialize
        node = initialize_node(node_name);
        // Add to dict
        dictionairy_add(node_dict, node_name, node);

        printf("MADE node \"%s\" @ %u\n", node_name, node);
    }else {
        printf("FOUND node \"%s\" @ %u\n", node_name, node);
    }

    return node;
}

uint64_t retrieve_cost(FILE * fp) {
    uint64_t cost = 0;
    int current_char = fgetc(fp);

    // Read char by char and convert into number
    while (current_char != '\n' && current_char != EOF) {
        cost = cost * 10;
        cost += current_char - 48;
        current_char = fgetc(fp);
    }

    return cost;
}

void read_data(struct dictionairy_t * node_dict, FILE * fp) {
    // Loop to read nodes and costs and make edges
    while (1) {
        struct node_t * node_a = retrieve_node(node_dict, fp);
        struct node_t * node_b = retrieve_node(node_dict, fp);
        uint64_t cost = retrieve_cost(fp);
        add_edge(node_a, node_b, cost);

        // Check if we've reached an EOF
        int b = fgetc(fp);
        if (b == EOF) {break;}
        else {ungetc(b, fp);}
    }
}

void dijkstra(struct node_t * start, struct node_t * goal);

int main(int argc, char const *argv[]) {
    struct dictionairy_t * node_dict = create_dictionairy();
    FILE * fp = fopen("file.csv", "r");
    assert(fp);

    // Read start and goal nodes
    struct node_t * start = retrieve_node(node_dict, fp);
    struct node_t * goal = retrieve_node(node_dict, fp);
    // Throw away unneccesary \n
    fgetc(fp);
    // Read all edges
    read_data(node_dict, fp);
    

    destroy_dictionairy(node_dict);
    fclose(fp);
    return 0;
}