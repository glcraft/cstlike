#ifndef CSTLIKE_LIST_H
#define CSTLIKE_LIST_H

#include "core.h"

typedef struct cstl_list_item_t cstl_list_item;

typedef struct cstl_list_t cstl_list;

//cstl_list
cstl_list* list_new(deleter_t);
void list_init(cstl_list* gest, deleter_t);
void list_clear(cstl_list* gest);
void list_free(cstl_list* gest);
void list_push_front(cstl_list* gest, void* content);
void list_push_back(cstl_list* gest, void* content);
const cstl_list_item* list_get_first_item(const cstl_list* gest);
const cstl_list_item* list_get_last_item(const cstl_list* gest);
cstl_list_item* list_get_first_item_mut(cstl_list* gest);
cstl_list_item* list_get_last_item_mut(cstl_list* gest);
deleter_t list_get_deleter(const cstl_list* gest);
size_t list_size(const cstl_list* gest);
const cstl_list_item* list_find(const cstl_list* list, void*);
cstl_list_item* list_find_mut(cstl_list* list, void*);
const cstl_list_item* list_find_if(const cstl_list* list, char(*callback_finder)(void*));
cstl_list_item* list_find_if_mut(cstl_list* list, char(*callback_finder)(void*));

void list_item_free(cstl_list_item* item);
void list_item_remove(cstl_list_item* item);
const void* list_item_get(const cstl_list_item* item);
void* list_item_get_mut(cstl_list_item* item);
cstl_list_item* list_item_get_next(cstl_list_item* item);
cstl_list_item* list_item_get_previous(cstl_list_item* item);
cstl_list_item* list_item_advance(cstl_list_item* item, int n);
cstl_list_item* list_item_insert_after(cstl_list_item* item, void* content);
cstl_list_item* list_item_insert_before(cstl_list_item* item, void* content);

#endif