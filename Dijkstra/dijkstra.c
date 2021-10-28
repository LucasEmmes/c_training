#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    char name;
    short shortest_path_length;
    char num_of_edges;
    struct node_t * shortest_path_via;
    struct node_t * edges;
} node_t;

void add_edge(node_t node1, node_t node2) {
    char old_length = node1.num_of_edges;
    char new_length = old_length + 1;

    // node_t * new_edges = (struct node_t *) malloc(sizeof(node_t)*new_length);
}

void print_edges(node_t node) {
    // for (char i = 0; i < node.num_of_edges; i++)
    // {
    //     printf("%c", node->edges[i]);
    // }
    
}

int main(int argc, char const *argv[])
{
    
    // printf("%d\n", sizeof(node_t));
    // printf("%d\n", sizeof(node_t *));

    node_t a;
    a.name = 'a';
    node_t b;
    b.name = 'b';

    node_t custom_edges[1] = {b};
    a.edges = custom_edges;

    printf("%c", a.name);
    printf("%c", a.edges[0].name);

    return 0;
}
