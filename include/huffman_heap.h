#ifndef HUFFMAN_HEAP_H
#define HUFFMAN_HEAP_H

#include "huffman_common.h"

// Heap operation functions
MinHeap* createMinHeap(unsigned capacity);
void swapNodes(Node** a, Node** b);
void minHeapify(MinHeap* minHeap, int idx);
int isSizeOne(MinHeap* minHeap);
Node* extractMin(MinHeap* minHeap);
void insertMinHeap(MinHeap* minHeap, Node* minHeapNode);
void buildMinHeap(MinHeap* minHeap);
MinHeap* createAndBuildMinHeap(unsigned char* data, unsigned* freq, int size);
void freeMinHeap(MinHeap* minHeap);

#endif /* HUFFMAN_HEAP_H */ 