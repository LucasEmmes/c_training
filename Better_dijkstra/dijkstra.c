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
        // Set up variables
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
        }

        return node;
}

void read_data(char * filename) {
    FILE * fp = fopen("file.txt", "r");
    assert(fp);
    
    // Set up variables
    struct dictionairy_t * node_dict = create_dictionairy();
    char name_start[12];
    char name_goal[12];
    memset(name_start, 0, sizeof(name_start));
    memset(name_goal, 0, sizeof(name_goal));

    // Read name of start node
    read_node_name(name_start, ',', fp);
    // Read name of goal node
    read_node_name(name_goal, '\n', fp);

    // Needed to make sure we don't skip first node's first character
    ungetc(0, fp); 
    // Loop to read nodes and costs and make edges
    while (fgetc(fp) != EOF) {
        // Get node A
        struct node_t * node_a = retrieve_node(node_dict, fp);
        // Get node B
        struct node_t * node_b = retrieve_node(node_dict, fp);
        // Get cost
        
        printf("%s - %s\n", node_a->name, node_b->name);
    }




    fclose(fp);
}

void dijkstra(struct node_t * start, struct node_t * goal) {





}

int main(int argc, char const *argv[]) {

    // struct node_t * a = initialize_node("A");
    // printf("%s\n",a->name);
    // printf("%d\n", ',');

    read_data("file.txt");

    return 0;
}