#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "slist.h"

extern snode* snode_create(int data, snode* next){
  snode* p = (snode*)malloc(sizeof(snode));
  p->data=data;
  p->next=next;
  return p;
}
extern slist* slist_create(void){
  slist* p = (slist*)malloc(sizeof(slist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;
  return p;
}

extern bool slist_empty(slist* list){
  return list->size ==0;
}
extern size_t slist_size(slist* list){
  return list->size;
}

extern void slist_popfront(slist* list){
  if(slist_empty(list)){
    printf("List is empty\n");
    return;
  }
  snode* p = list->head;
  list->head = list->head->next;
  free(p);
  --list->size;
}
extern void slist_popback(slist* list){
  if(slist_size(list)==1){ slist_popfront(list); return;}
  if(slist_empty(list)){  printf("List is empty\n"); return;}
  snode* p = list->head;
  while(p->next != list->tail){
    p = p->next;
  }
  p->next = NULL;
  free(list->tail);
  list->tail = p;
  --list->size;
}

extern void slist_pushfront(slist* list, int data){
  snode* p = snode_create(data, list->head);
  list->head = p;
  if(list->size == 0){list->tail = p;}
  ++list->size;
  if(p->next == NULL){list->tail=p;}
}
extern void slist_pushback(slist* list, int data){
  if(list->size ==0){slist_pushfront(list, data); return;}
  snode* p = snode_create(data, NULL);
  list->tail->next = p;
  ++list->size;
  if(p->next == NULL){list->tail=p;}

}

extern void slist_clear(slist* list){
list->head = NULL;
list->tail = NULL;
list->size = 0;
}

extern int slist_front(slist* list){
  if(slist_empty(list)){fprintf(stderr,"List is empty\n"); exit(1);}
  return list->head->data;
}
extern int slist_back(slist* list){
  if(slist_empty(list)){fprintf(stderr,"List is empty\n"); exit(1);}
  return list->tail->data;
}

extern void slist_print(slist* list, const char* msg){
  printf("list is created and is...\n");
  if(slist_empty(list)){printf("list is empty\n"); return;}
  snode* p = list->head;
  while (p!=NULL){
    printf("%d --> %p\n", p->data, p->next);
    p = p->next;
  }
  printf("list size is: %zu\n", list->size);
  printf("list is empty? ");
  if(slist_empty(list)){printf(" YES\n");}else printf(" NO\n");
  printf("assert front of list is: %d\n", slist_front(list));
  printf("assert back of list is : %d\n", slist_back(list));
  slist_clear(list);
  printf("after clearing the list, is the list now empty?");
  if(slist_empty(list)){printf(" YES\n");}else printf(" NO\n");
}



extern void slist_test(void){
  printf("//===================== TESTING SLIST =========================\n");
  slist test;
  test = *slist_create();
  slist_pushfront(&test,40 );
  slist_pushback(&test,30);
  slist_pushback(&test,20);
  slist_pushback(&test,10);
  slist_print(&test, " ");

  slist test2;
  test2 = *slist_create();
  slist_pushfront(&test,10 );
  slist_pushback(&test,30);
  slist_pushback(&test,50);
  slist_pushback(&test,70);
  slist_pushback(&test,90);
  slist_print(&test, " ");
  printf("//===================== END TESTING SLIST =========================\n");
}
