#include <cstlike/vector.h>
#include <string.h>

cstl_vector* vector_new(size_t size_item, deleter_t deleter)
{
    cstl_vector* res = malloc(sizeof(cstl_vector));
    vector_init(res, size_item, deleter);
    return res;
}
void vector_init(cstl_vector* vect, size_t size_item, deleter_t deleter)
{
    assert(size_item > 0);
    vect->data = NULL;
    vect->size = 0;
    vect->capacity = 0;
    vect->size_item = size_item;
    vect->deleter = deleter;
}
void vector_clear(cstl_vector* vect)
{
    if (vect->deleter)
    {
        for(size_t i=0;i<vect->size;i++)
            vect->deleter(vector_get_item_mut(vect, i));
    }
    vect->size = 0;
}
void vector_free(cstl_vector* vect)
{
    vector_clear(vect);
    if (vect->data)
        free(vect->data);
    free(vect);
}

/// Modifiers
void vector_resize(cstl_vector* vect, size_t nb_items)
{
    if (nb_items > vect->capacity)
        vector_reserve(vect, nb_items);
    vect->size = nb_items;
}
void vector_reserve(cstl_vector* vect, size_t nb_items)
{
    if (nb_items > vect->capacity)
    {
        vect->data = realloc(vect->data, nb_items*vect->size_item);
        vect->capacity = nb_items;
    }
}
void vector_shrink_to_fit(cstl_vector* vect)
{
    if (vect->size < vect->capacity)
    {
        vect->data = realloc(vect->data, vect->size*vect->size_item);
        vect->capacity = vect->size;
    }
}
void vector_increment_size(cstl_vector* vect)
{
    if (vect->capacity == 0)
        vector_reserve(vect, 10);
    if (vect->size == vect->capacity)
        vector_reserve(vect, vect->capacity*2);
    vect->size++;
}
void* vector_push_back_item(cstl_vector* vect)
{
    vector_increment_size(vect);
    return vector_get_item_mut(vect, vect->size-1);
}
void vector_pop_back_item(cstl_vector* vect)
{
    vect->size--;
}
void* vector_insert_item(cstl_vector* vect, size_t index)
{
    vector_increment_size(vect);
    for(size_t i=vect->size-1;i>index;i--)
        memcpy(vector_get_item_mut(vect, i), vector_get_item(vect, i-1), vect->size_item);
    return vector_get_item_mut(vect, index);
}
void vector_remove_item(cstl_vector* vect, size_t index)
{
    memcpy(vector_get_item_mut(vect, index), vector_get_item(vect, index+1), vect->size*vect->size_item);
    vect->size--;
}

/// Accessors
const void* vector_get_item(const cstl_vector* vect, size_t index)
{
    assert(index < vect->size);
    return vect->data + index * vect->size_item;
}
void* vector_get_item_mut(cstl_vector* vect, size_t index)
{
    assert(index < vect->size);
    return vect->data + index * vect->size_item;
}
const void* vector_first_item(const cstl_vector* vect)
{
    assert(vect->size > 0);
    return vect->data;
}
void* vector_first_item_mut(cstl_vector* vect)
{
    assert(vect->size > 0);
    return vect->data;
}

const void* vector_last_item(const cstl_vector* vect)
{
    assert(vect->size > 0);
    return vect->data + (vect->size - 1) * vect->size_item;
}
void* vector_last_item_mut(cstl_vector* vect)
{
    assert(vect->size > 0);
    return vect->data + (vect->size - 1) * vect->size_item;
}
size_t vector_size(const cstl_vector* vect)
{
    return vect->size;
}
size_t vector_capacity(const cstl_vector* vect)
{
    return vect->capacity;
}
const void* vector_data(const cstl_vector* vect)
{
    return vect->data;
}
void* vector_data_mut(cstl_vector* vect)
{
    return vect->data;
}
deleter_t vector_deleter(const cstl_vector* vect)
{
    return vect->deleter;
}