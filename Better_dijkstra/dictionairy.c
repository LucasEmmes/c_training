#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct dictionairy_entry_t {
    char * key;
    void * value;
};

struct dictionairy_t {
    uint8_t depth;
    struct dictionairy_entry_t * entry;
    struct dictionairy_list_t * subdict_list;
};

struct dictionairy_list_t {
    struct dictionairy_t * dict_pointer[256];
};

// Used to initialize an dictionairy_entry_t element. Mallocs memory and sets attributes
struct dictionairy_entry_t * init_entry(char * key, void * value) {
    struct dictionairy_entry_t * new_entry = malloc(sizeof(key) + sizeof(value));
    new_entry->key = key;
    new_entry->value = value;
    return new_entry;
}

// Same but for dictionairy_t elements
struct dictionairy_t * init_dictionairy(uint8_t depth) {
    struct dictionairy_t * new_dict = malloc(sizeof(* new_dict));
    new_dict->depth = depth;
    new_dict->entry = NULL;
    new_dict->subdict_list = NULL;
    return new_dict;
}

// Same but for dictionairy_list_t elements
struct dictionairy_list_t * init_subdict_list() {
    struct dictionairy_list_t * new_subdict_list = malloc(sizeof(struct dictionairy_t *) * 256);
    memset(new_subdict_list, 0, sizeof(struct dictionairy_t *) * 256);
    return new_subdict_list;
}

// Adds a dictionairy_entry_t element to the dictionairy, and dynamically extends and
// re-arranges the dictionairy as neccessary
void make_dictionairy_entry(struct dictionairy_t * root_dict, struct dictionairy_entry_t * entry) {
    char c = entry->key[root_dict->depth];

    // Nothing occupying the current dict
    if (root_dict->entry == NULL) {

        // Subdict entry doesn't point anywhere
        if (root_dict->subdict_list->dict_pointer[c] == NULL) {
            // Make subdict to put at c
            struct dictionairy_t * new_dict = init_dictionairy(root_dict->depth + 1);
            root_dict->subdict_list->dict_pointer[c] = new_dict; 
            // Not new entry there
            new_dict->entry = entry;
        } else {
            make_dictionairy_entry(root_dict->subdict_list->dict_pointer[c], entry);
        }
    // There is something occupying the dict
    } else {
        char next_key_character = entry->key[root_dict->depth];

        // We're out of chcracters and cannot move the entry further down
        if (next_key_character == 0) {

            if (strcmp(root_dict->entry->key, entry->key)) {
                // Copy old entry
                struct dictionairy_entry_t * old_entry = root_dict->entry;
                // Move in new entry
                root_dict->entry = entry;

                if (root_dict->subdict_list == NULL) {
                    root_dict->subdict_list = init_subdict_list();
                }

                // Find out where to check next
                char next_old_entry_character = old_entry->key[root_dict->depth];

                if (root_dict->subdict_list->dict_pointer[next_old_entry_character] == NULL) {
                    root_dict->subdict_list->dict_pointer[next_old_entry_character] = init_dictionairy(root_dict->depth + 1);
                }

                make_dictionairy_entry(root_dict->subdict_list->dict_pointer[next_old_entry_character], entry);

            }

        // We *CAN* move the entry further down to make space
        } else {

            if (root_dict->subdict_list == NULL) {
                root_dict->subdict_list = init_subdict_list();
            }

            if (root_dict->subdict_list->dict_pointer[c] == NULL) {
                struct dictionairy_t * new_dict = init_dictionairy(root_dict->depth + 1);
                root_dict->subdict_list->dict_pointer[c] = new_dict;
                new_dict->entry = entry;
            } else {
                make_dictionairy_entry(root_dict->subdict_list->dict_pointer[c], entry);
            }
        }
    }
}

// Call this when adding items to your dict
void dictionairy_add(struct dictionairy_t * root_dict, char * key, void * value) {
    struct dictionairy_entry_t * entry = init_entry(key, value);
    make_dictionairy_entry(root_dict, entry);
}

// Call this function in your code to generate a fresh dictionairy which you can add entries to
struct dictionairy_t * create_dictionairy() {
    struct dictionairy_t * dict = init_dictionairy(0);
    dict->subdict_list = init_subdict_list();
    return dict;
}

// Use this to search for entries by their string-key in a given dictionairy
void * search_dictionairy(struct dictionairy_t * root, char * key) {
    if (root->entry != NULL) {
        if (!strcmp(root->entry->key, key)) {
            return root->entry->value;
        } else if (!key[root->depth]) {
            return NULL;
        } else if (root->subdict_list != NULL) {
            char c = key[root->depth];
            struct dictionairy_t * next_dict = root->subdict_list->dict_pointer[c];
            return search_dictionairy(next_dict, key);
        } else {
            return NULL;
        }
    } else if (root->subdict_list != NULL) {
        char c = key[root->depth];
        struct dictionairy_t * next_dict = root->subdict_list->dict_pointer[c];
        
        if (next_dict == NULL) {return NULL;}

        return search_dictionairy(next_dict, key);
    } else {
        return NULL;
    }
}

// Call this when you're done with your doctionairy to free up malloc'ed space
void destroy_dictionairy(struct dictionairy_t * root) {
    if (root->subdict_list != NULL) {
        for (int i = 0; i < 256; i++) {
            struct dictionairy_t * next_dict = root->subdict_list->dict_pointer[i];
            if (next_dict != NULL) {
                destroy_dictionairy(next_dict);
            }
        }
        free(root->subdict_list);
    }
    if (root->entry != NULL) {free(root->entry);}
    free(root);
}