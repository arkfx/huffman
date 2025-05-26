#include "../include/huffman.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    
    // Check if file exists
    FILE* test = fopen(filename, "rb");
    if (!test) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return 1;
    }
    fclose(test);
    
    // Variables to hold data from file
    Node* root = NULL;
    char* encodedData = NULL;
    int dataSize = 0;
    int originalSize = 0;
    
    // Read file
    printf("Reading compressed file: %s\n", filename);
    readFromFile(filename, &root, &encodedData, &dataSize, &originalSize);
    
    // Decode data
    printf("Decoding data...\n");
    char* decodedData = decodeData(root, encodedData, originalSize);
    
    // Display the result
    printf("\nDecoded string: %s\n", decodedData);
    
    // Free allocated memory
    free(encodedData);
    free(decodedData);
    freeTree(root);
    
    return 0;
} 