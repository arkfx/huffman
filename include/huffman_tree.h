#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "huffman_common.h"
#include "huffman_heap.h"

// Tree operation functions
Node* createNode(unsigned char data, unsigned int freq);
Node* buildHuffmanTree(unsigned char* data, int size);
void freeTree(Node* root);
void printHuffmanCodes(Node* root, int arr[], int top);
void printArray(int arr[], int n);

#endif /* HUFFMAN_TREE_H */ 