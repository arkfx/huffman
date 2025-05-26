#include "../include/huffman_codes.h"

// Generate Huffman codes
void generateCodes(Node* root, int arr[], int top, char** codes) {
    if (!root) { // Proteção contra nó nulo
        return;
    }

    // Se este é um nó folha, armazene o código construído a partir de 'arr'
    if (!root->left && !root->right) {
        codes[root->data] = (char*)malloc(top + 1);
        if (!codes[root->data]) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        
        for (int i = 0; i < top; i++) {
            codes[root->data][i] = arr[i] + '0';
        }
        codes[root->data][top] = '\0';
        return; // Importante: retornar após processar a folha
    }
    
    // Se não for folha, atribua 0 para a aresta esquerda e faça a recursão
    if (root->left) {
        arr[top] = 0;
        generateCodes(root->left, arr, top + 1, codes);
    }
    
    // Atribua 1 para a aresta direita e faça a recursão
    if (root->right) {
        arr[top] = 1;
        generateCodes(root->right, arr, top + 1, codes);
    }
}

// Encode data using Huffman codes
char* encodeData(unsigned char* data, int size, char** codes) {
    // Calculate the size of encoded string
    int encodedSize = 0;
    for (int i = 0; i < size; i++) {
        if (codes[data[i]] == NULL) {
            fprintf(stderr, "Error: No code found for character '%c'\n", data[i]);
            exit(1);
        }
        encodedSize += strlen(codes[data[i]]);
    }
    
    // Create the encoded string
    char* encodedData = (char*)malloc(encodedSize + 1);
    if (!encodedData) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    encodedData[0] = '\0';  // Initialize as empty string
    
    // Concatenate all codes
    for (int i = 0; i < size; i++) {
        strcat(encodedData, codes[data[i]]);
    }
    
    return encodedData;
}

// Decode data using Huffman tree
char* decodeData(Node* root, char* encodedData, int decodedSize) {
    char* decodedData = (char*)malloc(decodedSize + 1);
    if (!decodedData) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    int index = 0;
    Node* curr = root;
    
    // Handle edge case: single character tree
    if (!root->left && !root->right) {
        for (int i = 0; i < decodedSize; i++) {
            decodedData[index++] = root->data;
        }
        decodedData[index] = '\0';
        return decodedData;
    }
    
    // Handle edge case: tree with only left child
    if (!root->right && root->left && !root->left->left && !root->left->right) {
        for (int i = 0; i < decodedSize; i++) {
            decodedData[index++] = root->left->data;
        }
        decodedData[index] = '\0';
        return decodedData;
    }
    
    for (int i = 0; encodedData[i] && index < decodedSize; i++) {
        if (encodedData[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;
        
        if (!curr->left && !curr->right) {
            decodedData[index++] = curr->data;
            curr = root;
        }
    }
    
    decodedData[index] = '\0';
    return decodedData;
}

// Free codes array
void freeCodes(char** codes) {
    for (int i = 0; i < MAX_CHAR; i++) {
        if (codes[i] != NULL) {
            free(codes[i]);
        }
    }
} 