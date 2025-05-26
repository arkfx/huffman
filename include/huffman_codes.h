#ifndef HUFFMAN_CODES_H
#define HUFFMAN_CODES_H

#include "huffman_common.h"
#include "huffman_tree.h"

// Encoding and decoding functions
void generateCodes(Node* root, int arr[], int top, char** codes);
char* encodeData(unsigned char* data, int size, char** codes);
char* decodeData(Node* root, char* encodedData, int decodedSize);
void freeCodes(char** codes);

#endif /* HUFFMAN_CODES_H */ 