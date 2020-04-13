#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dlist.h"

extern dnode* dnode_create(int data, dnode* prev, dnode* next){
  dnode* p = (dnode*)malloc(sizeof(dnode));
  p->data = data;
  p->next = next;
  p->prev = prev;
  return p;
}
extern dlist* dlist_create(void){
  dlist* p = (dlist*)malloc(sizeof(dlist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;
  return p;
}

extern bool dlist_empty(dlist* list){
  return list->size == 0;
}
extern size_t dlist_size(dlist* list){
  return list->size;
}

extern void dlist_popfront(dlist* list){
  if(dlist_empty(list)){printf("List is empty\n"); return;}
  dnode* p = list->head;
  list->head = list->head->next;
  free(p);
  --list->size;
}

extern void dlist_popback(dlist* list){
  if (dlist_size(list)==1){dlist_popfront(list); return;}
  dnode* p = list->head;
  while (p->next != list->tail){p=p->next;}
  p->next=NULL;
  free(list->tail);
  list->tail=p;
  --list->size;
}

extern void dlist_pushfront(dlist* list, int data){
  dnode* p = dnode_create(data, NULL, list->head);
  list->head = p;
  if (p->next!=NULL){p->next->prev = p;}
  if(list->size==0){list->tail = p;}
  ++list->size;
  if(p->next == NULL){list->tail=p;}

}
extern void dlist_pushback(dlist* list, int data){
  if(list->size ==0){dlist_pushfront(list, data); return;}
  dnode* p = dnode_create(data, list->tail, NULL);
  list->tail->next=p;
  list->tail = p;
  ++list->size;
  if(p->next == NULL){list->tail=p;}

}

extern void dlist_clear(dlist* list){
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}
extern void dlist_print(dlist* list, const char* msg){
  printf("list is created and is...\n");
  if(dlist_empty(list)){printf("list is empty\n"); return;}
  dnode* p = list->head;
  while (p!=NULL){
    printf("%p <-- %d (%p) --> %p\n",p->prev, p->data,p, p->next);
    p = p->next;
  }
  printf("list size is: %zu\n", list->size);
  printf("list is empty? ");
  if(dlist_empty(list)){printf(" YES\n");}else printf(" NO\n");
  printf("assert front of list is: %d\n", dlist_front(list));
  printf("assert back of list is : %d\n", dlist_back(list));
  dlist_clear(list);
  printf("after clearing the list, is the list now empty?");
  if(dlist_empty(list)){printf(" YES\n");}else printf(" NO\n");
}

extern int dlist_front(dlist* list){
  return list->head->data;
}
extern int dlist_back(dlist* list){
  return list->tail->data;
}

extern void dlist_test(void){
  printf("//===================== TESTING DLIST =========================\n");
  dlist test;
  test = *dlist_create();
  dlist_pushfront(&test, 40);
  dlist_pushback(&test, 30);
  dlist_pushback(&test, 20);
  dlist_pushback(&test, 10);
  dlist_print(&test, " ");
  dlist test2;
  test2 = *dlist_create();
  dlist_pushfront(&test2, 10);
  dlist_pushback(&test2, 30);
  dlist_pushback(&test2, 50);
  dlist_pushback(&test2, 70);
  dlist_pushback(&test2, 90);
  dlist_print(&test2, " ");
  dlist test3;
  test3 =*dlist_create();
  dlist_pushfront(&test3, 0);
  for(int i=1;i<100;i++){
    dlist_pushback(&test3, i);
  }
  dlist_print(&test3, " ");
  printf("//===================== END TESTING DLIST =========================");
}
