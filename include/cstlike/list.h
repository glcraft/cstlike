#ifndef CSTLIKE_LIST_H
#define CSTLIKE_LIST_H

#include "core.h"

typedef struct T_ListItem ListItem;

typedef struct T_List List;

//List
List* list_new(deleter_t);
void list_init(List* gest, deleter_t);
void list_clear(List* gest);
void list_free(List* gest);
void list_push_front(List* gest, void* content);
void list_push_back(List* gest, void* content);
const ListItem* list_get_first_item(const List* gest);
const ListItem* list_get_last_item(const List* gest);
ListItem* list_get_first_item_mut(List* gest);
ListItem* list_get_last_item_mut(List* gest);
deleter_t list_get_deleter(const List* gest);
size_t list_size(const List* gest);
const ListItem* list_find(const List* list, void*);
ListItem* list_find_mut(List* list, void*);
const ListItem* list_find_if(const List* list, char(*callback_finder)(void*));
ListItem* list_find_if_mut(List* list, char(*callback_finder)(void*));

void list_item_free(ListItem* item);
void list_item_remove(ListItem* item);
const void* list_item_get(const ListItem* item);
void* list_item_get_mut(ListItem* item);
ListItem* list_item_get_next(ListItem* item);
ListItem* list_item_get_previous(ListItem* item);
ListItem* list_item_advance(ListItem* item, int n);
ListItem* list_item_insert_after(ListItem* item, void* content);
ListItem* list_item_insert_before(ListItem* item, void* content);

#endif