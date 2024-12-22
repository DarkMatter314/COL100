#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
    int data;
    struct Node* next;
};

// create a node with data as x
struct Node* create_node(int x) {
    struct Node* ptr = malloc(sizeof(struct Node));
    ptr->next = NULL;
    ptr->data = x;
    return ptr;
};

// delete the node at `ptr` and free its memory
void delete_node(struct Node* ptr) {
    free(ptr);
}

// ------------------------------ Node struct definition ends here ------------------------------

// Use this to operate on the list, this will always point at the head of the list.
struct Node* PythonListHead = NULL;


// prints the list in space seperated format
void print_list(struct Node* head) {
    struct Node* cur = head;
    while(cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}


// Add an item to the end of the list
void append(int x) {
    struct Node* ptrref = PythonListHead;
    struct Node* ptrnew = create_node(x);
    if(PythonListHead == NULL){
        PythonListHead = ptrnew;
        return;
    }
    while(ptrref){
        if(ptrref->next == NULL) break;
        ptrref = ptrref->next;
    }
    ptrref->next = ptrnew;
}


// Insert an item at a given position. 
// The first argument is the index of the element before which to insert
// second argument is the value to insert at that position
// if the position does not exist, do nothing
void insert(int position, int x) {
    struct Node* ptrref = PythonListHead;
    struct Node* ptrnew = create_node(x);
    int counter = 0;
    if(ptrref == NULL && position == 0){
        PythonListHead = ptrnew;
        return;
    }
    if(position == 0){
        ptrnew->next = ptrref;
        PythonListHead = ptrnew;
        return;
    }
    while(ptrref){
        if(counter == position-1 && ptrref->next != NULL){
            ptrnew->next = ptrref->next;
            ptrref->next = ptrnew;
            break;
        }
        ptrref = ptrref->next;
        counter++;
    }
}


// Remove the item at the end of the list
void pop() {
    struct Node* ptrref = PythonListHead;
    if(ptrref == NULL) return;
    if(ptrref->next == NULL){
        delete_node(ptrref);
        PythonListHead = NULL;
        return;
    }
    while(ptrref){
        if((ptrref->next)->next == NULL){
            delete_node(ptrref->next->next);
            ptrref->next = NULL;
            break;
        }
        ptrref = ptrref->next;
    }   
}


// Remove all items from the list
void clear() {
    struct Node* ptrref = PythonListHead;
    while(ptrref){
        struct Node* ptrnew = ptrref;
        ptrref = ptrref->next;
        delete_node(ptrnew);
    }
    PythonListHead = NULL;
}


// Return the number of times x appears in the list.
int count(int x) {
    struct Node* ptrref = PythonListHead;
    int counter = 0;
    while(ptrref){
        if(ptrref->data == x) counter++;
        ptrref = ptrref->next;
    }
    return counter;
}


// Reverse the elements of the list in place.
// Make sure you change `PythonListHead` accordingly
void reverse() {
    if(PythonListHead == NULL || PythonListHead->next == NULL) return;
    struct Node* ptrrefprev = PythonListHead;
    struct Node* ptrref = PythonListHead->next;
    struct Node* ptrnew = PythonListHead->next->next;
    PythonListHead->next = NULL;
    while(ptrref){
        ptrref->next = ptrrefprev;
        ptrrefprev = ptrref;
        ptrref = ptrnew;
        if(ptrnew!=NULL) ptrnew = ptrnew->next;
    }
    PythonListHead = ptrrefprev;
}


// Return the number of elements in the list
int len() {
    struct Node* ptrref = PythonListHead;
    int length=0;
    while(ptrref){
        length++;
        ptrref = ptrref->next;
    }
    return length;
}


// Set the data attribute of the node at `position` to `x`
// if no such position, do nothing
void setitem(int position, int x) {
    struct Node* ptrref = PythonListHead;
    int counter = 0;
    while(ptrref){
        if(counter == position) ptrref->data = x;
        ptrref = ptrref->next;
        counter++;
    }
}


// Return the data of the node at `position` 
// if no such position, return -1
int getitem(int position) {
    struct Node* ptrref = PythonListHead;
    int counter = 0;
    int item = -1;
    while(ptrref){
        if(counter == position) item  = ptrref->data;
        ptrref = ptrref->next;
        counter++;
    }
    return item;
}


// erase the node at position
// if no such position, do nothing
void erase(int position) {
    struct Node* ptrref = PythonListHead;
    if(PythonListHead == NULL) return;
    if(position == 0){
        PythonListHead = PythonListHead->next;
        delete_node(ptrref);
        return;
    }
    int counter = 0;
    while(ptrref){
        if(counter == position-1 && ptrref->next != NULL){
            struct Node* ptrnew = ptrref->next;
            ptrref->next = ptrref->next->next;
            delete_node(ptrnew);
        }
        counter++;
        ptrref = ptrref->next;
    }
}


// Returns a the head of the newly formed Python List
// containing elements present in positions in the original List.
// Note: you have to create new Python List and return its head.
// Here positions is an array of size n.
// eg. if positions = [2, 3, 5], you need to return a newly formed list
// having nodes that were at position 2, 3 and 5 in the original list.
// if there is such a position that is not present in the original list, do nothing
// with that position.
struct Node* index_into(int *positions, int n) {
    struct Node* ptrref = PythonListHead;
    struct Node* listhead = NULL;
    struct Node* newptrref;  
    int counter = 0;
    int no = 1;
    for(int i=0;i<n;i++){
        while(ptrref){
            if(counter == positions[i]){
                if(no==1){
                    listhead = create_node(ptrref->data);
                    newptrref = listhead;
                    no++;
                }
                else{
                    struct Node* newptr = create_node(ptrref->data);
                    newptrref->next = newptr;
                    newptrref = newptr;
                    no++;
                }
            }
            ptrref = ptrref->next;
            counter++;
        }
        ptrref = PythonListHead;
        counter = 0;
    }
    return listhead;
}


// swaps the nodes present at `position` and `position+1`
// if either of  `position` or `position+1` does not exist, do nothing
void swap(int position) {
    if(position + 1 >= len()) return;
    struct Node* ptrref = PythonListHead;
    int counter = 0;
    if(position == 0){
        struct Node* temp1 = ptrref;
        struct Node* temp2 = ptrref->next;
        struct Node* temp3 = ptrref->next->next;
        PythonListHead = temp2;
        PythonListHead->next = temp1;
        PythonListHead->next->next = temp3;
        return;
    }
    while(ptrref){
        if(counter == position-1){
            struct Node* temp1 = ptrref->next;
            struct Node* temp2 = ptrref->next->next;
            struct Node* temp3 = ptrref->next->next->next;
            ptrref->next = temp2;
            ptrref->next->next = temp1;
            ptrref->next->next->next = temp3;
            break;
        }
        ptrref = ptrref->next;
        counter++;
    }
}

// sort the Python list
// you may use the above defined swap function to 
// implement bubble sort. But its upto you.
void sort() {
    struct Node* ptrref = PythonListHead;
    for(int i = 0; i < len()-1 ; i++){
        if(PythonListHead->data > PythonListHead->next->data){
            struct Node* temp1 = PythonListHead;
            struct Node* temp2 = PythonListHead->next;
            struct Node* temp3 = PythonListHead->next->next;
            PythonListHead = temp2;
            PythonListHead->next = temp1;
            PythonListHead->next->next = temp3;
        }
        ptrref = PythonListHead;
        for(int j = 1; j < len()-i-1; j++){
            if(ptrref->next->data > ptrref->next->next->data){
                struct Node* temp1 = ptrref->next;
                struct Node* temp2 = ptrref->next->next;
                struct Node* temp3 = ptrref->next->next->next;
                ptrref->next = temp2;
                ptrref->next->next = temp1;
                ptrref->next->next->next = temp3;
            }
            ptrref = ptrref->next;
        }
        ptrref = PythonListHead;
    }
}


// ----------------------- Driver program starts here -----------------------

int main(int argc, char const *argv[])
{
    int T; 
    scanf("%d", &T);

    char operation_type[20];
    int indices[100];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "append") == 0) {
            int x;
            scanf("%d", &x);
            append(x);
        } 

        if(strcmp(operation_type, "insert") == 0) {
            int pos, x;
            scanf("%d %d", &pos, &x);
            insert(pos, x);
        }

        if(strcmp(operation_type, "pop") == 0) {
            pop();
        }

        if(strcmp(operation_type, "clear") == 0) {
            clear();
        }

        if(strcmp(operation_type, "count") == 0) {
            int x;
            scanf("%d", &x);
            int cnt = count(x);
            printf("%d\n", cnt);
        }

        if(strcmp(operation_type, "reverse") == 0) {
            reverse();
        }

        if(strcmp(operation_type, "len") == 0) {
            int length = len();
            printf("%d\n", length);
        }

        if(strcmp(operation_type, "setitem") == 0) {
            int pos, x;
            scanf("%d %d", &pos, &x);
            setitem(pos, x);
        }

        if(strcmp(operation_type, "getitem") == 0) {
            int pos;
            scanf("%d", &pos);
            int value = getitem(pos);
            printf("%d\n", value);
        }

        if(strcmp(operation_type, "print") == 0) {
            print_list(PythonListHead);
        }

        if(strcmp(operation_type, "erase") == 0) {
            int pos;
            scanf("%d", &pos);
            erase(pos);
        }

        if(strcmp(operation_type, "swap") == 0) {
            int pos;
            scanf("%d", &pos);
            swap(pos);
        }

        if(strcmp(operation_type, "index_into") == 0) {
            int n;
            scanf("%d", &n);
            for(int i=0;i<n;i++) scanf("%d", &indices[i]);
            struct Node* new_head = index_into(indices, n);
            print_list(new_head);
        }

        if(strcmp(operation_type, "sort") == 0) {
            sort();
        }
    }
}