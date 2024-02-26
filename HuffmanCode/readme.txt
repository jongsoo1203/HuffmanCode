Name: Jongsoo Ha

Discription: 
1. Make a huffman code that reads a text file and makes a huffman code. - finished
2. Create a Makefile to compile the program by calling ""make"".- finished
3. Check the information about GNU Mkae Utility by calling ""man make"".- finished

4. Upload the code on the server and check the result by calling ""make"". C - finished
5. Include getopt.h to implement the options.- finished
6. Include a debug switch -d to set "int debug = 1" to turn on printf statements. - finished


CODING:

7. Read input file and use 256 element array to count the frequency of each character. - finished
8. Use the frequency to create a build a huffman tree node for non-zero frequency characters.- finished



9. Sort by frequency and create a huffman tree. -finished
10. Combine two lowest(children) frequency nodes and create a new node with the sum of the two frequencies. -finished
11 Repeat step 10 until there is only one node left. -finished


12. Use debug to check if the total frequencies matches the size of input file.
    a) I can use -d at the end of the command to check the debug.
    b) command line would be "./huffmancode -i completeShakespeare.txt -o outcome -d"

13. Traverse the tree to create a huffman code for each character.
14. Read the input file again and put the bits in a buffer keeping track of how many and output
a bytye using fwrite when the buffer has eight bits.
    a) use fwrite to write the buffer to the output file.
    b) bits[32]
            As I go down the depth, I will read the bits in orderr. Each bit will have either 0 or 1.

    c) After getting the binary you want, you put it in codes[256]

            Collect code length[256] to understand when it was started or ended.
            Use noDupFre to test.

            It should have 4 bytes.

15. Save the rest for the next byte. 


It is all finished.



-------------------------------------------------------------------------------------------------------------
code discription:


huffmanEncode[][] - 2D array to store the huffman code of each character.
freq[] - Array to store the frequency of each character.
debug - A switch to turn on the debug mode.
size - The size of the file.

MAX_CHAR - 256
MAX_TREE_HT - 100


struct PriorityQueue
-size
-capacity
-array of HuffmanTreeNode

struct HuffmanTreeNode
- data
- freq
- left
- right

struct PriorityQueue* createPriorityQueue(int capacity)
- Create a priority queue.

void enqueue(struct PriorityQueue* priorityQueue, struct HuffmanTreeNode* node)
- enqueue the node.

struct HuffmanTreeNode* dequeue(struct PriorityQueue* priorityQueue)
- dequeue the node.
- Return the temp node that has the character and the frequency.




struct HuffmanTreeNode* newNode(char data, unsigned freq)
- Create a new temp node that has the character and the frequency.
- Return the temp node that has the character and the frequency.


struct HuffmanTreeNode* buildHuffmanTree(char data[], int freq[], int size)
- Creates a priority queue.
- For [0, size], enqueue the node. With the character and the frequency.
- While the size is not 1, dequeue the two nodes and create a new node with the sum of the two frequencies.
- Enqueue the new top node (The sum of the two frequency).
- Return the top node (The sum of the two frequency).


void printHuffmanCodes(struct HuffmanTreeNode* root, int arr[], int top)
- If the root has a left node, put 1 in the array and call printCodes.
- If the root has a right node, put 0 in the array and call printCodes.
- If the root has no left and right node, print the character and the array.
- print root->freq and arr[]. the array is the huffman code.


void GetFrequencyArrary(const char *filename, int freq[MAX_CHAR])
- Add the frequencies of characters in the file to the freq[] array.
- Increament the size of the file.


int SumofAllFrequencyLength(const int freq[MAX_CHAR])
- Return the sum of all the frequencies.


void WriteEncodedHuffmanFile(FILE *inputFile, FILE *outputFile)
- Read the input file again and put the bits in a buffer keeping track of how many and output
- a bytye using fwrite when the buffer has eight bits.
- use huffmanEncode to get the huffman code of the character.


void GetHuffmanCodes(struct HuffmanTreeNode* root, int arr[], int top)
- Traverse the tree to create a huffman code for each character.
- Stores the huffman code in the huffmanEncode[][] array.

int main(int argc, char *argv[])
- Use getopt to implement the options.
- Use -d to turn on the debug mode.
- Read the input file and use 256 element array to count the frequency of each character.
- Use the frequency to create a build a huffman tree node for non-zero frequency characters.



-------------------------------------------------------------------------------------------------------------


Problems:

1. MinHeap has so many functions to create. - I used the priority queue instead.
2. Priority queue is lost or I am lost. Maybe problem in dequeue. - I sketched how priority queue works and structed it.
3. The frequence order is not the same. Only the result is the same. - The way I was sorting was wrong
4. understanding why it did not output the compressed file. - the bit operation using buffer was able to find on online.
5. The bit operator for outputing a file is not working. - I looked at stackoverflow and found the answer.
6. The huffman code was not working. - I mixed up the order of th functions, and caused the errors.


References:
Andrew Tanenbaum and Herbert Bos, Modern Operating Systems, Fifth Edition
Class Slides 27 of huffman.
https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
https://www.geeksforgeeks.org/huffman-coding-using-priority-queue/
Priority Queues & Huffman Encoding by UW Homepage. University of Washington.
https://stackoverflow.com/questions/71392994/huffman-coding-using-min-priority-queue
https://codereview.stackexchange.com/questions/250438/priority-queue-implementation-on-c-for-huffman-coding
https://stackoverflow.com/questions/35241663/reliably-counting-bytes-written-by-fwrite-when-disk-is-full
https://stackoverflow.com/questions/61824864/huffman-code-encoder-write-to-output-file
https://people.engr.tamu.edu/djimenez/ut/utsa/cs1723/lecture14.html
``` /* using the codes in codes[], encode the file in infile, writing
 * the result on outfile
 */
void encode_file (FILE *infile, FILE *outfile, char *codes[]) {
	unsigned char ch;
	char	*s;

	/* initialize globals for bitout() */

	current_byte = 0;
	nbits = 0;
	nbytes = 0;

	/* continue until end of file */

	for (;;) {

		/* get a char */

		ch = fgetc (infile);
		if (feof (infile)) break;

		/* put the corresponding bitstring on outfile */

		for (s=codes[ch]; *s; s++) bitout (outfile, *s);
	}

	/* finish off the last byte */

	while (nbits) bitout (outfile, '0');
}
```
