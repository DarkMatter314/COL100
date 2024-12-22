#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// The following is a employee in the organisation, it has the pointer to two more employees a subordinate_1 and a subordinate_2
struct Employee {

    int emp_id; // emp_ids will be unique
    struct Employee* subordinate_1;
    struct Employee* subordinate_2;
};

// The following function creates a employee and returns its pointer
struct Employee* create_employee(int x) {
    struct Employee* ptr = (struct Employee*) malloc(sizeof(struct Employee));
    ptr->emp_id = x;
    ptr->subordinate_1 = NULL;
    ptr->subordinate_2 = NULL;
    return ptr;
}

// The following code creates a organisation from scanning the input file
struct Employee* create_company() {
    int x;
    scanf("%d", &x);

    if(x == -1) return NULL; // -1 is used when there is a NULL pointer ie when no value is present
    struct Employee* par = create_employee(x);

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
    printf("%d ", ceo->emp_id);
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
int diameter = -1;

/*  In this function you have to print all the employees at a given level, Note that ceo is at level 0
In any of the functions which involve printing you need not print -1 for NULL pointers */

// To find the pointer of the boss of the employee
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

// To print employees at same level
void SameLevelHelper(int level, struct Employee* head){
    if(head == NULL) return;
    if(Level(head->emp_id) == level) printf("%d ",head->emp_id);
    SameLevelHelper(level, head->subordinate_1);
    SameLevelHelper(level, head->subordinate_2);
}

void EmployeesAtSameLevel(int level) {
    SameLevelHelper(level, CEO);
    return;
}

// You have to print the employees as you search the organization look for the examples in the pdf and the input.txt and output.txt for details
// Note: You do not have to print -1 for NULL pointers

// To print all the employees
void get_employees_help(struct Employee* head){
    if(head == NULL) return;
    printf("%d ",head->emp_id);
    get_employees_help(head->subordinate_1);
    get_employees_help(head->subordinate_2);
}

void get_employees() {
    get_employees_help(CEO);
    return;
}

/* In the following function you have to print the immediate team of a employee - it includes their boss and their subordinates
Note: You do not have to print -1 for NULL pointers */

void ImmediateTeam(int emp_id) {
    if(CEO->emp_id == emp_id){
        if(CEO->subordinate_1 != NULL) printf("%d ", CEO->subordinate_1->emp_id);
        if(CEO->subordinate_2 != NULL) printf("%d ", CEO->subordinate_2->emp_id);
        return;
    }
    struct Employee* boss = Boss_pointer(CEO, emp_id);
    if(boss->subordinate_1 != NULL){
        if(boss->subordinate_1->emp_id == emp_id){
            printf("%d ", boss->emp_id);
            if(boss->subordinate_1->subordinate_1 != NULL) printf("%d ", boss->subordinate_1->subordinate_1->emp_id);
            if(boss->subordinate_1->subordinate_2 != NULL) printf("%d ", boss->subordinate_1->subordinate_2->emp_id);
        }
    }
    if(boss->subordinate_2 != NULL){
        if(boss->subordinate_2->emp_id == emp_id){
            printf("%d ", boss->emp_id);
            if(boss->subordinate_2->subordinate_1 != NULL) printf("%d ", boss->subordinate_2->subordinate_1->emp_id);
            if(boss->subordinate_2->subordinate_2 != NULL) printf("%d ", boss->subordinate_2->subordinate_2->emp_id);
        }
    }
    return;
}

/* The following function takes an emp_id this will belong to a employee in the organisation and your task is to return the emp_id of its boss
Note: If the boss does not exit return -1 */

int Boss(int emp_id) {
    struct Employee* boss = Boss_pointer(CEO, emp_id);
    if(boss == NULL) return -1;
    return boss->emp_id;
}

// To find the common boss of two employees
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

// The following function gives the distance between employees with emp_id1 and emp_id2
int Distance(int emp_id1, int emp_id2) {
    // If emp_id1 and emp_id2 are equal the distance is 0, both emp_id's will exist in the organisation
    struct Employee* common_boss = CommonBoss(emp_id1, emp_id2, CEO);
    return level_help(common_boss, emp_id1, 0) + level_help(common_boss, emp_id2, 0);
}

/* The following function returns the diameter of a Organisation - 
a diameter is the maximum distance between any two emp_ids in the organisation. You can use the distance function implemented above */

// To find the distance between head and the last intern below him
int findIntern(struct Employee* head, int level){
    if(head == NULL) return 0;
    if(head->subordinate_1 == NULL && head->subordinate_2 == NULL) return level;
    int lvl1, lvl2;
    if(head->subordinate_1 != NULL &&  head->subordinate_2 != NULL){
        lvl1 = findIntern(head->subordinate_1, level+1);
        lvl2 = findIntern(head->subordinate_2, level+1);
        if(lvl1>lvl2) return lvl1;
        else return lvl2;
    }
    if(head->subordinate_2 == NULL) return findIntern(head->subordinate_1, level+1);
    if(head->subordinate_1 == NULL) return findIntern(head->subordinate_2, level+1);
}

// Recursion to find diameter
int DiameterHelp(struct Employee* head){
    if(head == NULL) return 0;
    int dia = findIntern(head->subordinate_1, 1) + findIntern(head->subordinate_2, 1);
    int sub1dia = DiameterHelp(head->subordinate_1);
    int sub2dia = DiameterHelp(head->subordinate_2);
    if(sub1dia >= sub2dia){
        if(sub1dia >= dia) return sub1dia;
        else if(dia > sub1dia) return dia;
    }
    else if(sub2dia > sub1dia){
        if(sub2dia >= dia) return sub2dia;
        else if(dia > sub2dia) return dia;
    }
}

int Diameter() {
    if (diameter == -1) diameter = DiameterHelp(CEO);
    return diameter;
}

/* The following function takes an emp_id of a employee and returns the number of employees directly connected to it.
NULL pointers are not included */

int TeamSize(int emp_id) {
    int size = 0;
    if(CEO->emp_id == emp_id){
        if(CEO->subordinate_1 != NULL) size++;
        if(CEO->subordinate_2 != NULL) size++;
        return size;
    }
    struct Employee* boss = Boss_pointer(CEO, emp_id);
    if(boss->subordinate_1 != NULL){
        if(boss->subordinate_1->emp_id == emp_id){
            size++;
            if(boss->subordinate_1->subordinate_1 != NULL) size++;
            if(boss->subordinate_1->subordinate_2 != NULL) size++;
            return size;
        }
    }
    if(boss->subordinate_2->emp_id == emp_id){
        size++;
        if(boss->subordinate_2->subordinate_1 != NULL) size++;
        if(boss->subordinate_2->subordinate_2 != NULL) size++;
        return size;
    }
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

    char operation_type[50];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "level") == 0) {
            int x;
            scanf("%d", &x);
            int d = Level(x);
            printf("%d\n", d);
        } 

        if(strcmp(operation_type, "distance") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            int d = Distance(x, y);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "employees_at_same_level") == 0) {
            int x;
            scanf("%d", &x);
            EmployeesAtSameLevel(x);
            printf("\n");
        }

        if(strcmp(operation_type, "get_employees") == 0) {
            get_employees();
            printf("\n");
        }

        if(strcmp(operation_type, "boss") == 0) {
            int x;
            scanf("%d", &x);
            int d = Boss(x);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "diameter") == 0) {
            int d = Diameter();
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "immediate_team") == 0) {
            int x;
            scanf("%d", &x);
            ImmediateTeam(x);
            printf("\n");
        }

        if(strcmp(operation_type, "team_size") == 0) {
            int x;
            scanf("%d", &x);
            int d = TeamSize(x);
            printf("%d\n", d);
        }
    }

    return 0;
}