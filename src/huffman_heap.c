#include <stdio.h>
#include <stdlib.h>
#include "../include/huffman_tree.h"
#include "../include/huffman_heap.h"

// Create a min heap of given capacity
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(capacity * sizeof(Node*));
    if (!minHeap->array) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    return minHeap;
}

// Swap two nodes
void swapNodes(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// Standard min-heapify function
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left >= 0 && (unsigned int)left < minHeap->size && 
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    
    if (right >= 0 && (unsigned int)right < minHeap->size && 
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
    
    if (smallest != idx) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Check if size of heap is 1
int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Extract the minimum value node from heap
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    
    return temp;
}

// Insert a new node into the min heap
void insertMinHeap(MinHeap* minHeap, Node* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    
    minHeap->array[i] = minHeapNode;
}

// Build min heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Create and build a min heap
MinHeap* createAndBuildMinHeap(unsigned char* data, unsigned* freq, int size) {
    int i;
    MinHeap* minHeap = createMinHeap(size);
    
    for (i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    
    minHeap->size = size;
    buildMinHeap(minHeap);
    
    return minHeap;
}

// Free the min heap
void freeMinHeap(MinHeap* minHeap) {
    if (minHeap) {
        if (minHeap->array) {
            free(minHeap->array);
        }
        free(minHeap);
    }
} 