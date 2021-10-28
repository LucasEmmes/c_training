#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_t {
    char name;
    short shortest_path_length;
    char num_of_edges;
    char active;
    struct node_t * shortest_path_via;
    struct node_t * * edges;
    char * weights;
} node_t;

void add_edge(node_t * node1, node_t * node2, char weight) {
    char old_length = node1->num_of_edges;
    char new_length = old_length + 1;

    node_t * * new_edges = (struct node_t * *) malloc(sizeof(node_t)*new_length);
    char * new_weights = (char *) malloc(sizeof(char) * new_length);

    for (char i = 0; i < new_length-1; i++)
    {
        new_edges[i] = node1->edges[i];
        new_weights[i] = node1->weights[i];
    }

    new_edges[new_length-1] = node2;
    new_weights[new_length-1] = weight;

    // Free the old arrays
    free(node1->edges);
    free(node1->weights);

    node1->edges = new_edges;
    node1->weights = new_weights;
    node1->num_of_edges = new_length;
}

void print_edges(node_t node) {
    printf("Edges: %d\n", node.num_of_edges);
    for (char i = 0; i < node.num_of_edges; i++)
    {
        printf("N:%c W:%d, ", node.edges[i]->name, node.weights[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{

    node_t a;
    a.name = 'a';

    node_t b;
    b.name = 'b';

    add_edge(&a, &b, 5);

    print_edges(a);


    return 0;
}
