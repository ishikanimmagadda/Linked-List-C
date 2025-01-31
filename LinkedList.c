#include <stdio.h>
#include <stdlib.h>

// define the linked list node 
typedef struct node { 
    void* data; 
    struct node* next; 
} node;

typedef struct linkedlist {
    node* head; 
    size_t size; 
} linkedlist;

void initialize_linked_list(linkedlist* list){
    list->head = NULL;
    list->size = 0; 
}

void addElement(linkedlist* list, void* value){ 
    node* newnode = (node*)malloc(sizeof(node));
    if (newnode == NULL) {
        printf("Memory allocation failed");
        return; 
    }

    newnode->data = value; 

    if (list->head == NULL) {
        list->head = newnode;
    } else {
        node* cur = list->head;
        while (cur->next != NULL){ 
            cur = cur->next; 
        }
        cur->next = newnode; // giving space for the new element 
        cur->next->next = NULL;
    }
    list->size++;
}

void* removeElement(linkedlist* list, size_t index){ 
    if (index >= list->size) {
        printf("Index out of bounds");
        return NULL;
    }

    node* temp = NULL; 
    void* tempdata = NULL; 

    if (index == 0) { //removing first element 
        temp = list->head;
        tempdata = temp->data;
        list->head = list->head->next;
        free(temp);
        
    } else {
        node* cur = list->head; 
        for(int i=0; i < index-1; i++){ // all the way until one before the index node 
            cur = cur->next; 
        }
        temp = cur->next; // temp is the node you want to remove 
        tempdata = temp->data; 
        cur->next = temp->next; 
        free(temp); 
    }
    list->size--;
    return tempdata; 
}

void* accessElement (linkedlist* list, size_t index){
    node* cur = list->head;  
    if (index >= list->size){ 
        return NULL;
    }

    for (int i = 0; i < index; i++){
        cur = cur->next; 
    }

    return cur->data; 
}

void printList(linkedlist* list) {
    node* cur = list->head;
    while (cur != NULL) {
        printf("%d -> ", *(int*)(cur->data)); // (int*) casting to integer and *(int*) accesses value stored at address (cur->data)
        cur = cur->next;
    }
    printf("NULL\n");
}

int main() {
    linkedlist list;
    initialize_linked_list(&list); // assigns address of list to *list parameter- (which accesses value stored at address) 

    int a = 5;
    int b = 10;
    int c = 15;
    int d = 20;

    addElement(&list, &a);
    addElement(&list, &b);
    addElement(&list, &c);
    addElement(&list, &d);

    //initial list
    printf("Initial List: ");
    printList(&list);

    // Removing an element at index 2
    void* removedData = removeElement(&list, 2);
    if (removedData != NULL) {
        printf("Removed element: %d\n", *(int*)removedData);
    }

    printf("List after removing element at index 2: ");
    printList(&list);

    // Accessing an element at index 1
    void* accessedData = accessElement(&list, 1);
    if (accessedData != NULL) {
        printf("Accessed element at index 1: %d\n", *(int*)accessedData);
    }
}
