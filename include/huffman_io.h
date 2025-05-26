#ifndef HUFFMAN_IO_H
#define HUFFMAN_IO_H

#include "huffman_common.h"
#include "huffman_tree.h"

// File I/O functions
void saveToFile(Node* root, char* encodedData, int dataSize, const char* filename);
void readFromFile(const char* filename, Node** treeRoot, char** encodedData, int* dataSize, int* originalSize);
void writeTreeToFile(Node* root, FILE* file);
Node* reconstructTree(FILE* file);

#endif /* HUFFMAN_IO_H */