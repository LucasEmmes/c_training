#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct node_t {
    int id;
    char name[10];
};

struct dict_list_t {
    struct dictionairy_t * dicts[256];
};

struct dictionairy_t {
    struct node_t * node;
    struct dict_list_t * next_char;
};

struct node_t make_node(int id, char * name) {
    struct node_t node;
    node.id = id;
    strncpy(node.name, name, 10);
    return node;
}


struct dictionairy_t * add_entry(struct dictionairy_t * root, struct node_t * node, int depth) {


// struct dictionairy_t * add_entry(struct dictionairy_t * root, struct node_t * node, int depth) {
//     // struct dictionairy_t * new_root = malloc(sizeof(*new_root) + sizeof(struct dictionairy_t * ) * 256);
    
//     // If there is no node here, then it should have a pointer to a dict_list
//     if (root->node == NULL) {
        
//         // Get out the next char from the node name and check if it is occupied in dict_list
//         char c = node->name[0];ry_t * add_entry(struct dictionairy_t * root, struct node_t * node, int depth) {
//     // struct dictionairy_t * new_root = malloc(sizeof(*new_root) + sizeof(struct dictionairy_t * ) * 256);
    
//     // If there is no node here, then it should have a pointer to a dict_list
//     if (root->node == NULL) {
        
//         // Get out the next char from the node name and check if it is occupied in dict_list
//         char c = node->name[0];
        
//         // If not occupied
//         if (root->next_char->dicts[c] == 0) {
            
//             // Make new dict with node
//             struct dictionairy_t new_entry;
//             new_entry.node = node;

//             // Add new entry to dict_list
//             struct dictionairy_t d;
//             root->next_char->dicts[c] = &d;
//             root->next_char->dicts[c]->node = node;
//         }
//         // If occupied
//         else {
            
//         }
//     }
//     return root;
// }
        
//         // If not occupied
//         if (root->next_char->dicts[c] == 0) {
            
//             // Make new dict with node
//             struct dictionairy_t new_entry;
//             new_entry.node = node;

//             // Add new entry to dict_list
//             struct dictionairy_t d;
//             root->next_char->dicts[c] = &d;
//             root->next_char->dicts[c]->node = node;
//         }
//         // If occupied
//         else {
            
//         }
//     }
//     return root;
// }

int main(int argc, char const *argv[])
{
    struct node_t a;
    a = make_node(0, "Hello");    

    struct dictionairy_t dict;
    struct dictionairy_t * dict_root;
    dict_root = &dict;

    dict_root->node = NULL;
    struct dict_list_t charlist;
    memset(charlist.dicts, 0, sizeof(struct dictionairy_t *)*256);

    dict_root->next_char = &charlist;

    assert(dict_root->next_char->dicts['H'] == NULL && "1");
    dict_root = add_entry(dict_root, &a, 0);
    assert(dict_root->next_char->dicts['H'] == NULL && "2");

    return 0;
}
