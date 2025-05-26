#include "../include/huffman_io.h"

// Forward declaration for the new helper if needed, or define it before reconstructTree
Node* reconstructTreeFromBuffer(int* pos, char* treeData, int treeSize);

// Write tree in pre-order to the file
void writeTreeToFile(Node* root, FILE* file) {
    if (!root)
        return;
    
    // If leaf node, write 1 followed by the character
    if (!root->left && !root->right) {
        fprintf(file, "1");
        fwrite(&root->data, sizeof(unsigned char), 1, file);
    } else {
        // If internal node, write 0
        fprintf(file, "0");
    }
    
    writeTreeToFile(root->left, file);
    writeTreeToFile(root->right, file);
}

// Save encoded data and tree to file
void saveToFile(Node* root, char* encodedData, int dataSize, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Failed to open file for writing\n");
        exit(1);
    }
    
    // Write original data size (for decoding)
    fwrite(&dataSize, sizeof(int), 1, file);
    
    // Write the tree in pre-order
    writeTreeToFile(root, file);
    
    // Mark end of tree with a special sequence
    fprintf(file, "2");  // End of tree marker
    
    // Write the encoded data (convert string to bits)
    int encodedLen = strlen(encodedData);
    
    // Write the bit length of encoded data
    fwrite(&encodedLen, sizeof(int), 1, file);
    
    // Convert string of '0' and '1' to actual bits
    unsigned char byte = 0;
    int bitCount = 0;
    
    for (int i = 0; i < encodedLen; i++) {
        if (encodedData[i] == '1')
            byte |= (1 << (7 - bitCount));
        
        bitCount++;
        
        if (bitCount == 8 || i == encodedLen - 1) {
            fwrite(&byte, sizeof(unsigned char), 1, file);
            byte = 0;
            bitCount = 0;
        }
    }
    
    fclose(file);
}

// New helper function to reconstruct tree from buffer
Node* reconstructTreeFromBuffer(int* pos, char* treeData, int treeSize) {
    if (*pos >= treeSize) {
        // fprintf(stderr, "Error: Unexpected end of tree data buffer during reconstruction.\n");
        return NULL;
    }
    
    char structural_char = treeData[*pos];
    (*pos)++;

    // Note: O marcador '2' deveria ser idealmente tratado pelo chamador que preenche treeData,
    // ou o treeSize deveria ser o tamanho ANTES do '2'.
    // Se structural_char for '2' aqui, e era o último, (*pos) já é >= treeSize na próxima chamada.
    // Se o '2' está *dentro* do treeSize, esta verificação é necessária.
    if (structural_char == '2') { 
        // fprintf(stderr, "Encountered end-of-tree marker '2' in buffer.\n");
        return NULL; 
    }
    
    if (structural_char == '1') {  // Leaf node
        if (*pos >= treeSize) { 
            // fprintf(stderr, "Error: Buffer underflow when expecting data byte for leaf node.\n");
            return NULL; 
        }
        unsigned char data_char = (unsigned char)treeData[*pos];
        (*pos)++;
        return createNode(data_char, 0);
    }
    
    // Internal node (should be '0')
    if (structural_char != '0') {
        // fprintf(stderr, "Error: Expected '0' for internal node in tree data, got '%c'.\n", structural_char);
        // return NULL; // Comportamento atual: assume que é '0' se não for '1' ou '2'
    }

    Node* node = createNode('$', 0);  // Placeholder for internal nodes
    node->left = reconstructTreeFromBuffer(pos, treeData, treeSize);
    node->right = reconstructTreeFromBuffer(pos, treeData, treeSize);
    
    return node;
}

// Read the tree from file
Node* reconstructTree(FILE* file) {
    char treeData[MAX_CHAR * 10]; 
    int treePos = 0;
    int c;
    
    // Read the serialized tree (structure and leaf data) into treeData buffer
    // This loop assumes '2' correctly marks the end of the tree stream.
    while ((c = fgetc(file)) != EOF) {
        treeData[treePos++] = (char)c;
        if (treePos > 1 && treeData[treePos-1] == '2' && treeData[treePos-2] != '1') {
             // A simple heuristic to detect '2' as a marker, not data.
             // This might be error-prone if '2' is a valid char data preceding '2' marker.
             // Or if a char data '1' precedes the '2' marker.
             // For now, we assume '2' is the marker and remove it from treeData for processing.
             treePos--; // Remove the '2' marker itself from the data to be processed by helper
             break;
        }
        if (treePos >= MAX_CHAR * 10) {
            fprintf(stderr, "Error: Tree data buffer overflow.\n");
            exit(1); // or return NULL
        }
    }
    if (c == EOF && (treePos == 0 || treeData[treePos-1] != '2')) {
        // fprintf(stderr, "Warning: Tree data stream ended before '2' marker or stream is empty.\n");
        // Depending on strictness, this could be an error.
    }

    // treePos is now the size of the actual tree representation in treeData (excluding the marker '2')

    int pos = 0;
    return reconstructTreeFromBuffer(&pos, treeData, treePos);
}

// Read encoded data and tree from file
void readFromFile(const char* filename, Node** treeRoot, char** encodedData, int* dataSize, int* originalSize) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file for reading\n");
        exit(1);
    }
    
    // Read the original data size
    fread(originalSize, sizeof(int), 1, file);
    
    // Reconstruct the Huffman tree
    *treeRoot = reconstructTree(file);
    
    // Read bit length of encoded data
    int bitLength;
    fread(&bitLength, sizeof(int), 1, file);
    
    // Allocate memory for encoded data (as string of '0' and '1')
    *encodedData = (char*)malloc(bitLength + 1);
    if (!*encodedData) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    // Read and convert bytes to string of '0' and '1'
    int bytesNeeded = (bitLength + 7) / 8;
    unsigned char* buffer = (unsigned char*)malloc(bytesNeeded);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    fread(buffer, sizeof(unsigned char), bytesNeeded, file);
    
    int bitIndex = 0;
    for (int i = 0; i < bytesNeeded && bitIndex < bitLength; i++) {
        for (int j = 0; j < 8 && bitIndex < bitLength; j++) {
            (*encodedData)[bitIndex++] = ((buffer[i] >> (7 - j)) & 1) + '0';
        }
    }
    (*encodedData)[bitIndex] = '\0';
    
    *dataSize = bitLength;
    
    free(buffer);
    fclose(file);
} 