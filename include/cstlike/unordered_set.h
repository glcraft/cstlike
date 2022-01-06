#ifndef CSTLIKE_UNORDERED_SET_H
#define CSTLIKE_UNORDERED_SET_H
#include "core.h"
#include <stdlib.h>
#include "vector.h"

typedef struct cstl_unordered_set_t {
    size_t (*hash)(void*);
    cstl_vector buffer;
} cstl_unordered_set;

/// cstl_unordered_set constructor and destructor
cstl_unordered_set* unordered_set_new(size_t size_item, deleter_t deleter);
void unordered_set_init(cstl_unordered_set* set, size_t size_item, deleter_t);
void unordered_set_clear(cstl_unordered_set* set);
void unordered_set_free(cstl_unordered_set* set);

/// Modifiers
void unordered_set_resize(cstl_unordered_set* set, size_t nb_items);
void unordered_set_reserve(cstl_unordered_set* set, size_t nb_items);
void unordered_set_shrink_to_fit(cstl_unordered_set* set);
void unordered_set_insert_from(cstl_unordered_set* set, void*);
void unordered_set_insert_inplace(cstl_unordered_set* set, void (*init_value_fn)(void*));


/// Accessors
void* unordered_set_find(cstl_unordered_set* set, void*);
void* unordered_set_find_if(cstl_unordered_set* set, bool (*compare_fn)(void*, void*));

#endif