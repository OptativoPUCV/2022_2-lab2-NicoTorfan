#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *lista = (List*) calloc(1,sizeof(lista));   
  return lista;
}

void * firstList(List * list) {
  if(list->current  && list->head){
    list->current=list->head;
    return list->head->data;
  }
  return NULL;
}

void * nextList(List * list) {
    if(list->current  && list->current->next){
    list->current=list->current->next;
    return list->current->data;
  }
  return NULL;
}

void * lastList(List * list) {
     if(list->current  && list->tail){
    list->current=list->tail;
    return list->tail->data;
  }
  return NULL;
}


void * prevList(List * list) {
    if(list->current  && list->current->prev){
    list->current=list->current->prev;
    return list->current->data;
  }
  return NULL;
}

void pushFront(List * list, void * data) {
  Node * nodo = createNode(data);
  if(list->head){
    nodo->next=list->head;
    list->head->prev=nodo;
  }
  list->head=nodo;
  list->tail=nodo;
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * pushed = createNode(data);
  pushed->prev=list->current;
  list->current->next=pushed;
  list->tail=pushed;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node * nodoAux=createNode(list->current->data);
  Node * curent=list->current;
  if(curent==NULL){
    return NULL;
  }
  if (curent==list->tail){
    curent->prev->next=NULL;
    list->tail=curent->prev;
  }
  else if(list->head==curent){
    curent->next->prev=NULL;
    list->head=curent->next;
  }
  else{
    curent->prev->next=list->current->next;
    curent->next->prev=list->current->prev;
  }
  
  free(list->current);
  list->current=nodoAux->next;
    return nodoAux->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}