#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct dictionairy_entry_t {
    char * key;
    void * value;
};

struct dictionairy_t {
    __uint8_t depth;
    struct dictionairy_entry_t * entry;
    struct dictionairy_list_t * subdict_list;
};

struct dictionairy_list_t {
    struct dictionairy_t * * dict_pointer;
};

struct dictionairy_entry_t * init_entry(char * key, void * value) {
    struct dictionairy_entry_t * new_entry = malloc(sizeof(key) + sizeof(value));
    return new_entry;
}

struct dictionairy_t * init_dictionairy(__uint8_t depth) {
    struct dictionairy_t * new_dict = malloc(sizeof(* new_dict));
    new_dict->depth = depth;
    return new_dict;
}

struct dictionairy_list_t * init_subdict_list() {
    struct dictionairy_list_t * new_subdict_list = malloc(sizeof(struct dictionairy_t *) * 256);
    return new_subdict_list;
}

void make_dictionairy_entry(struct dictionairy_t * root_dict, struct dictionairy_entry_t * entry) {
    char c = entry->key[root_dict->depth];

    if (root_dict->entry == NULL) {
        assert(root_dict->subdict_list != NULL);

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
    } else {
        char next_key_character = entry->key[root_dict->depth];

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

            } else {
                printf("NODE IS ALREADY IN DICT");
            }

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

struct dictionairy_entry_t * search_dictionairy();

void destroy_dictionairy();

int main(int argc, char const *argv[])
{
    
    return 0;
}
