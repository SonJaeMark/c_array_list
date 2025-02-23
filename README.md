# ArrayList - A Generic Dynamic Array for C/C++

## Overview
`ArrayList` is a lightweight, efficient dynamic array implementation for C and C++. It provides flexible memory management and supports generic data storage, including integers, strings, and structs. 

### **Features:**
- Works with any data type (`int`, `char*`, `struct`, etc.)
- Dynamic resizing
- Insert, delete, and search operations
- Custom comparators for struct-based data
- Thread-safe when used with external mutexes
- C++ compatibility with `extern "C"`

---

## Installation & Compilation

### **For C Projects**
```sh
gcc -o main main.c array_list.c -Wall -Wextra -std=c11
./main
```

### **For C++ Projects**
```sh
g++ -o main main.cpp array_list.c -Wall -Wextra -std=c++11
./main
```

📌 **Note**: `array_list.h` uses `extern "C"` for C++ compatibility.

---

## API Reference

### **1. Initialize an ArrayList**
```c
void arr_init(ArrayList *arrayList, size_t dataTypeSize);
```
**Description:** Allocates memory for a new ArrayList.

#### **Example:**
```c
ArrayList list;
arr_init(&list, sizeof(int));
```

### **2. Insert Elements**
```c
int arr_insert(ArrayList *arrayList, void *data);
```
**Description:** Adds an element to the end of the list. Resizes if necessary.

#### **Example:**
```c
int value = 42;
arr_insert(&list, &value);
```

### **3. Insert Multiple Elements**
```c
int arr_insertAll(ArrayList *arrayList, int count, ...);
```
**Description:** Inserts multiple elements at once.

#### **Example:**
```c
int a = 10, b = 20, c = 30;
arr_insertAll(&list, 3, &a, &b, &c);
```

### **4. Delete Element by Index**
```c
int arr_delete(ArrayList *arrayList, int index);
```
**Description:** Deletes an element at a given index, shifting elements accordingly.

#### **Example:**
```c
arr_delete(&list, 1); // Deletes the element at index 1
```

### **5. Delete Multiple Elements by Index**
```c
int arr_deleteAll(ArrayList *arrayList, int count, ...);
```
**Description:** Deletes multiple elements using a variable argument list.

#### **Example:**
```c
arr_deleteAll(&list, 2, 0, 2); // Deletes elements at indices 0 and 2
```

### **6. Delete First Occurrence of a Value**
```c
int arr_deleteFirst(ArrayList *arrayList, void *data, int (*cmpField)(void *, void *));
```
**Description:** Deletes the first occurrence of an element using a comparator.

#### **Example:**
```c
int target = 10;
arr_deleteFirst(&list, &target, compareInt);
```

### **7. Retrieve an Element by Index**
```c
void *arr_get(ArrayList *arrayList, int index);
```
**Description:** Returns a pointer to the element at the given index.

#### **Example:**
```c
int *retrieved = (int *)arr_get(&list, 0);
printf("Value: %d\n", *retrieved);
```

### **8. Find Index of an Element**
```c
int arr_getIndexOf(ArrayList *arrayList, void *data, int (*cmpField)(void *, void *));
```
**Description:** Returns the index of the first occurrence of an element using a comparator.

#### **Example:**
```c
int index = arr_getIndexOf(&list, &target, compareInt);
printf("Index: %d\n", index);
```

### **9. Update an Element by Index**
```c
int arr_set(ArrayList *arrayList, int index, void *data);
```
**Description:** Replaces an existing element at the given index.

#### **Example:**
```c
int newValue = 99;
arr_set(&list, 0, &newValue);
```

### **10. Get the Size of the ArrayList**
```c
size_t arr_size(ArrayList *arrayList);
```
**Description:** Returns the number of elements currently stored.

#### **Example:**
```c
printf("Size: %zu\n", arr_size(&list));
```

### **11. Get the Capacity of the ArrayList**
```c
size_t arr_capacity(ArrayList *arrayList);
```
**Description:** Returns the total allocated capacity.

#### **Example:**
```c
printf("Capacity: %zu\n", arr_capacity(&list));
```

### **12. Resize the ArrayList**
```c
void arr_resize(ArrayList *arrayList);
```
**Description:** Doubles the capacity when needed.

#### **Example:**
```c
arr_resize(&list);
```

### **13. Clear the ArrayList**
```c
int arr_clear(ArrayList *arrayList);
```
**Description:** Frees allocated memory and resets size.

#### **Example:**
```c
arr_clear(&list);
```

### **14. Compare Elements (For Structs)**
```c
int genericComparator(void *a, void *b, size_t dataTypeSize, int (*cmpField)(void *, void *));
```
**Description:** Allows for custom comparisons when dealing with structs.

#### **Example:**
```c
Person p1 = {"Alice", 25, 'F', {1, 15, 1998}, {"123 Main St", "Apt 4B"}};
Person p2 = {"Bob", 30, 'M', {3, 22, 1993}, {"456 Elm St", "Suite 2A"}};
int result = genericComparator(&p1, &p2, sizeof(Person), comparePersons);
printf("Comparison Result: %d\n", result);
```

---

## Conclusion
`ArrayList` is a **versatile and efficient dynamic array library** for C and C++. It offers easy-to-use functions for adding, removing, searching, and managing elements dynamically, making it a great choice for projects requiring flexible memory management.

🚀 **Supports:** Numbers, strings, structs, multi-threading, and more!

🔧 **Ideal for:** Small and large-scale projects needing dynamic arrays in C/C++.

Happy coding! 😃

