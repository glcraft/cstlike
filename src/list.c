#include <cstlike/list.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct T_ListItem
{
    void* content;
    ListItem* previous;
    ListItem* next;
    List* list;
} ListItem;

typedef struct T_List
{
    void (*deleter)(void*);
    ListItem* first;
    ListItem* last;
} List;

void list_item_init(ListItem* item, List* list, void* content, ListItem* next, ListItem* previous);

//List
List* list_new(deleter_t d)
{
    List* res = malloc(sizeof(List));
    list_init(res, d);
    return res;
}
void list_init(List* list, void (*deleter)(void*))
{
    list->deleter = deleter;
    list->first = list->last = NULL;
}
void list_free(List* list)
{
    list_clear(list);
    free(list);
}
void list_clear(List* list)
{
    for(ListItem* it=list->first;it!=NULL;)
    {
        ListItem* newit = it->next;
        if (list->deleter)
            list->deleter(it->content);
        it = newit;
    }
    list->first = list->last = NULL;
}

void list_push_front(List* list, void* content)
{
    if (list->first==NULL)
    {
        list->first = list->last = (ListItem*)malloc(sizeof(ListItem));
        list_item_init(list->first, list, content, NULL, NULL);
    }
    else
        list_item_insert_before(list->first, content);
}
void list_push_back(List* list, void* content)
{
    if (list->first==NULL)
    {
        list->first = list->last = (ListItem*)malloc(sizeof(ListItem));
        list_item_init(list->first, list, content, NULL, NULL);
    }
    else
        list_item_insert_after(list->last, content);
}
const ListItem* list_get_first_item(const List* list)
{
    return list->first;
}
const ListItem* list_get_last_item(const List* list)
{
    return list->last;
}
ListItem* list_get_first_item_mut(List* list)
{
    return list->first;
}
ListItem* list_get_last_item_mut(List* list)
{
    return list->last;
}
deleter_t list_get_deleter(const List* list)
{
    return list->deleter;
}
size_t list_size(const List* list)
{
    size_t i=0;
    for(ListItem* it=list->first;it!=NULL;i++, it = it->next);
    return i;
}
const ListItem* list_find(const List* list, void* to_search)
{
    for(const ListItem* it = list_get_first_item(list); it!=NULL; it = list_item_get_next(it))
    {
        if (it->content == to_search)
            return it;
    }
    return NULL;
}
ListItem* list_find_mut(List* list, void* to_search)
{
    for(ListItem* it = list_get_first_item_mut(list); it!=NULL; it = list_item_get_next(it))
    {
        if (it->content == to_search)
            return it;
    }
    return NULL;
}
const ListItem* list_find_if(const List* list, char(*callback_finder)(void*))
{
    for(const ListItem* it = list_get_first_item(list); it!=NULL; it = list_item_get_next(it))
    {
        if (callback_finder(it->content))
            return it;
    }
    return NULL;
}
ListItem* list_find_if_mut(List* list, char(*callback_finder)(void*))
{
    for(ListItem* it = list_get_first_item_mut(list); it!=NULL; it = list_item_get_next(it))
    {
        if (callback_finder(it->content))
            return it;
    }
    return NULL;
}


void list_item_init(ListItem* item, List* list, void* content, ListItem* next, ListItem* previous)
{
    item->content = content;
    item->previous = previous;
    item->next = next;
    item->list = list;
}
void list_item_free(ListItem* item)
{
    if (item->content && list_get_deleter(item->list))
        list_get_deleter(item->list)(item->content);
}
void list_item_remove(ListItem* item)
{
    list_item_free(item);
    if (item->list->first == item)
        item->list->first=item->next;
    if (item->list->last == item)
        item->list->last=item->previous;

    if (item->previous)
        item->previous->next = item->next;
    if (item->next)
        item->next->previous = item->previous;
    free(item);
}
const void* list_item_get(const ListItem* item)
{
    return item->content;
}
void* list_item_get_mut(ListItem* item)
{
    return item->content;
}
ListItem* list_item_insert_after(ListItem* item, void* content)
{
    ListItem* new_item = (ListItem*)malloc(sizeof(ListItem));
    list_item_init(new_item, item->list, content, item->next, item);
    if (item->next)
        item->next->previous = new_item;
    else
        item->list->last=new_item;
    item->next = new_item;
    return new_item;
}
ListItem* list_item_insert_before(ListItem* item, void* content)
{
    ListItem* new_item = (ListItem*)malloc(sizeof(ListItem));
    list_item_init(new_item, item->list, content, item, item->previous);
    if (item->previous)
        item->previous->next = new_item;
    else
        item->list->first=new_item;
    item->previous = new_item;
    return new_item;
}
const ListItem* list_item_get_next(const ListItem* item)
{
    return item->next;
}
const ListItem* list_item_get_previous(const ListItem* item)
{
    return item->previous;
}
ListItem* list_item_get_next_mut(ListItem* item)
{
    return item->next;
}
ListItem* list_item_get_previous_mut(ListItem* item)
{
    return item->previous;
}
ListItem* list_item_advance(ListItem* item, int n)
{
    if (n==0)
        return item;
    for (int i=0;item!=NULL && i!=n; (n>0)?i++:i--, item = item->next);
    return item;
}