# string_dictionairy.c  

I figured it'd be useful to make my own "library" for dictionairies,  
such that I might sort data more effectively (and with less brain-pain)  
while I get more comfortable with c.

# Usage  
To make a new dictionairy, use `struct dictionairy_t * create_dictionairy(void)`  

When adding data, use `void dictionairy_add(struct dictionairy_t * root_dict, char * key, void * value)`  
where `root_dict` is your dictionairy pointer from above, `key` is the key for your entry
(only null-terminated strings please), and `value` is the pointer to whatever you want to store under that key.  

To search, use `void * search_dictionairy(struct dictionairy_t * root, char * key)`.  
This will return whatever it finds at that key, NULL otherwise.  

Finally, use `void destroy_dictionairy(struct dictionairy_t * root)` to destroy the dictionairy  
when finished, to free all the space malloc'ed by it.  