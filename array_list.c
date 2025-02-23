#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "array_list.h"

/**
 * @brief Initializes an ArrayList with a specified data type size.
 * 
 * This function sets the initial size, capacity, and data type size of the 
 * ArrayList. It also allocates memory for the array, ensuring dynamic growth.
 * If memory allocation fails, a message is printed.
 * 
 * @param arrayList Pointer to the ArrayList to be initialized.
 * @param dataTypeSize Size of each data element to be stored in the ArrayList.
 */
void arr_init(ArrayList *arrayList, size_t dataTypeSize) 
{
    // Initialize size and capacity
    arrayList->size = 0;
    arrayList->capacity = INIT_CAPACITY;
    arrayList->dataTypeSize = dataTypeSize;

    // Allocate memory for the array
#ifdef __cplusplus
    arrayList->data = new char[arrayList->capacity * arrayList->dataTypeSize]; // Use new in C++
#else
    arrayList->data = malloc(arrayList->capacity * arrayList->dataTypeSize); // Use malloc in C
#endif

    // Check if memory allocation was successful
    if (!arrayList->data) {
        printf("Memory allocation failed!\n");
    }
}



/**
 * @brief Inserts an element into the ArrayList.
 * 
 * This function adds a new element to the end of the ArrayList. If the 
 * ArrayList is full, it automatically resizes before inserting the new element.
 * 
 * @param arrayList Pointer to the ArrayList where the element will be inserted.
 * @param data Pointer to the data to be inserted.
 * @return 0 on success.
 */
int arr_insert(ArrayList *arrayList, void *data)
{
    // Check if the list is full; resize if needed
    if (arrayList->size == arrayList->capacity) 
    {
        arr_resize(arrayList);
    }

    // Calculate the destination address for the new element
    void *dest = (char *)arrayList->data + (arrayList->size * arrayList->dataTypeSize);

    // Copy the new data into the calculated position
    memcpy(dest, data, arrayList->dataTypeSize);

    // Increase the size of the list to reflect the new element
    arrayList->size++;

    return 0; // Success
}



/**
 * @brief Inserts multiple elements into the ArrayList.
 * 
 * This function allows inserting multiple elements at once using variable arguments.
 * If the ArrayList does not have enough capacity, it will be resized before insertion.
 * 
 * @param arrayList Pointer to the ArrayList where elements will be inserted.
 * @param count Number of elements to insert.
 * @param ... Variable arguments representing the elements to insert.
 * @return 0 on success.
 */
int arr_insertAll(ArrayList *arrayList, int count, ...) 
{
    va_list args;
    va_start(args, count);

    // Ensure the array has enough space for all new elements
    while (arrayList->size + count > arrayList->capacity) {
        arr_resize(arrayList);
    }

    // Iterate through the variable arguments and insert each element
    for (int i = 0; i < count; i++) {
        void *data = va_arg(args, void *); // Retrieve the next argument
        void *dest = (char *)arrayList->data + (arrayList->size * arrayList->dataTypeSize);
        
        // Copy the data into the calculated position
        memcpy(dest, data, arrayList->dataTypeSize);

        // Increase the size of the list
        arrayList->size++;
    }

    va_end(args);
    return 0; // Success
}



/**
 * @brief Deletes an element at a specific index in the ArrayList.
 * 
 * This function removes an element from the specified index and shifts the 
 * remaining elements to maintain list continuity. The size of the list is 
 * updated accordingly.
 * 
 * @param arrayList Pointer to the ArrayList.
 * @param index Index of the element to delete.
 * @return 0 on success, -1 if the index is invalid.
 */
int arr_delete(ArrayList *arrayList, int index)
{
    // Validate the index
    if (index < 0 || index >= arrayList->size) {
        return -1; // Return error if index is out of bounds
    }

    // Calculate the memory address of the element to be removed
    void *target = (char *)arrayList->data + (index * arrayList->dataTypeSize);
    void *next = (char *)target + arrayList->dataTypeSize;

    // Shift remaining elements to fill the gap
    memmove(target, next, (arrayList->size - index - 1) * arrayList->dataTypeSize);

    // Reduce the size of the list
    arrayList->size--;

    return 0; // Success
}



/**
 * @brief Deletes multiple elements at specified indices in the ArrayList.
 * 
 * This function removes multiple elements based on the provided indices.
 * To prevent shifting issues, it first sorts the indices in descending order 
 * before deletion.
 * 
 * @param arrayList Pointer to the ArrayList.
 * @param count Number of elements to delete.
 * @param ... Variable arguments specifying the indices to delete.
 * @return 0 on success.
 */
int arr_deleteAll(ArrayList *arrayList, int count, ...) {
    va_list args;
    va_start(args, count);
    int indices[count]; // Array to store indices to be deleted

    // Store indices from the variable arguments
    for (int i = 0; i < count; i++) {
        indices[i] = va_arg(args, int);
    }
    va_end(args);

    // Sort indices in descending order to prevent shifting issues
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (indices[i] < indices[j]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Delete elements starting from the highest index to the lowest
    for (int i = 0; i < count; i++) {
        arr_delete(arrayList, indices[i]);
    }

    return 0; // Success
}



/**
 * @brief Deletes the first occurrence of an element matching a custom comparator.
 * 
 * This function searches for the first element in the ArrayList that matches 
 * the given data using a custom comparator function. If found, the element is 
 * deleted, and the list is shifted accordingly.
 * 
 * @param arrayList Pointer to the ArrayList.
 * @param data Pointer to the element to delete.
 * @param cmpField Function pointer for custom comparison.
 * @return 0 on success, 1 if the element is not found.
 */
int arr_deleteFirst(ArrayList *arrayList, void *data, int (*cmpField)(void *, void *)) 
{
    // Iterate through the list to find the first matching element
    for (size_t i = 0; i < arrayList->size; i++) {
#ifdef __cplusplus
        void *current = reinterpret_cast<char *>(arrayList->data) + (i * arrayList->dataTypeSize);
#else
        void *current = (char *)arrayList->data + (i * arrayList->dataTypeSize);
#endif

        // Use the generic comparator function to check for a match
        if (genericComparator(current, data, arrayList->dataTypeSize, cmpField) == 0) {
            arr_delete(arrayList, i); // Delete the found element
            return 0; // Success
        }
    }

    return 1; // Element not found
}




/**
 * @brief Retrieves an element at a specific index in the ArrayList.
 * 
 * This function returns a pointer to the element at the specified index.
 * If the index is out of bounds, it returns NULL (or nullptr in C++).
 * 
 * @param arrayList Pointer to the ArrayList.
 * @param index Index of the element to retrieve.
 * @return Pointer to the element if found, NULL (or nullptr in C++) if the index is invalid.
 */
void *arr_get(ArrayList *arrayList, int index)
{
    // Validate index to ensure it's within bounds
    if (index < 0 || index >= (int)arrayList->size) {
#ifdef __cplusplus
        return nullptr; // Return nullptr in C++
#else
        return NULL; // Return NULL in C
#endif
    }

    // Calculate and return the memory address of the requested element
#ifdef __cplusplus
    return reinterpret_cast<char*>(arrayList->data) + (index * arrayList->dataTypeSize);
#else
    return (char *)arrayList->data + (index * arrayList->dataTypeSize);
#endif
}



/**
 * @brief Finds the index of an element using a custom comparator.
 * 
 * This function searches for an element in the ArrayList that matches 
 * the given data using a custom comparator function. If found, it returns 
 * the index of the first occurrence. If the element is not found, it returns -1.
 * 
 * @param arrayList Pointer to the ArrayList.
 * @param data Pointer to the element to search for.
 * @param cmpField Function pointer for custom comparison.
 * @return Index of the element if found, -1 if not found.
 */
int arr_getIndexOf(ArrayList *arrayList, void *data, int (*cmpField)(void *, void *)) 
{
    // Iterate through the list to find the matching element
    for (size_t i = 0; i < arrayList->size; i++) {
#ifdef __cplusplus
        void *current = reinterpret_cast<char *>(arrayList->data) + (i * arrayList->dataTypeSize);
#else
        void *current = (char *)arrayList->data + (i * arrayList->dataTypeSize);
#endif

        // Use the generic comparator function to check for a match
        if (genericComparator(current, data, arrayList->dataTypeSize, cmpField) == 0) {
            return (int)i; // Return index if found
        }
    }

    return -1; // Element not found
}



/**
 * @brief Updates an element at a specific index in the ArrayList.
 * 
 * This function replaces the existing element at the given index with new data.
 * If the index is out of bounds, the function returns an error.
 * 
 * @param arrayList Pointer to the ArrayList.
 * @param index Index of the element to modify.
 * @param data Pointer to the new data.
 * @return 0 on success, -1 if the index is invalid.
 */
int arr_set(ArrayList *arrayList, int index, void *data)
{
    // Validate index to ensure it's within bounds
    if (index < 0 || index >= arrayList->size) {
        return -1; // Return error if index is invalid
    }

    // Calculate the memory address of the target element
    void *target = (char *)arrayList->data + (index * arrayList->dataTypeSize);

    // Copy new data to the target location
    memcpy(target, data, arrayList->dataTypeSize);

    return 0; // Success
}



/**
 * @brief Retrieves the current number of elements in the ArrayList.
 * 
 * This function returns the number of elements currently stored in the ArrayList.
 * 
 * @param arrayList Pointer to the ArrayList.
 * @return The current size of the ArrayList.
 */
size_t arr_size(ArrayList *arrayList)
{
    return arrayList->size;
}


/**
 * @brief Retrieves the current capacity of the ArrayList.
 * 
 * This function returns the maximum number of elements the ArrayList can hold
 * before requiring a resize.
 * 
 * @param arrayList Pointer to the ArrayList.
 * @return The current capacity of the ArrayList.
 */
size_t arr_capacity(ArrayList *arrayList)
{
    return arrayList->capacity;
}


/**
 * @brief Doubles the capacity of the ArrayList when it reaches its limit.
 * 
 * This function increases the capacity of the ArrayList by a factor of two
 * using `realloc()`. If memory allocation fails, the function prints an error
 * message but retains the existing data.
 * 
 * @param arrayList Pointer to the ArrayList.
 */
void arr_resize(ArrayList *arrayList)
{
    // Calculate new capacity (double the previous size)
    size_t newCapacity = arrayList->capacity * 2;

    // Attempt to allocate new memory block with increased capacity
    void *newData = realloc(arrayList->data, newCapacity * arrayList->dataTypeSize);

    // Check if memory allocation was successful
    if (!newData) {
        printf("Memory allocation failed during resize!\n");
        return; // Keep existing data instead of corrupting it
    }

    // Assign the newly allocated memory block to the array
    arrayList->data = newData;
    arrayList->capacity = newCapacity;
}



/**
 * @brief Clears all elements from the ArrayList and resets its capacity.
 * 
 * This function frees the memory allocated for the ArrayList and resets its size and capacity 
 * to the initial default. It then reallocates memory to prepare the list for future use.
 * 
 * @param arrayList Pointer to the ArrayList to be cleared.
 * @return 0 on success, 1 if memory reallocation fails.
 */
int arr_clear(ArrayList *arrayList) 
{
    // Free allocated memory based on C or C++ environment
#ifdef __cplusplus
    delete[] (char*)arrayList->data;
#else
    free(arrayList->data);
#endif

    // Reset size and capacity
    arrayList->size = 0;
    arrayList->capacity = INIT_CAPACITY;

    // Reallocate memory for future use
#ifdef __cplusplus
    arrayList->data = new char[arrayList->capacity * arrayList->dataTypeSize];
#else
    arrayList->data = malloc(arrayList->capacity * arrayList->dataTypeSize);
#endif

    // Check if memory allocation was successful
    if (!arrayList->data) {
        printf("Memory allocation failed!\n");
        return 1; // Error
    }
    return 0; // Success
}

/**
 * @brief Compares two elements using a custom or default memory comparison.
 * 
 * This function allows comparison of two elements using a custom comparator function. 
 * If no comparator is provided, it defaults to `memcmp()`, which compares raw memory.
 * 
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @param dataTypeSize Size of each element type.
 * @param cmpField Function pointer for custom comparison (optional).
 * @return 0 if elements are equal, non-zero otherwise.
 */
int genericComparator(void *a, void *b, size_t dataTypeSize, int (*cmpField)(void *, void *)) {
    // Use custom comparator if provided, otherwise use memcmp for raw memory comparison
    if (cmpField) {
        return cmpField(a, b);
    }
    return memcmp(a, b, dataTypeSize);
}
