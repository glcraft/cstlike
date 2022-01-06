#ifndef CSTLIKE_VECTOR_H
#define CSTLIKE_VECTOR_H
#include "core.h"
#include <stdlib.h>

typedef struct T_Vector Vector;

/// Vector constructor and destructor
Vector* vector_new(size_t size_item, deleter_t deleter);
void vector_init(Vector* vect, size_t size_item, deleter_t);
void vector_clear(Vector* vect);
void vector_free(Vector* vect);

/// Modifiers
void vector_resize(Vector* vect, size_t nb_items);
void vector_reserve(Vector* vect, size_t nb_items);
void vector_shrink_to_fit(Vector* vect);
void* vector_push_back_item(Vector* vect);
void vector_pop_back_item(Vector* vect);
void* vector_insert_item(Vector* vect, size_t index);
void vector_remove_item(Vector* vect, size_t index);

/// Accessors
const void* vector_get_item(const Vector* vect, size_t index);
void* vector_get_item_mut(Vector* vect, size_t index);
const void* vector_first_item(const Vector* vect);
void* vector_first_item_mut(Vector* vect);
const void* vector_last_item(const Vector* vect);
void* vector_last_item_mut(Vector* vect);
size_t vector_size(const Vector* vect);
size_t vector_capacity(const Vector* vect);
const void* vector_data(const Vector* vect);
void* vector_data_mut(Vector* vect);
deleter_t vector_deleter(const Vector* vect);

#endif