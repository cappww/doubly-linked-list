/*
Capp Wiedenhoefer
DoublyLinkedList Assignment
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t{
  //Node contain the data as well as pointers to other nodes.
  int data;
  struct node_t *next;
  struct node_t *prev;
} node_t;

typedef struct list_t{
  //Lists have a size, a head node, and a tail node.
  int size;
  node_t* head;
  node_t* tail;
} list_t;

node_t* allocate(void){
  //Memory must be allocated for each node. It will be freed at the end of the
  //program
  node_t* nodePtr = malloc(sizeof(node_t));
  nodePtr -> next = NULL;
  nodePtr -> prev = NULL;
  return nodePtr;
}

void clearList(list_t list){
  //Used to free the memory of each node in the list.
  node_t* node = list.head;
  while(node != NULL){
    node = list.head -> next;
    free(list.head);
    list.head = node;
  }
}

void printList(list_t list){
  //Prints the data of all the nodes in the list.
  node_t* node = list.head -> next;
  while(node -> next != NULL){
    printf("%d, ", node->data);
    node = node -> next;
  }
  printf("\n");
  //Since the list is doubly linked, the list can be printed backwards.
  /*
  printf("Backwards: ");
  node = list.tail -> prev;
  while(node -> prev != NULL){
    printf("%d, ", node->data);
    node = node -> prev;
  }
  printf("\n");
  */
}

list_t initalizeList(){
  //Allocated memory for the head and tail of the list, sets size to 0, and
  //points the head to tail and vice versa.
  list_t list;
  list.size = 0;
  list.head = allocate();
  list.tail = allocate();
  list.head -> next = list.tail;
  list.tail -> prev = list.head;
  return list;
}

void insertAtEnd(int data, list_t* list){
  //Allocates new node, inserts it at the end of the list. Increases size by 1.
  node_t* node = allocate();
  node_t* temp = list -> tail -> prev;
  node -> data = data;

  list -> tail -> prev = node;
  node -> next = list -> tail;
  temp -> next = node;
  node -> prev = temp;
  list -> size = list -> size + 1;
}

void movePosition(int pos, int moveDistance, list_t list){
  //Moves a node to a different position in the list by changing its pointers.
  int newPos = pos - moveDistance;
  int i = 1;
  node_t* node = list.head -> next;
  node_t* temp1;
  node_t* temp2 = list.head -> next;
  node_t* temp3;
  node_t* temp4;

  //The first while loop finds the location of the node that must be moved.
  while(i < pos){
    node = node -> next;
    i++;
  }
  //The second loop finds the location of where the node must be moved.
  i = 1;
  while(i< newPos){
    temp2 = temp2 -> next;
    i++;
  }
  //Switch around the pointers until the node is in the right place.
  temp1 = temp2 -> prev;

  temp3 = node -> prev;
  temp4 = node -> next;

  temp3 -> next = temp4;
  temp4 -> prev = temp3;

  temp1 -> next = node;
  temp2 -> prev = node;

  node -> next = temp2;
  node -> prev = temp1;
}

int findPositionAndMove(int data, int moveDistance, list_t list){
  //Finds the position and then uses the movePosition function to move the node.
  node_t* node = list.head -> next;
  int pos = 1;
  while(node -> next != NULL){
    if(node -> data == data){
      movePosition(pos, moveDistance, list);
      //As the instructions state, the funciton returns the location of the node.
      return pos;
    } else{
      node = node -> next;
      pos++;
    }
  }
  //If there is no node with the right data,  the funciton returns -1.
  return -1;
}



int main(int argc, char const *argv[]) {

  list_t list = initalizeList();
  list_t* listPtr = &list;

  insertAtEnd(10, listPtr);
  insertAtEnd(11, listPtr);
  insertAtEnd(12, listPtr);
  insertAtEnd(13, listPtr);
  insertAtEnd(14, listPtr);
  insertAtEnd(15, listPtr);
  printList(list);
  printf("Added at least four nodes to the list.\n\n");

  findPositionAndMove(15, 4, list);
  printList(list);
  printf("Moved the tailing node (15) to somewhere other than the head\n\n");

  findPositionAndMove(14, list.size-1, list);
  printList(list);
  printf("Moved the tailing node (14) to the head of the list\n\n");

  findPositionAndMove(11, 3, list);
  printList(list);
  printf("Moved non tail (11) to the front of the list\n\n");

  findPositionAndMove(10, 1, list);
  printList(list);
  printf("Moved a non tail node (10) to a non head locaiton\n");

  clearList(list);


  return 0;
}
