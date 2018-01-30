#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "first.h"

// Global Variables
struct TrieNode *root; //root node of each trie
bool isDict = false; //determines whether file is a dictionary or data file
int line = 0; //keeps track of line number in mapping file

/**
* Obtains name of dictionary and data files (line by line) from the mapping 
* file so that the files can be scanned/read for possible words/strings.
* 
* @param argc, argv Arguments (argc = # of arguments & argv = user inputted arguments)
*
* @return A return value of zero to terminate the program/main method.
*/
int main(int argc, char **argv) {

	if(argc != 2){ //no or too many args -> error
		printf("invalid input\n");
		return 0;
	}
	
	FILE *textfile = fopen(argv[1], "r");
	
	if(textfile == NULL || !(textfile)){ //mapping file is invalid -> error
		printf("invalid input\n");
		return 0;
	}
	
  char input[200]; //holds dictionary file name
  line = 1; //starting line of mapping file
  
	// Scanning textfile for dictionary and data file names
	while(fgets(input, 200, textfile)){
	
		// Dictionary File (obtains file name by utilizing tokenizer)
		char *dictName = strtok(input, " ");
		FILE *dictFile = fopen(dictName, "r");
		
		// Data File (obtains file name by utilizing tokenizer)
		char *dataName = strtok(NULL, "\n");
		FILE *dataFile = fopen(dataName, "r");
		
		if(dictFile == NULL || dataFile == NULL){ //invalid file(s) -> error
			printf("invalid input\n");
			return 0;
		} else {
			isDict = true; //reading dictionary file
			root = NULL; //null so that we can create root TrieNode later
			readDict(dictFile);
			fclose(dictFile);
			
			isDict = false; //reading data file
			readDict(dataFile);
			fclose(dataFile);
		}
		
		printResult(); //prints trie output for each line
	}
	
	fclose(textfile); //closes mapping file
	
	return 0;
}

/**
* Reads unique words from the file and either adds or 
* searches the word in the trie.
* 
* @param *dict_file Pointer to dictionary or data file
*/
void readDict(FILE *dict_file) {

	char word[200]; //character array to store letters (to build words)
	char letter;
	int i = 0;
	
	// Scan through dictionary or data file
	while( (letter = fgetc(dict_file)) != EOF){
		if(isalpha(letter) != 0){ //is a letter -> add to word array
			letter = tolower(letter);
			word[i] = letter;
			i++;
		} else if(isalpha(letter) == 0 && i > 0){ //is NOT a letter -> marks end of current word
				word[i] = '\0'; //string terminator
				i = 0; //reset starting index
				matchStr(word); //adds or searches word in trie (depends on value of 'isData' global variable)
		} else {
			continue;
		}
	}
	
}

/**
* Does one of the following :
* 
* Dictionary File (isDict is 'true'): stores given word in a trie
* Data File (isDict is 'false'): searches for given word in the trie and if found, updates its count/occurrences
* 
* @param str Word/string
*/
void matchStr(char* str) {

	// No root TrieNode
	if(root == NULL){
		if(isDict == true){ //creates new node and makes it the root
			struct TrieNode *n = malloc(sizeof(TrieNode));
			assignNodeValues(n, 'a'); //assigns default values to new node ('a' = temp value -> will be replaced)
			root = n;
		} else { //empty trie so no match
			return;
		}
	}

	struct TrieNode *ptr = root; //pointer to root of trie
	int wordLength = strlen(str); //length of word/string
	int WL2 = (wordLength - 1);
	int index = 0;
	int position;
	char letter;

	// Iterate through given word/string
	while(index < wordLength){
	
		letter = str[index]; //letter at index
		position = (letter - 'a'); //letter's index in node's children array (e.g. 0=a, 1=b, 2=c, etc.)

		// Letter doesn't exist
		if(ptr->child[position] == NULL){
			if(isDict == true){ //create node at position
				struct TrieNode *n = malloc(sizeof(TrieNode));
				assignNodeValues(n, letter); //assigns default values to new node
				ptr->child[position] = n;
			} else { //letter/word doesn't exist so no match
				return;
			}
		}
		
		ptr = ptr->child[position]; //iterate
		
		if(isDict == false && index < WL2){
			ptr->superwords++; //increment superword count
		} else if((index + 1) == wordLength){ //is last letter of the word
			updateField(ptr, isDict, str, wordLength); //either updates pointer's occurrence or string field
		} else {
			//does nothing
		}
		
		index++;
	}
	
}

/**
* Assigns default values to newly created TrieNodes.
* 
* @param node, letter Newly created TrieNode and its letter
*/
void assignNodeValues(struct TrieNode *n, char letter) {

	n->occurrence = 0;
	n->superwords = 0;
	n->isLeaf = false;
	n->letter = letter;
	n->string = NULL;
	n = markNull(n); //sets all 26 children to null
	
}

/**
* Sets all of TrieNode's children to NULL.
* 
* @param n Newly created TrieNode
* 
* @return n Same TrieNode with all its children set to null.
*/
struct TrieNode *markNull(struct TrieNode *n) {

	int i = 0;
	
	while(i < 26){
		n->child[i] = NULL;
		i++;
	}
	
	return n;
}

/**
* Dict File : Copies given string to an allocated character array, sets pointer's string field 
* to the copied string, and marks the current TrieNode as a leaf node.
* 
* Data File : Word/string was found in Trie, so increment the pointer's/leaf node's occurrence  field
* 
* @param ptr, str, isDict, wordLength
*/
void updateField(struct TrieNode *ptr, bool isDict, char* str, int wordLength) {

	if(isDict == true){ //dict file -> store string in leaf node
	
		char* str2 = (char*)(malloc(sizeof(char) * (wordLength + 1))); //allocate characters for the string
		int i = 0;
		
		while(i < wordLength){
			str2[i] = str[i]; //copy string/word from 'str' to 'str2'
			i++;
			if(i == wordLength){ str2[i] = '\0'; } //string terminator marks end of the word
		}
	
		ptr->string = str2; //stores the current string/word in the current leaf node
		ptr->isLeaf = true; //marks leaf nodes b/c they store the full words
		
	} else { //data file
		ptr->occurrence++; //word found so increment word's occurrence
	}

}

/**
* Calls printAndFree to traverse through the trie and 
* print the trie output in the desired format.
*/
void printResult() {

	char name[24]; //holds name of current output file (outi.txt, where i is the line number)
	sprintf(name, "out%d.txt", line++);
	
	FILE *output = fopen(name, "w"); //opens current output file in write mode
	printAndFree(root, output); //recursively traverses through trie, prints output, and then frees each node and the stored strings
	
	fclose(output); //closes output file
	
}

/**
* Assists printResult() by recursively traversing through the trie until reaching a 
* leaf node, where it prints out all the leaf node's information (current word, 
* word's occurrence, and word's prefix/superwords count). Also frees each node
* and the allocated strings of the leaf nodes after printing the output.
*
* param: root, output
*/
void printAndFree(struct TrieNode *root, FILE *output) {

	if(root == NULL || !(root)){ //empty
		return;
	} else if(root->isLeaf == true){ //is a leaf node
	
		// Prints output in the format: <wordi><space><counti1><space><counti2><new line> (where i = line number) 
		fprintf(output, "%s %d %d\n", root->string, root->occurrence, root->superwords);
		free(root->string); //frees the stored allocated string
	} else {
		//does nothing
	}
	
	// Recursively traverses the trie's children in alphabetical order (from A to Z)
	int index;
	for(index = 0; index < 26; index++){
		if(root->child[index] != NULL){
			printAndFree(root->child[index], output); //recursion
		}
	}
	
	free(root); //frees node
}
