#include <list.h>
#include <stddef.h>


typedef struct T_Item
{
    void* content;
    Item* previous;
    Item* next;
    List* list;
} Item;

typedef struct T_List
{
    void (*deleter)(void*);
    Item* first;
    Item* last;
} List;

void list_item_init(Item* item, List* list, void* content, Item* next, Item* previous);

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
    for(Item* it=list->first;it!=NULL;)
    {
        Item* newit = it->next;
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
        list->first = list->last = (Item*)malloc(sizeof(Item));
        list_item_init(list->first, list, content, NULL, NULL);
    }
    else
        list_item_insert_before(list->first, content);
}
void list_push_back(List* list, void* content)
{
    if (list->first==NULL)
    {
        list->first = list->last = (Item*)malloc(sizeof(Item));
        list_item_init(list->first, list, content, NULL, NULL);
    }
    else
        list_item_insert_after(list->last, content);
}
const Item* list_get_first_item(const List* list)
{
    return list->first;
}
const Item* list_get_last_item(const List* list)
{
    return list->last;
}
Item* list_get_first_item_mut(List* list)
{
    return list->first;
}
Item* list_get_last_item_mut(List* list)
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
    for(Item* it=list->first;it!=NULL;i++, it = it->next);
    return i;
}
const Item* list_find(const List* list, void* to_search)
{
    for(const Item* it = list_get_first_item(list); it!=NULL; it = list_item_get_next(it))
    {
        if (it->content == to_search)
            return it;
    }
    return NULL;
}
Item* list_find_mut(List* list, void* to_search)
{
    for(Item* it = list_get_first_item_mut(list); it!=NULL; it = list_item_get_next(it))
    {
        if (it->content == to_search)
            return it;
    }
    return NULL;
}
const Item* list_find_if(const List* list, char(*callback_finder)(void*))
{
    for(const Item* it = list_get_first_item(list); it!=NULL; it = list_item_get_next(it))
    {
        if (callback_finder(it->content))
            return it;
    }
    return NULL;
}
Item* list_find_if_mut(List* list, char(*callback_finder)(void*))
{
    for(Item* it = list_get_first_item_mut(list); it!=NULL; it = list_item_get_next(it))
    {
        if (callback_finder(it->content))
            return it;
    }
    return NULL;
}


void list_item_init(Item* item, List* list, void* content, Item* next, Item* previous)
{
    item->content = content;
    item->previous = previous;
    item->next = next;
    item->list = list;
}
void list_item_free(Item* item)
{
    if (item->content && list_get_deleter(item->list))
        list_get_deleter(item->list)(item->content);
}
void list_item_remove(Item* item)
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
const void* list_item_get(const Item* item)
{
    return item->content;
}
void* list_item_get_mut(Item* item)
{
    return item->content;
}
Item* list_item_insert_after(Item* item, void* content)
{
    Item* new_item = (Item*)malloc(sizeof(Item));
    list_item_init(new_item, item->list, content, item->next, item);
    if (item->next)
        item->next->previous = new_item;
    else
        item->list->last=new_item;
    item->next = new_item;
    return new_item;
}
Item* list_item_insert_before(Item* item, void* content)
{
    Item* new_item = (Item*)malloc(sizeof(Item));
    list_item_init(new_item, item->list, content, item, item->previous);
    if (item->previous)
        item->previous->next = new_item;
    else
        item->list->first=new_item;
    item->previous = new_item;
    return new_item;
}
Item* list_item_get_next(Item* item)
{
    return item->next;
}
Item* list_item_get_previous(Item* item)
{
    return item->previous;
}
Item* list_item_advance(Item* item, int n)
{
    if (n==0)
        return item;
    for (int i=0;item!=NULL && i!=n; (n>0)?i++:i--, item = item->next);
    return item;
}