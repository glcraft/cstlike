#include <cstlike/list.h>
#include <stddef.h>
#include <stdlib.h>

void list_item_init(cstl_list_item* item, cstl_list* list, void* content, cstl_list_item* next, cstl_list_item* previous);

//cstl_list
cstl_list* list_new(deleter_t d)
{
    cstl_list* res = malloc(sizeof(cstl_list));
    list_init(res, d);
    return res;
}
void list_init(cstl_list* list, void (*deleter)(void*))
{
    list->deleter = deleter;
    list->first = list->last = NULL;
}
void list_free(cstl_list* list)
{
    list_clear(list);
    free(list);
}
void list_clear(cstl_list* list)
{
    for(cstl_list_item* it=list->first;it!=NULL;)
    {
        cstl_list_item* newit = it->next;
        if (list->deleter)
            list->deleter(it->content);
        it = newit;
    }
    list->first = list->last = NULL;
}

void list_push_front(cstl_list* list, void* content)
{
    if (list->first==NULL)
    {
        list->first = list->last = (cstl_list_item*)malloc(sizeof(cstl_list_item));
        list_item_init(list->first, list, content, NULL, NULL);
    }
    else
        list_item_insert_before(list->first, content);
}
void list_push_back(cstl_list* list, void* content)
{
    if (list->first==NULL)
    {
        list->first = list->last = (cstl_list_item*)malloc(sizeof(cstl_list_item));
        list_item_init(list->first, list, content, NULL, NULL);
    }
    else
        list_item_insert_after(list->last, content);
}
const cstl_list_item* list_get_first_item(const cstl_list* list)
{
    return list->first;
}
const cstl_list_item* list_get_last_item(const cstl_list* list)
{
    return list->last;
}
cstl_list_item* list_get_first_item_mut(cstl_list* list)
{
    return list->first;
}
cstl_list_item* list_get_last_item_mut(cstl_list* list)
{
    return list->last;
}
deleter_t list_get_deleter(const cstl_list* list)
{
    return list->deleter;
}
size_t list_size(const cstl_list* list)
{
    size_t i=0;
    for(cstl_list_item* it=list->first;it!=NULL;i++, it = it->next);
    return i;
}
const cstl_list_item* list_find(const cstl_list* list, void* to_search)
{
    for(const cstl_list_item* it = list_get_first_item(list); it!=NULL; it = list_item_get_next(it))
    {
        if (it->content == to_search)
            return it;
    }
    return NULL;
}
cstl_list_item* list_find_mut(cstl_list* list, void* to_search)
{
    for(cstl_list_item* it = list_get_first_item_mut(list); it!=NULL; it = list_item_get_next_mut(it))
    {
        if (it->content == to_search)
            return it;
    }
    return NULL;
}
const cstl_list_item* list_find_if(const cstl_list* list, char(*callback_finder)(void*))
{
    for(const cstl_list_item* it = list_get_first_item(list); it!=NULL; it = list_item_get_next(it))
    {
        if (callback_finder(it->content))
            return it;
    }
    return NULL;
}
cstl_list_item* list_find_if_mut(cstl_list* list, char(*callback_finder)(void*))
{
    for(cstl_list_item* it = list_get_first_item_mut(list); it!=NULL; it = list_item_get_next_mut(it))
    {
        if (callback_finder(it->content))
            return it;
    }
    return NULL;
}


void list_item_init(cstl_list_item* item, cstl_list* list, void* content, cstl_list_item* next, cstl_list_item* previous)
{
    item->content = content;
    item->previous = previous;
    item->next = next;
    item->list = list;
}
void list_item_free(cstl_list_item* item)
{
    if (item->content && list_get_deleter(item->list))
        list_get_deleter(item->list)(item->content);
}
void list_item_remove(cstl_list_item* item)
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
const void* list_item_get(const cstl_list_item* item)
{
    return item->content;
}
void* list_item_get_mut(cstl_list_item* item)
{
    return item->content;
}
cstl_list_item* list_item_insert_after(cstl_list_item* item, void* content)
{
    cstl_list_item* new_item = (cstl_list_item*)malloc(sizeof(cstl_list_item));
    list_item_init(new_item, item->list, content, item->next, item);
    if (item->next)
        item->next->previous = new_item;
    else
        item->list->last=new_item;
    item->next = new_item;
    return new_item;
}
cstl_list_item* list_item_insert_before(cstl_list_item* item, void* content)
{
    cstl_list_item* new_item = (cstl_list_item*)malloc(sizeof(cstl_list_item));
    list_item_init(new_item, item->list, content, item, item->previous);
    if (item->previous)
        item->previous->next = new_item;
    else
        item->list->first=new_item;
    item->previous = new_item;
    return new_item;
}
const cstl_list_item* list_item_get_next(const cstl_list_item* item)
{
    return item->next;
}
const cstl_list_item* list_item_get_previous(const cstl_list_item* item)
{
    return item->previous;
}
cstl_list_item* list_item_get_next_mut(cstl_list_item* item)
{
    return item->next;
}
cstl_list_item* list_item_get_previous_mut(cstl_list_item* item)
{
    return item->previous;
}
cstl_list_item* list_item_advance(cstl_list_item* item, int n)
{
    if (n==0)
        return item;
    for (int i=0;item!=NULL && i!=n; (n>0)?i++:i--, item = item->next);
    return item;
}