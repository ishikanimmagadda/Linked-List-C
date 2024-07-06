#include <stdio.h>
#include <stdlib.h> 

// define the linked list node 
typedef struct node { 
    void* data; 
    struct node* next; 
}node;

typedef struct linkedlist {
    node* head; 
    size_t size; 
    void (*copy_data)(void *dest, void *src); //copying data from src location to destination
    void (*free_data)(void *data); // freeing space in memory 
}linkedlist;

void initialize_linked_list(linkedlist* list, size_t size, void (*copy_data)(void *dest, void *src),
    void (*free_data)(void *data)){
       list->head = NULL;
       list->size = 0; 
       list->copy_data = copy_data; 
       list->free_data = free_data;  
}

void addElement(linkedlist* list, void* data){ 
    node* newnode = (node*)malloc(sizeof(node)); // node you want to add 
    node* cur = list->head; 
    newnode->data = malloc(sizeof(data)); // making space for the data in the node 
    while(cur != NULL){ 
        cur = cur->next; 
    } // until list->head is the last element 

    cur->next = newnode; // giving space for the new element 
    newnode->data = data; //populating new node with data 
    cur->next->next = NULL; //resetting last element to NULL 
}

void removeElement (linkedlist* list, size_t index){ 
   int i = 0; 
   node* cur = list->head; 
   node* temp = NULL; 
   node* next = list->head->next; 

   if (index == 0) { 
        if(list->head == NULL){
           return "empty";
        }
        free(list->head);
        list->head = next;  
   }

   for(i=0; i < index-1; i++){
    if (cur->next == NULL){ //index out of bounds 
        return "out of bounds";
    }
    cur = cur->next; 
   }

   if (cur->next == NULL){
        return "empty"; 
   }

   temp = cur->next; 
   cur->next = temp->next;
   free(temp); 

   return "removed";
}

void accessElement (linkedlist* list, size_t index){
    node* cur = list->head; 
    int i = 0; 
    if (index >= list->size){ 
        return NULL;
    }

    for (int i = 0; i < index; i++){
        cur = cur->next; 
    }

    return cur; 
}

