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
    struct dictionairy_t * dict_pointer[256];
};

struct dictionairy_entry_t * init_entry(char * key, void * value) {
    struct dictionairy_entry_t * new_entry = malloc(sizeof(key) + sizeof(value));
    new_entry->key = key;
    new_entry->value = value;
    return new_entry;
}

struct dictionairy_t * init_dictionairy(__uint8_t depth) {
    struct dictionairy_t * new_dict = malloc(sizeof(* new_dict));
    new_dict->depth = depth;
    new_dict->entry = NULL;
    new_dict->subdict_list = NULL;
    return new_dict;
}

struct dictionairy_list_t * init_subdict_list() {
    struct dictionairy_list_t * new_subdict_list = malloc(sizeof(struct dictionairy_t *) * 256);
    memset(new_subdict_list, 0, sizeof(struct dictionairy_t *) * 256);
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

struct dictionairy_t * create_dictionairy() {
    struct dictionairy_t * dict = init_dictionairy(0);
    dict->subdict_list = init_subdict_list();
    return dict;
}

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
        printf("ROOT MISSING ENTRY AND SUBDICT LIST");
        return NULL;
    }
}

void destroy_dictionairy();

struct data_t {
    int id;
};

int main(int argc, char const *argv[])
{
    struct data_t a;
    a.id = 69;
    
    struct data_t b;
    b.id = 420;

    struct dictionairy_t * dictionairy = create_dictionairy();
    struct dictionairy_entry_t * entry_a = init_entry("wow", &a);
    make_dictionairy_entry(dictionairy, entry_a);
    struct dictionairy_entry_t * entry_b = init_entry("wow2", &b);
    make_dictionairy_entry(dictionairy, entry_b);

    assert((struct data_t *) search_dictionairy(dictionairy, "wow") == &a);
    assert((struct data_t *) search_dictionairy(dictionairy, "wow2") == &b);

    return 0;
}
