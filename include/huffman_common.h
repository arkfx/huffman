#ifndef HUFFMAN_COMMON_H
#define HUFFMAN_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum ASCII value
#define MAX_CHAR 256

// Node structure for Huffman Tree
typedef struct Node {
    unsigned char data;
    unsigned int freq;
    struct Node *left, *right;
} Node;

// Min Heap structure
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    Node **array;
} MinHeap;

#endif /* HUFFMAN_COMMON_H */ 