#include "../include/huffman_tree.h"

// Create a new node
Node* createNode(unsigned char data, unsigned int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    
    return node;
}

// Build Huffman Tree
Node* buildHuffmanTree(unsigned char* data, int size) {
    if (size == 0) {
        // fprintf(stderr, "Warning: Input data is empty, cannot build Huffman tree.\n");
        return NULL; // Retorna NULL para entrada vazia
    }

    Node *left, *right, *top;
    
    // Step 1: Calculate frequency of each character
    unsigned* freq = (unsigned*)calloc(MAX_CHAR, sizeof(unsigned));
    if (!freq) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i < size; i++)
        freq[data[i]]++;
    
    // Step 2: Create a min heap with all the characters that appear in input
    unsigned char uniqueChars[MAX_CHAR];
    unsigned uniqueFreq[MAX_CHAR];
    int uniqueCount = 0;
    
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            uniqueChars[uniqueCount] = (unsigned char)i;
            uniqueFreq[uniqueCount] = freq[i];
            uniqueCount++;
        }
    }
    
    free(freq);
    
    // Handle edge case: only one unique character
    if (uniqueCount == 1) {
        Node* root = createNode('$', uniqueFreq[0]);
        root->left = createNode(uniqueChars[0], uniqueFreq[0]);
        root->right = NULL;
        return root;
    }
    
    // Create a min heap with capacity equal to distinct characters
    MinHeap* minHeap = createAndBuildMinHeap(uniqueChars, uniqueFreq, uniqueCount);
    
    // Iterate until there is only one node left in the heap
    while (!isSizeOne(minHeap)) {
        // Extract the two minimum frequency nodes
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        
        // Create a new internal node with frequency equal to sum of the two nodes
        // '$' is used as placeholder for internal nodes as they don't have actual characters
        top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        
        insertMinHeap(minHeap, top);
    }
    
    // The remaining node is the root of the Huffman Tree
    Node* root = extractMin(minHeap);
    freeMinHeap(minHeap);
    
    return root;
}

// Free the Huffman tree
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Print an array (for debugging)
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", arr[i]);
    printf("\n");
}

// Print Huffman codes (for debugging)
void printHuffmanCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printHuffmanCodes(root->left, arr, top + 1);
    }
    
    if (root->right) {
        arr[top] = 1;
        printHuffmanCodes(root->right, arr, top + 1);
    }
    
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        printArray(arr, top);
    }
} 