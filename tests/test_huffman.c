#include "../include/huffman.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Helper para imprimir resultado do teste de forma concisa
void print_test_result(const char* test_name, int success) {
    printf("%s: %s\n", test_name, success ? "PASSED" : "FAILED");
}

int test_basic_encoding_decoding() {
    const char* test_name = "Basic Encoding/Decoding (hello world)";
    unsigned char* input = (unsigned char*)"hello world";
    int size = strlen((char*)input);
    int success = 0;

    Node* root = buildHuffmanTree(input, size);
    if (!root) {
        printf("buildHuffmanTree failed for '%s'\n", input);
        print_test_result(test_name, success);
        return success;
    }

    char* codes[MAX_CHAR] = {NULL};
    int arr[MAX_CHAR], top = 0;
    generateCodes(root, arr, top, codes);

    char* encoded = encodeData(input, size, codes);
    if (!encoded) {
        printf("encodeData failed for '%s'\n", input);
        freeTree(root);
        freeCodes(codes);
        print_test_result(test_name, success);
        return success;
    }

    char* decoded = decodeData(root, encoded, size);
    if (!decoded) {
        printf("decodeData failed for '%s'\n", input);
        freeTree(root);
        freeCodes(codes);
        free(encoded);
        print_test_result(test_name, success);
        return success;
    }

    success = (strcmp((char*)input, decoded) == 0);
    if (!success) {
        printf("Mismatch for '%s': Original: '%s', Decoded: '%s'\n", input, input, decoded);
    }

    freeCodes(codes);
    free(encoded);
    free(decoded);
    freeTree(root);
    
    print_test_result(test_name, success);
    return success;
}

int test_file_operations() {
    const char* test_name = "File Operations (test string)";
    unsigned char* input = (unsigned char*)"test string for file operations";
    int size = strlen((char*)input);
    const char* filename = "test_file_ops.huff";
    int success = 0;

    Node* root = buildHuffmanTree(input, size);
    if (!root) { /* ... error handling ... */ print_test_result(test_name, 0); return 0; }

    char* codes[MAX_CHAR] = {NULL};
    int arr[MAX_CHAR], top = 0;
    generateCodes(root, arr, top, codes);

    char* encoded = encodeData(input, size, codes);
    if (!encoded) { /* ... error handling ... */ freeTree(root); freeCodes(codes); print_test_result(test_name, 0); return 0; }
    
    saveToFile(root, encoded, size, filename);

    Node* readRoot = NULL;
    char* readEncoded = NULL;
    int readDataSize = 0; // Renomeado para evitar confusão com dataSize global se houver
    int originalSizeFromFile = 0;
    
    readFromFile(filename, &readRoot, &readEncoded, &readDataSize, &originalSizeFromFile);
    if (!readRoot || !readEncoded) {
        printf("readFromFile failed for %s\n", filename);
        freeTree(root); freeCodes(codes); free(encoded); 
        if(readRoot) freeTree(readRoot); 
        if(readEncoded) free(readEncoded);
        print_test_result(test_name, success);
        return success;
    }

    char* decoded = decodeData(readRoot, readEncoded, originalSizeFromFile);
    if (!decoded) { /* ... error handling ... */ print_test_result(test_name, 0); /* cleanup */ return 0;}
    
    success = (strcmp((char*)input, decoded) == 0);
    if (!success) {
        printf("Mismatch for file op '%s': Original: '%s', Decoded: '%s'\n", input, input, decoded);
    }

    freeCodes(codes);
    free(encoded);
    free(readEncoded);
    free(decoded);
    freeTree(root);
    freeTree(readRoot);
    remove(filename); // Limpa o arquivo de teste
    
    print_test_result(test_name, success);
    return success;
}

int test_single_char_string() {
    const char* test_name = "Single Char String (aaaaa)";
    unsigned char* input = (unsigned char*)"aaaaa";
    int size = strlen((char*)input);
    int success = 0;

    Node* root = buildHuffmanTree(input, size);
    if (!root) { print_test_result(test_name, 0); return 0; }

    char* codes[MAX_CHAR] = {NULL};
    int arr[MAX_CHAR], top = 0;
    generateCodes(root, arr, top, codes);

    // Para uma string de um único caractere, o código deve ser "0"
    if (!codes['a'] || strcmp(codes['a'], "0") != 0) {
        printf("Incorrect code for 'a' in single char string: %s\n", codes['a'] ? codes['a'] : "NULL");
        freeTree(root); freeCodes(codes); print_test_result(test_name, 0); return 0;
    }

    char* encoded = encodeData(input, size, codes);
    if (!encoded) { freeTree(root); freeCodes(codes); print_test_result(test_name, 0); return 0; }

    char* decoded = decodeData(root, encoded, size);
    if (!decoded) { freeTree(root); freeCodes(codes); free(encoded); print_test_result(test_name, 0); return 0; }

    success = (strcmp((char*)input, decoded) == 0);
     if (!success) {
        printf("Mismatch for '%s': Original: '%s', Decoded: '%s'\n", input, input, decoded);
    }

    freeCodes(codes);
    free(encoded);
    free(decoded);
    freeTree(root);

    print_test_result(test_name, success);
    return success;
}

int test_unique_chars_string() {
    const char* test_name = "Unique Chars String (abcdef)";
    unsigned char* input = (unsigned char*)"abcdef";
    int size = strlen((char*)input);
    int success = 0;

    Node* root = buildHuffmanTree(input, size);
    if (!root) { print_test_result(test_name, 0); return 0; }

    char* codes[MAX_CHAR] = {NULL};
    int arr[MAX_CHAR], top = 0;
    generateCodes(root, arr, top, codes);

    char* encoded = encodeData(input, size, codes);
    if (!encoded) { freeTree(root); freeCodes(codes); print_test_result(test_name, 0); return 0; }

    char* decoded = decodeData(root, encoded, size);
    if (!decoded) { freeTree(root); freeCodes(codes); free(encoded); print_test_result(test_name, 0); return 0; }

    success = (strcmp((char*)input, decoded) == 0);
    if (!success) {
        printf("Mismatch for '%s': Original: '%s', Decoded: '%s'\n", input, input, decoded);
    }

    freeCodes(codes);
    free(encoded);
    free(decoded);
    freeTree(root);

    print_test_result(test_name, success);
    return success;
}

int test_empty_string() {
    const char* test_name = "Empty String ()";
    unsigned char* input = (unsigned char*)"";
    int size = strlen((char*)input);
    int success = 0;

    Node* root = buildHuffmanTree(input, size);
    if (root != NULL) { // Espera-se NULL para string vazia
        printf("buildHuffmanTree did not return NULL for empty string.\n");
        freeTree(root); // Limpa se algo foi criado erroneamente
        print_test_result(test_name, 0);
        return 0;
    }

    // Se root é NULL, encodeData não deve ser chamado com ele, ou deve lidar com root NULL.
    // Para este teste, consideramos sucesso se buildHuffmanTree retornou NULL.
    // Funções subsequentes como generateCodes, encodeData, decodeData não seriam chamadas neste fluxo.
    success = 1;
    
    print_test_result(test_name, success);
    return success;
}

int main() {
    printf("=== Huffman Coding Unit Tests ===\n");
    int all_tests_passed = 1;
    int result;

    result = test_basic_encoding_decoding();
    all_tests_passed &= result;

    result = test_file_operations();
    all_tests_passed &= result;

    result = test_single_char_string();
    all_tests_passed &= result;

    result = test_unique_chars_string();
    all_tests_passed &= result;

    result = test_empty_string();
    all_tests_passed &= result;

    printf("\n=== Test Summary ===\n");
    // Reimpressão individual para clareza, já que print_test_result está dentro de cada função.
    // Alternativamente, as funções de teste poderiam apenas retornar 0 ou 1 e main imprimiria.
    printf("Overall Result: %s\n", all_tests_passed ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    
    return all_tests_passed ? 0 : 1; // Retorna 0 para sucesso geral, 1 para falha
} 