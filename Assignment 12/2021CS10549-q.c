#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// The following is a employee in the organisation, it has the pointer to two more employees a subordinate_1 and a subordinate_2
struct Employee {
    int emp_id; // emp_ids will be unique
    char* emp_name;
    int emp_salary;
    struct Employee* subordinate_1;
    struct Employee* subordinate_2;
};

// The following function creates a employee and returns its pointer
struct Employee* create_employee(int id, char* name, int salary) {
    struct Employee* ptr = (struct Employee*) malloc(sizeof(struct Employee));
    ptr->emp_id = id;
    ptr->emp_salary = salary;
    ptr->emp_name = strdup(name);
    // strdup() creates a copy of the string or char pointer and stores it in the new char pointer of the employee
    ptr->subordinate_1 = NULL;
    ptr->subordinate_2 = NULL;
    return ptr;
}

// The following code creates a organisation from scanning the input file
struct Employee* create_company() {
    int id, salary;
    char name[100];
    scanf("%d", &id);
    if(id == -1) return NULL; // -1 is used when there is a NULL pointer ie when no value is present

    scanf("%s %d", name, &salary);
    struct Employee* par = create_employee(id, name, salary);

    par->subordinate_1 = create_company();
    par->subordinate_2 = create_company();
    
    return par;
}

// The following function 
void print_company_helper(struct Employee* ceo) {
    // take input
    if(!ceo) {
        printf("%d ", -1);
        return;
    }
    printf("%d %s %d ", ceo->emp_id, ceo->emp_name, ceo->emp_salary);
    print_company_helper(ceo->subordinate_1);
    print_company_helper(ceo->subordinate_2);
    return;
}

void print_company(struct Employee* ceo) {
    print_company_helper(ceo);
    printf("\n");
    return;
} 

// --------------------------------------------------- YOU CAN EDIT BELOW THIS LINE -----------------------------------

struct Employee* CEO = NULL;
// CEO is a global pointer that points to the CEO of the company
struct Node* PythonListHead = NULL;
int n = 0; // number of employees

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
}

// delete the node at `ptr` and free its memory
void delete_node(struct Node* ptr) {
    free(ptr);
}

struct Node* get_node_at_pos(int position) {
    int pos = 0;
    struct Node* cur = PythonListHead;
    while(cur) {
        if(pos == position) return cur;
        pos++;
        cur = cur->next;
    }
    return NULL;
}

int len() {
    int length = 0;
    struct Node* cur = PythonListHead;
    while(cur) {
        length++;
        cur = cur->next;
    }
    return length;
}

void append(int x) {
    struct Node* cur = PythonListHead;
    if(cur == NULL) {
        // no list exists, we have to create one
        PythonListHead = create_node(x);
    }
    else {
        int pos = len() - 1;
        struct Node* last_node = get_node_at_pos(pos);
        last_node->next = create_node(x);
    }
}

void clear() {
    struct Node* cur = PythonListHead;
    PythonListHead = NULL;
    while(cur) {
        struct Node* next_node = cur->next;
        delete_node(cur);
        cur = next_node;
    }
}

void print_list(struct Node* head) {
    struct Node* cur = head;
    while(cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
}

struct Node* reverse_helper(struct Node* cur_node) {
    if(cur_node == NULL) return NULL;

    if(cur_node->next == NULL) {
        // this is the first node of the reversed list
        PythonListHead = cur_node;
        return cur_node;
    }

    // recursively solve for the next node
    struct Node* next_node = reverse_helper(cur_node->next);

    // set the next of next_node to cur_node
    next_node->next = cur_node;

    // also make the cur_node->next as NULL, since cur_node is the last node of the list
    cur_node->next = NULL;

    return cur_node;
}

// Reverse the elements of the list in place.
// Make sure you change `PythonListHead` accordingly
void reverse() {
    struct Node* last_node = reverse_helper(PythonListHead);
}

struct Employee* Boss_pointer(struct Employee* head, int id){
    if(head == NULL) return NULL;
    if(head->subordinate_1 == NULL && head->subordinate_2 == NULL) return NULL;
    struct Employee* s1 = NULL;
    struct Employee* s2 = NULL;
    if(head->subordinate_1 != NULL){
        if(head->subordinate_1->emp_id == id) return head;
        s1 = Boss_pointer(head->subordinate_1, id);
    }
    if(head->subordinate_2 != NULL){
        if(head->subordinate_2->emp_id == id) return head;
        s2 = Boss_pointer(head->subordinate_2, id);
    }
    if(s1 != NULL) return s1;
    if(s2 != NULL) return s2;
    return NULL;
}

// To find the level of the employee with id
int level_help(struct Employee* head, int id, int level){
    if(head == NULL) return -1;
    if(head->emp_id == id) return level;
    if(head->subordinate_1 == NULL && head->subordinate_2 == NULL) return -1;
    else{
        int s1 = level_help(head->subordinate_1, id, level+1);
        int s2 = level_help(head->subordinate_2, id, level+1);
        if(s1 != -1) return s1;
        if(s2 != -1) return s2;
        else return -1;
    }
}

// The following function returns the level of a employee with the given emp_id
int Level(int emp_id) {
    return level_help(CEO,emp_id,0);
}

struct Employee* CommonBoss(int id1, int id2, struct Employee* head){
    if(head == NULL) return NULL;
    if(head->emp_id == id1 || head->emp_id == id2) return head;
    struct Employee* sub1 = CommonBoss(id1, id2, head->subordinate_1);
    struct Employee* sub2 = CommonBoss(id1, id2, head->subordinate_2);
    if(sub1 != NULL && sub2 != NULL) return head;
    if(sub1 == NULL && sub2 == NULL) return NULL;
    if(sub1 != NULL) return sub1;
    if(sub2 != NULL) return sub2;
}

// The below returns the employee id of the first common boss
int get_first_common_boss(int emp_id1,int emp_id2){
    if(emp_id1 == emp_id2){
        struct Employee* boss = Boss_pointer(CEO, emp_id1);
        if(boss == NULL) return -1;
        return boss->emp_id;
    }
    struct Employee* boss = CommonBoss(emp_id1, emp_id2, CEO);
    return boss->emp_id;
}

int depth(struct Employee* head){
    if(head == NULL) return -1;
    int d1 = depth(head->subordinate_1);
    int d2 = depth(head->subordinate_2);
    if(d1 >= d2) return d1+1;
    else return d2+1;
}

void last_name_helper(struct Employee* head, int i, struct Employee* emp){
    if(head == NULL) return;
    if(strcmp(head->emp_name, emp->emp_name) == 0)
        if(Level(head->emp_id) == i) printf("%d ", head->emp_id);
    last_name_helper(head->subordinate_1, i, emp);
    last_name_helper(head->subordinate_2, i, emp);
}

//Print the employees with the same last name sperated by a space in the order of their level
void same_last_names(int emp_id){
    int d = depth(CEO);
    struct Employee* emp = Boss_pointer(CEO, emp_id);
    if(emp == NULL) emp = CEO;
    if(emp->subordinate_1 != NULL) 
        if(emp->subordinate_1->emp_id == emp_id) emp = emp->subordinate_1;
    if(emp->subordinate_2 != NULL) 
        if(emp->subordinate_2->emp_id == emp_id) emp = emp->subordinate_2;
    for(int i = 0; i < d+1; i++)
        last_name_helper(CEO, i, emp);
    return;
}

void allBosses(struct Employee* boss){
    if(boss == NULL) return;
    append(boss->emp_id);
    boss = Boss_pointer(CEO, boss->emp_id);
    allBosses(boss);
    return;
}

// Print the bosses of the given employee in the order from CEO to immediate boss
void get_all_bosses(int emp_id){
    struct Employee* firstboss = Boss_pointer(CEO, emp_id);
    if(firstboss == NULL) append(-1);
    allBosses(firstboss);
    reverse();
    print_list(PythonListHead);
    clear();
    return;
}

double salary_calc(struct Employee* head, double salary){
    if(head == NULL) return salary;
    salary += head->emp_salary;
    n++;
    salary = salary_calc(head->subordinate_1, salary);
    salary = salary_calc(head->subordinate_2, salary);
    return salary;
}

// Return the average salary of the team with the given employee as head
double get_average_salary(int emp_id){
    struct Employee* emp = Boss_pointer(CEO, emp_id); // emp here stores the boss
    if(emp == NULL) emp = CEO;
    if(emp->subordinate_1 != NULL) 
        if(emp->subordinate_1->emp_id == emp_id) emp = emp->subordinate_1;
    if(emp->subordinate_2 != NULL) 
        if(emp->subordinate_2->emp_id == emp_id) emp = emp->subordinate_2;
    double totsal = salary_calc(emp, 0.00);
    double avgsal = totsal/n;
    n = 0;
    return avgsal;
}
// --------------------------------------------------- YOU CAN EDIT ABOVE THIS LINE -----------------------------------

/* The following driver code creates a organisation for you and based on the input file
it will call all the functions that are necessary, your job is to edit the functions
above the line. Their descriptions are in the pdf and in the comments in the code. */

int main(int argc, char const *argv[])
{
    CEO = create_company();
    print_company(CEO);

    int T; 
    scanf("%d", &T);

    char operation_type[100];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "get_first_common_boss") == 0) {
            int x,y;
            scanf("%d %d", &x, &y);
            int ans = get_first_common_boss(x,y);
            printf("%d\n", ans);
        } 
        else if(strcmp(operation_type, "same_last_names") == 0) {
            int x;
            scanf("%d", &x);
            same_last_names(x);
            printf("\n");
        } 
        else if(strcmp(operation_type, "get_all_bosses") == 0) {
            int x;
            scanf("%d", &x);
            get_all_bosses(x);
            printf("\n");
        } 
        else if(strcmp(operation_type, "get_average_salary") == 0) {
            int x;
            scanf("%d", &x);
            double ans = get_average_salary(x);
            printf("%.2f\n", ans);
        } 

    }

    return 0;
}
