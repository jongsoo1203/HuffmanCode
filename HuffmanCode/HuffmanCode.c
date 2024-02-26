#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

#define MAX_TREE_HT 100
#define MAX_CHAR 256 // Maximum number of characters (ASCII range)

int debug = 0; // Debug mode flag
int size = 0; // size of the frequency array
int freq[MAX_CHAR] = {0}; // Array to hold the frequency of each character
char huffmanEncoded[MAX_CHAR][MAX_TREE_HT];

#define MAX_TREE_HT 100

// Structure to represent a priority queue
struct PriorityQueue {
    int size; // Current size of the PriorityQueue
    int capacity; // Capacity of the PriorityQueue
    struct HuffmanTreeNode** array; // Array of Huffman Tree Nodes
};

// A Huffman tree node
struct HuffmanTreeNode {
    char data; // One of the input characters
    unsigned freq; // Frequency of the character
    struct HuffmanTreeNode *left, *right; // Left and right child of this node
};

// Got the idea from Geekforgeeks.
// The code was written in C++ and I converted it to C.
// Creating a new PriorityQueue structure
struct PriorityQueue* createPriorityQueue(int capacity) {
    // Allocate memory for the PriorityQueue
    struct PriorityQueue* priorityQueue = (struct PriorityQueue*) malloc(sizeof(struct PriorityQueue));
    // Initialize the size of the PriorityQueue to 0
    priorityQueue->size = 0; 
    // Set the capacity of the PriorityQueue
    priorityQueue->capacity = capacity;

    // Make the array of Huffman Tree Nodes of the PriorityQueue
    priorityQueue->array = (struct HuffmanTreeNode**) malloc(capacity * sizeof(struct HuffmanTreeNode*));
    return priorityQueue;
}


// Enqueue a new node to the PriorityQueue and keep it sorted
void enqueue(struct PriorityQueue* priorityQueue, struct HuffmanTreeNode* node) {
    // size of the pirorityQueue
    int i = priorityQueue->size - 1;

    // While the array has elements && the frequency of the new node is less than the frequency of the current node
    while (i >= 0 && node->freq < priorityQueue->array[i]->freq) {
        priorityQueue->array[i + 1] = priorityQueue->array[i];
        i--;
    }
    // Insert the new node at the correct position
    priorityQueue->array[i + 1] = node;
    // Increment the size of the PriorityQueue
    priorityQueue->size++;
}


// Function to remove and return the node of highest priority (lowest frequency)
struct HuffmanTreeNode* dequeue(struct PriorityQueue* priorityQueue) {
    // base case
    if (priorityQueue->size == 0) {
        return NULL;
    }

    // make a copy of the first node
    struct HuffmanTreeNode* temp = priorityQueue->array[0];
    // shift the array to the left
    for (int i = 1; i < priorityQueue->size; i++) {
        priorityQueue->array[i - 1] = priorityQueue->array[i];
    }
    // decrement the size of the PriorityQueue
    priorityQueue->size--;
    // return the first node
    return temp;
}

// create a new node
struct HuffmanTreeNode* newNode(char data, unsigned freq) {
    struct HuffmanTreeNode* temp = (struct HuffmanTreeNode*) malloc(sizeof(struct HuffmanTreeNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    // temp has data and frequency as a node
    return temp;
}

// Build the Huffman Tree and return the root of the tree
// The function takes an array of characters, an array of frequencies, and the size of the arrays
struct HuffmanTreeNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct HuffmanTreeNode *left, *right, *top;
    struct PriorityQueue* priorityQueue = createPriorityQueue(size);

    for (int i = 0; i < size; ++i) {
        enqueue(priorityQueue, newNode(data[i], freq[i]));
    }

    while (priorityQueue->size != 1) {
        left = dequeue(priorityQueue);
        right = dequeue(priorityQueue);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        enqueue(priorityQueue, top);
    }

    return dequeue(priorityQueue);
}
// Function to print the codes for each character
void printHuffmanCodes(struct HuffmanTreeNode* root, int arr[], int top) {
    // If the node is a leaf, print the character, frequency, and Huffman code
    // If the node is not a leaf, recurse down the tree
        if (root->left) {
            arr[top] = 1;
            printHuffmanCodes(root->left, arr, top + 1);
        }

        if (root->right) {
            arr[top] = 0;
            printHuffmanCodes(root->right, arr, top + 1);
        }
        
        if (!root->left && !root->right) {
        // Use a switch statement to handle different characters
        switch (root->data) {
            case ' ':
                printf("SPACE\t");
                break;
            case '\n':
                printf("LF\t"); // 'LF' for Line Feed
                break;
            case '\r':
                printf("CR\t"); // 'CR' for Carriage Return
                break;
            case '\t':
                printf("TAB\t"); // 'TAB' for Horizontal Tab
                break;
            default:
                if (isprint(root->data)) {
                    printf("%c\t", root->data);
                } else {
                    // Print non-printable characters as their ASCII value in decimal
                    printf("%d\t", (unsigned char)root->data);
                }
                break;
        }

        // Print the frequency
        printf("%d\t", root->freq);

        // Print the Huffman code
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}


// Read the frequency of each character from a file
void GetFrequencyArrary(const char *filename, int freq[MAX_CHAR]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int c; // Variable to hold character read from file

    // Initialize frequency array
    memset(freq, 0, sizeof(int) * MAX_CHAR);

    // Read characters from file and update the frequency array
    while ((c = fgetc(file)) != EOF) {
        if (c >= 0 && c < MAX_CHAR) {
            freq[c]++;
        }
    }
    // Close the file
    fclose(file);
    
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            size++;
        }
    } 
}

// Function definition
int SumofAllFrequencyLength(const int freq[MAX_CHAR]) {
    int frequency_length = 0;

    // Get the frequency length
    for (int i = 0; i < MAX_CHAR; i++) {
        frequency_length += freq[i];
    }

    // Return the calculated frequency length
    return frequency_length;
}

void printFrequency(const char *filename, int freq[MAX_CHAR]) {
    printf("%s length: ", filename);
    int freq_length = SumofAllFrequencyLength(freq);
    printf("%d\n", freq_length);

}

// Got the idea from StackoverFlow and other university.
void WriteEncodedHuffmanFile(FILE *inputFile, FILE *outputFile) {
    // Go back to the beginning of the file
    fseek(inputFile, 0, SEEK_SET);
    int character; 
    char buffer = 0;
    int bitCount = 0;


    // Read characters from the input
    while ((character = fgetc(inputFile)) != EOF) {
        // Get the Huffman code for the character
        char *code = huffmanEncoded[(unsigned char)character];

        // for each bit in the code
        for (int i = 0; code[i] != '\0'; i++) {
            // If the bit is 1, set the corresponding bit in the buffer to 1
            buffer = buffer << 1 | (code[i] - '0');
            bitCount++;
            
            // If the buffer is full
            if (bitCount == 8) {
                // Write the buffer to the output file
                fwrite(&buffer, 1, 1, outputFile);
                bitCount = 0;
                buffer = 0;
            }
        }
    }

    // Handle the last byte if it's not full
    if (bitCount > 0) {
        buffer = buffer << (8 - bitCount);
        fwrite(&buffer, 1, 1, outputFile);
    }
}

void GetHuffmanCodes(struct HuffmanTreeNode* root, int arr[], int top) {
    if (!root) return;

    // Traverse left
    if (root->left) {
        arr[top] = 1;
        GetHuffmanCodes(root->left, arr, top + 1);
    }

    // Traverse right
    if (root->right) {
        arr[top] = 0;
        GetHuffmanCodes(root->right, arr, top + 1);
    }

    // Store codes in huffmanEncoded when reaching a leaf node
    if (!root->left && !root->right) {
        // Convert the code from int[] to char[] and store it
        char encodedCode[MAX_TREE_HT + 1]; // +1 for the null terminator
        for (int i = 0; i < top; i++) {
            encodedCode[i] = '0' + arr[i]; // Convert int to char ('0' or '1')
        }
        encodedCode[top] = '\0'; // Null-terminate the string

        // Assume root->data is the character. Cast to unsigned char to handle potentially negative chars.
        strcpy(huffmanEncoded[(unsigned char)root->data], encodedCode);
    }
}
// Main function
int main(int argc, char *argv[]) {
    int opt;
    char *filename = "completeShakespeare.txt"; // Initialize filename as NULL
    char *outputFileName = "CompressedFile.out";

    // Process command-line options
    while ((opt = getopt(argc, argv, "d:i:o")) != -1) {
        switch (opt) {
            case 'd': // Debug mode
                debug = 1;
                break;
            case 'i': // Input file name
                filename = optarg;
                break;
            case 'o':
                outputFileName = optarg;
                break;    
            default: /* '?' */
                fprintf(stderr, "Usage: %s -i <filename> [-d]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!filename) {
        filename = "completeShakespeare.txt";
    }
    
    // read the frequency of each character from the file and store it in the freq array
    GetFrequencyArrary(filename, freq);

    // Allocate memory based on the updated size
    char *data = (char *)malloc(size * sizeof(char));
    int *f = (int *)malloc(size * sizeof(int));
    int j = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            data[j] = (char)i;
            f[j] = freq[i];
            j++;
        }
    }
    
    // first call buildHuffmanTree to get the root of the Huffman Tree
    struct HuffmanTreeNode* root = buildHuffmanTree(data, f, size);
    int arr[MAX_TREE_HT], top = 0;
    
    
    if (debug) {
        // call printHuffmanCodes to print the Huffman codes for each character
        // Print the frequencies
        printFrequency(filename, freq);
        printHuffmanCodes(root, arr, top);
    }


    // Clear the huffmanEncoded array
    memset(huffmanEncoded, 0, sizeof(huffmanEncoded));


    // It stores the huffman codes in huffmanEncoded[][] array
    GetHuffmanCodes(root, arr, top);

    FILE *inputFile = fopen(filename, "r");
    FILE *outputFile = fopen(outputFileName, "wb"); // Assuming binary write mode
    if (inputFile == NULL || outputFile == NULL) {
        // Handle file open error
    } else {
        WriteEncodedHuffmanFile(inputFile, outputFile);
        fclose(inputFile);
        fclose(outputFile);
    }

    free(data);
    free(f);
    

    // You should also free memory allocated within the HuffmanCodes and related functions

    return 0;
}

