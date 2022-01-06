#ifndef CSTLIKE_UNORDERED_SET_H
#define CSTLIKE_UNORDERED_SET_H
#include "core.h"
#include <stdlib.h>
#include "vector.h"

typedef struct cstl_unordered_set_t {
    size_t (*hash)(void*);
    cstl_vector buffer;
} cstl_unordered_set;

#endif