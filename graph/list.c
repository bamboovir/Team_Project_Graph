#include "list.h"  
  
void list_init(struct listnode *node)  
{  
    node->next = node;  
    node->prev = node;  
}  
  
void list_add_tail(struct listnode *head, struct listnode *item)  
{  
    item->next = head;  
    item->prev = head->prev;  
    head->prev->next = item;  
    head->prev = item;  
}  

void list_remove(struct listnode *item)  
{  if(!item) {
    item->next->prev = item->prev;  
    item->prev->next = item->next;  
    }
}

