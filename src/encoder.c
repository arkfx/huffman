#include "../include/huffman.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string_to_encode>\n", argv[0]);
        return 1;
    }
    
    unsigned char* input = (unsigned char*)argv[1];
    int size = strlen((char*)input);
    
    if (size == 0) {
        fprintf(stderr, "Error: Empty input string\n");
        return 1;
    }
    
    printf("Encoding string: %s\n", input);
    
    // Build the Huffman tree
    Node* root = buildHuffmanTree(input, size);
    
    // Generate codes for each character
    char* codes[MAX_CHAR] = {NULL};
    int arr[MAX_CHAR], top = 0;
    generateCodes(root, arr, top, codes);
    
    // Print the generated Huffman codes (for debugging)
    printf("\nHuffman Codes:\n");
    for (int i = 0; i < MAX_CHAR; i++) {
        if (codes[i] != NULL) {
            printf("%c: %s\n", i, codes[i]);
        }
    }
    
    // Encode the input string
    char* encodedData = encodeData(input, size, codes);
    printf("\nEncoded data: %s\n", encodedData);
    
    // Save to file
    const char* filename = "saida.huff";
    saveToFile(root, encodedData, size, filename);
    printf("\nCompressed data saved to %s\n", filename);
    
    // Print compression statistics
    int originalSize = size * 8;  // in bits
    int compressedSize = strlen(encodedData);
    printf("Original size: %d bits\n", originalSize);
    printf("Compressed size: %d bits\n", compressedSize);
    printf("Compression ratio: %.2f%%\n", 
           (1.0 - (float)compressedSize / originalSize) * 100);
    
    // Free allocated memory
    freeCodes(codes);
    free(encodedData);
    freeTree(root);
    
    return 0;
} 