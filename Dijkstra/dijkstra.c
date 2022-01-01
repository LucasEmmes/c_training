#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t id_counter = 0;

struct node_t;

struct edge_t {
    struct node_t * node;
    uint32_t cost;
};

struct node_t {
    uint32_t id;
    char name[10];
    uint64_t shortest_distance;
    struct node_t * best_parent;
    uint8_t in_queue;
    uint16_t num_of_actual_edges;
    uint16_t num_of_edges_available;
    struct edge_t edges[];
};

struct dict_t {
    uint8_t depth;
    struct node_t * node;
    struct dict_list_t * characters;
};

struct dict_list_t {
    struct dict_t * entries[256];
};

struct node_t * initialize_node(char * name) {
    struct node_t * new_node = malloc(sizeof(* new_node) + sizeof(struct edge_t)*10);
    
    new_node->id = id_counter;
    new_node->shortest_distance = -1;
    new_node->in_queue = 0;
    new_node->num_of_actual_edges = 0;
    new_node->num_of_edges_available = 10;
    new_node->best_parent = NULL;

    strncpy(new_node->name, name, sizeof(char)*10);

    id_counter ++;
    return new_node;
}

void initialize_dict(struct dict_t * dict) {
    dict->depth = 0;
    dict->node = NULL;
    dict->characters = NULL;
}

void initialize_dict_list(struct dict_list_t * list) {
    memset(list, 0, sizeof(struct dict_t * ) * 256);
}

void add_new_character(struct dict_t * dict, struct node_t * node, char character) {
    // Used when there is a guaranteed clear spot at 'char' in dict->characers[]
    assert("The spot wasn't clear"
    && dict->characters->entries[character] == NULL);

    struct dict_t node_entry;
    node_entry.node = node;
    dict->characters->entries[character] = &node_entry;
};

void add_node_to_dict(struct dict_t * root, struct node_t * node, uint8_t depth) {
    char c = node->name[depth];
    // CASE 1) NOTHING IN ROOT->NODE
    if (root->node == NULL) {

        // THIS MEANS IT MUST HAVE A LIST
        assert("Missing list" && root->characters != NULL);

        // CASE 1.1) LIST ENTRY @ C IS EMPTY
        if (root->characters->entries[c] == NULL) {

            // MAKE NEW DICT AND PUT @ C
            struct dict_t * new_dict = malloc(sizeof(* new_dict));
            initialize_dict(new_dict);
            root->characters->entries[c] = new_dict;
            
            // THEN ADD NODE TO THAT DICT
            new_dict->node = node;
        }
        // CASE 1.2) LIST ENTRY @ C IS NOT EMPTY
        else {

            // GET OUT DICT @ C AND RECURSIVELY CALL add_node_to_dict()
            add_node_to_dict(root->characters->entries[c], node, depth+1);
        }
    }
    // CASE 2+) SOMETHING IN ROOT->NODE
    else {

        char next_node_char = node->name[depth];
        // CASE 2) SOMETHING IN ROOT->NODE, BUT NODE->NAME IS OUT OF CHARACTERS
        if (next_node_char == 0) {
            
            // CASE 2.1) STRINGS ARE EQUAL
            if (!strcmp(root->node->name, node->name)) {
                // DO NOTHING 
                printf("NODE IS ALREADY IN DICT\n");
            }
            // CASE 2.2) STRINGS ARE NOT EQUAL. MEANS ROOT->NODE HAS MORE CHARCTERS AND NEEDS TO BE PUSHED DOWN
            else {
                // COPY OLD NODE
                struct node_t * old_node = root->node;
                // MOVE IN NEW NODE
                root->node = node;
                // CASE 2.2.1) THERE IS NO CHARLIST
                if (root->characters == NULL) {
                    // MAKE NEW AND LINK UP
                    struct dict_list_t * charlist = malloc(sizeof(* charlist));
                    root->characters = charlist;
                }
                // CASE 2.2.2) THERE IS A CHARLIST (GUARANTEED OVERFLOW FROM CASE 2.2.1)
                // GET NEXT CHARACTER IN OLD_NODE->NAME
                char next_old_node_char = old_node->name[depth];

                // CASE 2.2.2.1) THERE IS NOTHING @ NODC
                if (root->characters->entries[next_old_node_char] == NULL) {
                    // MAKE NEW DICT AND PUT @ C
                    struct dict_t * new_dict = malloc(sizeof(* new_dict));
                    initialize_dict(new_dict);
                    root->characters->entries[next_old_node_char] = new_dict;
                    
                    // THEN ADD NODE TO THAT DICT
                    new_dict->node = old_node;
                }
                // CASE 2.2.2.2) THERE IS SOMETHING @ NODC
                else {
                    // RECURSIVELY TRY TO APPEND OLD_NODE
                    add_node_to_dict(root, old_node, depth+1);
                }
            }

            // SHOULD BE EQUAL
            assert("Equality check failed" && strcmp(root->node->name, node->name)==0 && root->node == node);
            // DO NOTHING
        }
        // CASE 3) SOMETHING IN ROOT->NODE, WE STILL HAVE MORE CHARACTERS LEFT
        else {

            // CASE 3.1) ROOT DOESN'T HAVE CHARLIST
            if (root->characters == NULL) {

                // MAKE NEW CHARLIST
                struct dict_list_t * charlist = malloc(sizeof(* charlist));
                initialize_dict_list(charlist);
                root->characters = charlist;
            }

            // CASE 3.2) ROOT HAS A CHARLIST (GUARANTEED OVERFLOW FROM 3.1)
            
            // CASE 3.2.1) NOTHING IN ROOT->CHARACTERS->ENTRIES[C]
            if (root->characters->entries[c] == NULL) {
                
                // CREATE NEW DICT TO PLACE AT C
                struct dict_t * new_dict = malloc(sizeof(* new_dict));
                initialize_dict(new_dict);

                // ADD DATA TO DICT
                new_dict->node = node;
                new_dict->depth = depth+1;

                // LINK UP @ C
                root->characters->entries[c] = new_dict;
            }
            // CASE 3.2.2) SOMETHING IN ROOT->CHARACTERS->ENTRIES[C]
            else {

                // GET OUT DICT @ C AND RECURSIVELY CALL add_node_to_dict()
                add_node_to_dict(root->characters->entries[c], node, depth+1);

            }

        }
    }
    
}

struct node_t * search_dict(struct dict_t * root, char * name, uint8_t depth) {
    if (root->node != NULL) {
        if (strcmp(root->node->name, name) == 0) {
            // printf("FOUND AT DEPTH %d\n", depth);
            return root->node;
        } else if (name[depth] == 0) {
            // printf("NAME NOT IN DICT");
            return NULL;
        } else if (root->characters != NULL) {
            char c = name[depth];
            struct dict_t * next_dict;
            next_dict = root->characters->entries[c];

            return search_dict(next_dict, name, depth+1);
        } else {
            // printf("NAME NOT IN DICT");
            return NULL;
        }
    } else if (root->characters != NULL) {
        char c = name[depth];
        struct dict_t * next_dict;
        next_dict = root->characters->entries[c];

        if (next_dict == NULL) {
            return NULL;
        }

        return search_dict(next_dict, name, depth+1);
    } else {
        printf("ROOT MISSING NODE AND CHARLIST");
        return NULL;
    }

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

struct node_t * * read_data(struct dict_t * root) {
    FILE * fp = fopen("dijkstra_data.txt", "r");
    assert(fp);

    // count lines
    uint64_t number_of_lines = 1;

    int next_char = fgetc(fp);
    while (next_char != EOF) {
        if (next_char == 10) {
            number_of_lines ++;
        }
        next_char = fgetc(fp);
    }

    fseek(fp, 0L, 0);

    // make node_list
    struct node_t * * node_list = (struct node_t * *) malloc(sizeof(struct node_t *) * number_of_lines*2);
    memset(node_list, 0, sizeof(struct node_t *) * number_of_lines*2);

    // save data
    char start_name[10];
    char end_name[10];
    memset(start_name, 0, sizeof(char) * 10);
    memset(end_name, 0, sizeof(char) * 10);

    // get start and goal names
    int counter = 0;
    next_char = fgetc(fp);
    while (next_char != 10 && next_char != EOF) {
        start_name[counter] = (char) next_char;
        counter ++;
        next_char = fgetc(fp);
    }
    counter = 0;
    next_char = fgetc(fp);
    while (next_char != 10 && next_char != EOF) {
        end_name[counter] = (char) next_char;
        counter ++;
        next_char = fgetc(fp);
    }

    // set up variables for node a, b and cost
    char name_a[10];
    struct node_t * node_a;
    char name_b[10];
    struct node_t * node_b;
    uint32_t cost;

    // for each line with data
    while (next_char != EOF) {
        // get a
        memset(name_a, 0, sizeof(char)*10);
        counter = 0;
        next_char = fgetc(fp);
        while (next_char != 44 && next_char != EOF) {
            name_a[counter] = next_char;
            counter ++;
            next_char = fgetc(fp);
        }

        // get b
        memset(name_b, 0, sizeof(char)*10);
        counter = 0;
        next_char = fgetc(fp);
        while (next_char != 44 && next_char != EOF) {
            name_b[counter] = next_char;
            counter ++;
            next_char = fgetc(fp);
        }

        // get cost
        // x-48
        cost = 0;
        next_char = fgetc(fp);
        while (next_char != 10 && next_char != EOF) {
            cost = cost * 10;
            cost = cost << 1;
            cost += (next_char - 48);
            next_char = fgetc(fp);
        }
        
        // find/make nodes
        node_a = search_dict(root, name_a, 0);
        if (node_a == NULL) {
            // printf("DIDNT FIND NODE '%s'\n", name_a);
            node_a = initialize_node(name_a);
            node_list[node_a->id] = node_a;
            add_node_to_dict(root, node_a, 0);
        }
        node_b = search_dict(root, name_b, 0);
        if (node_b == NULL) {
            // printf("DIDNT FIND NODE '%s'\n", name_b);
            node_b = initialize_node(name_b);
            node_list[node_b->id] = node_b;
            add_node_to_dict(root, node_b, 0);
        }

        // make edges
        node_a = add_edge(node_a, node_b, cost);
    }
    search_dict(root, start_name, 0)->shortest_distance = 0;
    return node_list;
}

void dijkstra(struct node_t ** node_list, struct dict_t * dictionairy, char * start_name, char * goal_name) {
    // uint32_t node_list_length can be replaced with global id_counter
    
    // set up vars
    struct node_t * current_edge_node;
    struct node_t * current_node;

    // create queue
    struct node_t * * queue = malloc(sizeof(struct node_t *) * id_counter);
    memset(queue, 0, sizeof(sizeof(struct node_t *) * id_counter));
    // add start node to queue
    struct node_t * start = search_dict(dictionairy, start_name, 0);
    assert("START NODE DOESN'T EXIST" && start != NULL);
    queue[0] = start;

    // find end node
    struct node_t * goal = search_dict(dictionairy, goal_name, 0);
    assert("GOAL NODE DOESN'T EXIST" && goal != NULL);

    // counter for queue length
    uint8_t queue_length = 1;

    // while queue is not empty
    while (queue_length > 0) {

        // POP (IN C)
        // copy last element in list
        current_node = queue[queue_length-1];
        // overwrite as NULL
        queue[queue_length-1] = NULL;
        queue_length --;
        current_node->in_queue = 0;

        // printf("POPPED NODE %s\n", current_node->name);

        // IS NODE GOAL? => DONE
        // if node.id == goal.id
        if (current_node == goal)
        {
            printf("Found goal\n");
            break;
        }
        

        // EXPAND NODE (IN C)
        // for i in range(node.numofactual)
        for (uint16_t i = 0; i < current_node->num_of_actual_edges; i++)
        {
            // n = node.edge[i].node
            current_edge_node = current_node->edges[i].node;
            // if n.shortest_path > node.shortest + edge.cost
            if (current_edge_node->shortest_distance > current_node->shortest_distance + current_node->edges[i].cost)
            {
                // n.shortest = node.shortest + edge.cost
                current_edge_node->shortest_distance = current_node->shortest_distance + current_node->edges[i].cost;
                // n.best_parent = node
                current_edge_node->best_parent = current_node;
                // printf("UPDATED NODE %s\n", current_edge_node->name);
                // if not n.in_queue
                if (!current_edge_node->in_queue)
                {
                    // last ++;
                    queue_length ++;
                    // queue[last] = n
                    queue[queue_length-1] = current_edge_node;
                    current_edge_node->in_queue = 1;
                    // printf("QUEUED NODE %s\n", current_edge_node->name);

                }
            }
        }
        
        // SORT QUEUE
        // qsort
        qsort(queue, queue_length, sizeof(struct node_t *), comp_nodes);

    }
    // DO SOME SHID
};


void print_data(struct node_t * a) {
    printf("Id: %d\n", a->id);
    printf("Shortest path: %d\n", a->shortest_distance);
    printf("Best parent: %d\n", a->best_parent);
    printf("Actual edges: %d\n", a->num_of_actual_edges);
    printf("Edges available: %d\n", a->num_of_edges_available);
}

void print_path(struct node_t * goal) {
    struct node_t * parent = goal->best_parent;
    if (parent != NULL)
    {
        print_path(parent);
    }
    printf("%s\n", goal->name);    
}

int main(int argc, char const *argv[])
{

    struct dict_t root;
    initialize_dict(&root);

    struct dict_list_t root_list;
    initialize_dict_list(&root_list);
    root.characters = &root_list;

    // struct node_t * a;
    // a = initialize_node("HI");
    // struct node_t * b;
    // b = initialize_node("HELLO");

    search_dict(&root, "HI", 0);

    // add_node_to_dict(&root, a, 0);
    // add_node_to_dict(&root, b, 0);

    // assert(search_dict(&root, "HELLO", 0) == b);
    // assert(search_dict(&root, "HI", 0) == a);
    struct node_t * * nodelist = read_data(&root);

    dijkstra(nodelist, &root, "B", "F");

    print_path(search_dict(&root, "F", 0));

    return 0;
}