#ifndef _first_h
#define _first_h

/*
* More information, such as method and line descriptions, can be found 
* in the main C file ('first.c') and the readme file ('readme.pdf').
*/

// 'TrieNode' structure
typedef struct TrieNode {

	int occurrence; //number of times a given word in the data file appears in the dictionary file
	int superwords; //keeps count how many times a given/specific dictionary file word is a prefix of a data file word
	bool isLeaf; //keeps track of whether or not a TrieNode is a leaf node (a node with no children)
	char letter; //stores the TrieNode's alphabetical letter
	char* string; //stores the full words/strings that are added to the Trie into the leaf nodes (last node of the word)
	struct TrieNode *child[26]; //stores other TrieNodes to form a word (the indeces correspond to the 26 alphabetical letters)
	
} TrieNode;

void readDict(FILE *dict_file); //reads unique words from the file and either adds (if dict file) or searches (if data file) the word in the trie

void matchStr(char* str); //Does one of the following:
													// if Dict File: stores the given string in the trie
													// if Data File: searches for given string in the trie and if found, updates its count/occurrences

void assignNodeValues(struct TrieNode *n, char letter); //assigns default values to newly created TrieNodes

struct TrieNode *markNull(struct TrieNode *n); //sets all of TrieNode's children to null

void updateField(struct TrieNode *ptr, bool isDict, char* str, int wordLength); //Does one of the following:
																																								// if Dict File: Copies given string to an allocated character array,
																																								//							 sets pointer's string field to the copied string, 
																																								//							 and marks the current TrieNode as a leaf node.
																																								// if Data File: Word/string was found in Trie, so increment the 
																																								//							 pointer's/leaf node's occurrence  field

void printResult(); //creates and opens an output file in write mode so that the printAndFree method can print the output in it

void printAndFree(struct TrieNode *root, FILE *output); //recursively traverses through the trie until reaching a leaf node, where it prints 
																											  //out all of the leaf node's information. Also frees each node and the allocated strings of 
																											  //the leaf nodes after printing the output.

#endif
