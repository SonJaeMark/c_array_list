#include <stdio.h>
#include <string.h>
#include "array_list.h"

typedef struct {
    int MM;             /**< Month of birth */
    int DD;             /**< Day of birth */
    int YYYY;           /**< Year of birth */
} Date;

typedef struct {
    char *address1;     /**< First line of the address */
    char *address2;     /**< Second line of the address (optional) */
} Address;

typedef struct {
    char *name;         /**< Name of the person */
    int age;            /**< Age of the person */
    char gender;        /**< Gender of the person */
    Date dateOfBirth;   /**< Date of birth of the person */
    Address homeAddress; /**< Home address of the person */
} Person;



// Comparator for integers
int compareInt(void *a, void *b) {
    return (*(int *)a - *(int *)b);
}

// Comparator for strings
int compareString(void *a, void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

// Comparator for Person struct
int comparePerson(void *a, void *b) {
    return strcmp(((Person *)a)->name, ((Person *)b)->name);
}

void test_int_operations() {
    printf("\nTesting ArrayList with int:\n");
    ArrayList list;
    arr_init(&list, sizeof(int));

    int a = 10, b = 20, c = 30;
    arr_insert(&list, &a);
    arr_insert(&list, &b);
    arr_insert(&list, &c);
    
    printf("Size: %zu\n", arr_size(&list));
    printf("Value at index 1: %d\n", *(int *)arr_get(&list, 1));
    
    arr_delete(&list, 1);
    printf("After deletion, size: %zu\n", arr_size(&list));
    
    arr_clear(&list);
}

void test_string_operations() {
    printf("\nTesting ArrayList with strings:\n");
    ArrayList strList;
    arr_init(&strList, sizeof(char *));

    char *s1 = "Hello";
    char *s2 = "World";
    arr_insert(&strList, &s1);
    arr_insert(&strList, &s2);
    
    printf("String at index 1: %s\n", *(char **)arr_get(&strList, 1));
    
    arr_deleteFirst(&strList, &s1, compareString);
    printf("After deletion, size: %zu\n", arr_size(&strList));
    
    arr_clear(&strList);
}

void test_person_operations() {
    printf("\nTesting ArrayList with Person struct:\n");
    ArrayList people;
    arr_init(&people, sizeof(Person));

    Person p1 = {"Alice", 25, 'F', {1, 15, 1998}, {"123 Main St", "Apt 4B"}};
    Person p2 = {"Bob", 30, 'M', {3, 22, 1993}, {"456 Elm St", "Suite 2A"}};
    
    arr_insert(&people, &p1);
    arr_insert(&people, &p2);
    
    Person *retrieved = (Person *)arr_get(&people, 0);
    printf("Person at index 0: %s, Age: %d\n", retrieved->name, retrieved->age);
    
    arr_deleteFirst(&people, &p1, comparePerson);
    printf("After deletion, size: %zu\n", arr_size(&people));
    
    arr_clear(&people);
}

int main() {
    test_int_operations();
    test_string_operations();
    test_person_operations();
    return 0;
}
