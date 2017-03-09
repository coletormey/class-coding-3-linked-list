//04_simple linked list
//!!!SOLUTION!!

#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *next;
};

/**
 * This is only for the 1st Node
 * @param head - pointer to the head of the list
 * @param n - data that the first element should hold
 */
void initNode(struct Node *head, int n) {
  head->data = n;
  head->next = nullptr;
}

/**
 * This funtion addes a node to the end of the list.
 * @param head - pointer to the head of the list
 * @param n - data that the new node should hold
 */
void addNode(struct Node *head, int n) {
    Node *tempNode = head; //to not mess up current head
  while(tempNode->next != nullptr){ //checks if it is the last node in the list
     tempNode = tempNode->next; //continuse to traverse if not
  }
    tempNode->next = new Node; //creates new node and sets it to the las nodes next
    tempNode = tempNode->next; //traverses to the new last node
    tempNode->data = n; //sets the new nodes data to n
}

/**
 * This funtion addes a node to the front of the list.
 * @param head - pointer to the head of the list
 * @param n - data that the new node should hold
 */
void insertFront(struct Node **head, int n) {
    Node *temp = new Node; //creates new node in heap
    temp->data = n; //sets data of the new node to n
    temp->next = *head; //sets the next of the new node to the current head
    *head = temp; //updates the head to the new head
    //**** order is very important so you don't lose the old head and cause memory leak
}

/**
 * This function displayes the nodes in the list
 * @param head  - pointer to the head of the list
 */
void display(struct Node *head) {
    if (head == nullptr){
        cout << "Nothing to display";
        return;
    }
    Node *tempNode = head;
  while(tempNode->next != nullptr){
      cout << tempNode->data << endl;
      tempNode = tempNode->next;
  }
        cout << tempNode->data << endl;
}

/**
 * This function searches for a node holding n and returns a pointer to it.
 * @param head - pointer to the head of the list
 * @param n - data to search nodes for
 * @return - pointer to the node found.
 */
struct Node *searchNode(struct Node *head, int n) {
    Node *tempNode = head; //to not mess with the head pointer
    while(tempNode->data != n){ //traverses data until a node with value n is found
        if(tempNode->next == nullptr){ //checks if the node is the last node
            tempNode = nullptr;//assigns tempnode to null to return it if the desired node isn't found
            break;//breaks out of while loop b/c the desired node wasn't found
        }
        tempNode = tempNode->next; //sets tempNode to the next node to continue traversing
    }
    return tempNode; //returns the found node or null
}

/**
 * This function deletes a node
 * @param head - pointer to the head of the list
 * @param ptrDel - pointer to the node that is to be deleted
 * @return - boolean that indicates if the deletion was successful
 */
bool deleteNode(struct Node **head, Node *ptrDel) {
  //TODO
    Node *current = *head;
    Node *last; //to keep track of last node
    while(current != ptrDel) {  //keeps looking until desired node is found
        if (current->next == nullptr) { //if the desired node isn't found by last node
            return false;
        }
        last = current; //otherwise, update last and current
        current = current->next;
    }
    //requested node is found
    if(current == *head){ //if the node is the first node in the list
        current = current->next; //to make sure you don't lost he address of the "new" head
        delete *head; //delete the first node
        *head = current; //assign the "new" head to head
    }else if(current->next == nullptr){ //if the last entry is the one to be deleted
        last->next = nullptr; //change the new "last" node's next to null
        delete current; //delete it
    }else{
        last->next = current->next; //assigns the last node's next to the current node's next to skip the current node
        delete current; //deletes
    }
  return true;
}

/* reverse the list */
struct Node *reverse(struct Node **head) {
  Node *parent = *head;
  Node *me = parent->next;
  Node *child = me->next;

  /* make parent as tail */
  parent->next = NULL;
  while (child) {
    me->next = parent;
    parent = me;
    me = child;
    child = child->next;
  }
  me->next = parent;
  *head = me;
  return *head;
}

/* Creating a copy of a linked list */
void copyLinkedList(struct Node *node, struct Node **pNew) {
  if (node != NULL) {
    *pNew = new Node;
    (*pNew)->data = node->data;
    (*pNew)->next = NULL;
    copyLinkedList(node->next, &((*pNew)->next));
  }
}

/* Compare two linked list */
/* return value: same(1), different(0) */
int compareLinkedList(struct Node *node1, struct Node *node2) {
  static int flag;

  /* both lists are NULL */
  if (node1 == NULL && node2 == NULL) {
    flag = 1;
  }
  else {
    if (node1 == NULL || node2 == NULL)
      flag = 0;
    else if (node1->data != node2->data)
      flag = 0;
    else
      compareLinkedList(node1->next, node2->next);
  }

  return flag;
}

void deleteLinkedList(struct Node **node) {
  struct Node *tmpNode;
  while (*node) {
    tmpNode = *node;
    *node = tmpNode->next;
    delete tmpNode;
  }
}

int main() {
  struct Node *newHead;
  struct Node *head = new Node;


  initNode(head,10);

  addNode(head,20);

  addNode(head,30);

  addNode(head,35);

  addNode(head,40);

  insertFront(&head,5);
  display(head);

  int numDel = 5;
  Node *ptrDelete = searchNode(head,numDel);
  if(deleteNode(&head,ptrDelete)) {
      cout << "Node " << numDel << " deleted!\n";
  }
    ptrDelete = searchNode(head,40);
    if(deleteNode(&head,ptrDelete)) {
        cout << "Node " << 40 << " deleted!\n";
    }
  display(head);
  cout << "The list is reversed\n";
  reverse(&head);
  display(head);

  cout << "The list is copied\n";
  copyLinkedList(head,&newHead);
  display(newHead);

  cout << "Comparing the two lists...\n";
  cout << "Are the two lists same?\n";
  if(compareLinkedList(head,newHead))
      cout << "Yes, they are same!\n";
  else
      cout << "No, they are different!\n";
  cout << endl;

  numDel = 35;
  ptrDelete = searchNode(newHead,numDel);
  if(deleteNode(&newHead,ptrDelete)) {
      cout << "Node "<< numDel << " deleted!\n";
      cout << "The new list after the delete is\n";
      display(newHead);
  }
  cout << "Comparing the two lists again...\n";
  cout << "Are the two lists same?\n";
  if(compareLinkedList(head,newHead))
      cout << "Yes, they are same!\n";
  else
      cout << "No, they are different!\n";

  cout << endl;
  cout << "Deleting the copied list\n";
  deleteLinkedList(&newHead);
    display(newHead);
  return 0;
}