#pragma once

#include <stdlib.h>

typedef struct T_Item Item;

typedef struct T_List List;

typedef void (*deleter_t)(void*);

//List
List* list_new(deleter_t);
void list_init(List* gest, deleter_t);
void list_clear(List* gest);
void list_free(List* gest);
void list_push_front(List* gest, void* content);
void list_push_back(List* gest, void* content);
const Item* list_get_first_item(const List* gest);
const Item* list_get_last_item(const List* gest);
Item* list_get_first_item_mut(List* gest);
Item* list_get_last_item_mut(List* gest);
deleter_t list_get_deleter(const List* gest);
size_t list_size(const List* gest);
const Item* list_find(const List* list, void*);
Item* list_find_mut(List* list, void*);
const Item* list_find_if(const List* list, char(*callback_finder)(void*));
Item* list_find_if_mut(List* list, char(*callback_finder)(void*));

void list_item_free(Item* item);
void list_item_remove(Item* item);
const void* list_item_get(const Item* item);
void* list_item_get_mut(Item* item);
Item* list_item_get_next(Item* item);
Item* list_item_get_previous(Item* item);
Item* list_item_advance(Item* item, int n);
Item* list_item_insert_after(Item* item, void* content);
Item* list_item_insert_before(Item* item, void* content);