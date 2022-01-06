#ifndef CSTLIKE_VECTOR_H
#define CSTLIKE_VECTOR_H
#include "core.h"
#include <stdlib.h>

typedef struct cstl_vector_t cstl_vector;

/// cstl_vector constructor and destructor
cstl_vector* vector_new(size_t size_item, deleter_t deleter);
void vector_init(cstl_vector* vect, size_t size_item, deleter_t);
void vector_clear(cstl_vector* vect);
void vector_free(cstl_vector* vect);

/// Modifiers
void vector_resize(cstl_vector* vect, size_t nb_items);
void vector_reserve(cstl_vector* vect, size_t nb_items);
void vector_shrink_to_fit(cstl_vector* vect);
void* vector_push_back_item(cstl_vector* vect);
void vector_pop_back_item(cstl_vector* vect);
void* vector_insert_item(cstl_vector* vect, size_t index);
void vector_remove_item(cstl_vector* vect, size_t index);

/// Accessors
const void* vector_get_item(const cstl_vector* vect, size_t index);
void* vector_get_item_mut(cstl_vector* vect, size_t index);
const void* vector_first_item(const cstl_vector* vect);
void* vector_first_item_mut(cstl_vector* vect);
const void* vector_last_item(const cstl_vector* vect);
void* vector_last_item_mut(cstl_vector* vect);
size_t vector_size(const cstl_vector* vect);
size_t vector_capacity(const cstl_vector* vect);
const void* vector_data(const cstl_vector* vect);
void* vector_data_mut(cstl_vector* vect);
deleter_t vector_deleter(const cstl_vector* vect);

#endif