#pragma once 

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INIT_CAPACITY 10

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t dataTypeSize;
} ArrayList;

void arr_init(ArrayList *arrayList, size_t dataTypeSize);
int arr_insert(ArrayList *arrayList, void *data);
int arr_insertAll(ArrayList *arrayList, int count, ...);
int arr_delete(ArrayList *arrayList, int index);
int arr_deleteAll(ArrayList *arrayList, int count, ...);
int arr_deleteFirst(ArrayList *arrayList, void *data, int (*cmpField)(void *, void *));
void *arr_get(ArrayList *arrayList, int index);
int arr_getIndexOf(ArrayList *arrayList, void *data, int (*cmpField)(void *, void *));
int arr_set(ArrayList *arrayList, int index, void *data);
size_t arr_size(ArrayList *arrayList);
size_t arr_capacity(ArrayList *arrayList);
void arr_resize(ArrayList *arrayList);
int arr_clear(ArrayList *arrayList);


int genericComparator(void *a, void *b, size_t dataTypeSize, int (*cmpField)(void *, void *));

#ifdef __cplusplus
}
#endif
