#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

//node of our tree
struct node {
	char letter;
	struct node* left;
	struct node* right;
};

//allocates a new node with given letter
//right and left pointers are NULL
struct node* createNode(char character)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->letter = character;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void DeleteTree(struct node* root)
{
	if (root == NULL)
	{
		return;
	}
	DeleteTree(root->left);
	DeleteTree(root->right);
	free(root);
}

//build the tree needed to do morse to english conversion
//see project description
void buildMorseTree(struct node* root)
{
	struct node* OGRoot = root;

	char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	char morse[26][5] = {
	{ '0', '1', '\0', '\0', '\0' },      // A
	{ '1', '0', '0', '0', '\0' },        // B
	{ '1', '0', '1', '0', '\0' },        // C
	{ '1', '0', '0', '\0', '\0' },       // D
	{ '0', '\0', '\0', '\0', '\0' },     // E
	{ '0', '0', '1', '0', '\0' },        // F
	{ '1', '1', '0', '\0', '\0' },       // G
	{ '0', '0', '0', '0', '\0' },        // H
	{ '0', '0', '\0', '\0', '\0' },      // I
	{ '0', '1', '1', '1', '\0' },        // J
	{ '1', '0', '1', '\0', '\0' },       // K
	{ '0', '1', '0', '0', '\0' },        // L
	{ '1', '1', '\0', '\0', '\0' },      // M
	{ '1', '0', '\0', '\0', '\0' },      // N
	{ '1', '1', '1', '\0', '\0' },       // O
	{ '0', '1', '1', '0', '\0' },        // P
	{ '1', '1', '0', '1', '\0' },        // Q
	{ '0', '1', '0', '\0', '\0' },       // R
	{ '0', '0', '0', '\0', '\0' },       // S
	{ '1', '\0', '\0', '\0', '\0' },     // T
	{ '0', '0', '1', '\0', '\0' },       // U
	{ '0', '0', '0', '1', '\0' },        // V
	{ '0', '1', '1', '\0', '\0' },       // W
	{ '1', '0', '0', '1', '\0' },        // X
	{ '1', '0', '1', '1', '\0' },         // Y
	{ '1', '1', '0', '0', '\0' },         // Z
	};

	for (int i = 0; i < 26; i++)
	{
		root = OGRoot;
		char temp = '1';
		char letter = alphabet[i];

		char code[5];
		strcpy(code, morse[i]); // Copy the first row to start the string	

		int length = strlen(code);
		for (int j = 0; j < length; j++)
		{
			if (code[j] == '0')
			{
				if (root->left == NULL)
				{
					root->left = createNode(temp);
					root = root->left;
				}
				else
				{
					root = root->left;
				}
			}
			else if (code[j] == '1')
			{
				if (root->right == NULL)
				{
					root->right = createNode(temp);
					root = root->right;
				}
				else
				{
					root = root->right;
				}
			}

			if (j == length - 1)
			{

				root->letter = letter;
			}
		}

	}
}



//prints the Morse Tree in preorder
void printMorseTree(struct node* node)
{
	if (node == NULL)
	{
		return;
	}
	printf("%c", node->letter);
	printMorseTree(node->left);
	printMorseTree(node->right);
}

//converts all the characters(dot, dash, space, slash) pointed to 
//by characters and converts to english characters and places the 
//english conversions in output.
//This function will create the root by calling createNode.
//The data of the root node can be a character 0
//and will build the tree by calling buildTree(root)
//After building the tree, call printMorseTree to show it was built correctly
void convertMorseToEnglish(char* characters, char* output)
{
	char letter = ' ';
	char* space = " ";

	// Create root node and build the Morse code tree
	struct node* root = createNode('0');
	buildMorseTree(root);

	int len = strlen(characters);
	int i = 0;
	int j = 0;

	struct node* temp = root;

	while (i < len)
	{
		if (characters[i] == '.')
		{
			temp = temp->left;
			
			if (temp == NULL)
			{
				printf("Error: Invalid Morse code");
				return;
			}
		}
		else if (characters[i] == '-')
		{
			temp = temp->right;

			if(temp == NULL)
			{
				printf("Error: Invalid Morse code");
				return;
			}
		}
		else if (characters[i] == ' ')
		{
			if (temp->letter != root->letter)
			{
				char let[2];
				let[0] = temp->letter;
				let[1] = '\0';

				strcat(output, let);

				// start from beginning of tree 
				temp = root;
			}

		}
		else if (characters[i] == '/')
		{
			// add a space character to output var

			strcat(output, space);
			// start from beginning of tree 
			temp = root;
		}

		i++;
	}

	if (temp->letter != root->letter)
	{
		char let[2];
		let[0] = temp->letter;
		let[1] = '\0';

		strcat(output, let);

		// start from beginning of tree 
		temp = root;
	}

	int length = strlen(output);
	output[length] = '\0'; // Add null terminator to end of output string

	DeleteTree(root);
}

// int main(int argc, char** argv)
// {
// 	//create and initialize arrays message and output
// 	char message[200] = ".- / --. --- --- -.. / --- ..-. ..-. .. -.-. . .-. / -.-. --- -- -- .- -. -.. ... / .-- .. - .... --- ..- - / -.. --- ..- -... -";
// 	char message1[200] = ".- / --. --- --- -.. / ... --- .-.. -.. .. . .-. / --- -... . -.-- ... / .-- .. - .... --- ..- - / --.- ..- . ... - .. --- -.";
						  
// 	char output[100] = { '\0' };

		
	
// 	int length = strlen(message);
// 		message[length] = ' ';
// 		message[length + 1] = '\0';
// 		convertMorseToEnglish(message, output);
// 		printf("%s", output);
// 		printf("\nImbetween..\n");
// 		// reset output
		
// 		for (int i = 0; i < 100; i++)
// 		{
// 			output[i] = '\0';
// 		}
		
// 		convertMorseToEnglish(message1, output);
// 		printf("%s", output);
// }

int main(int argc, char** argv)
{
	//create and initialize arrays message and output
	char message[200] = { '0' };
	char output[100] = { '\0' };
	//the input file is the second argument when executing the program
	FILE* datafile = fopen(argv[1], "r");/* open file for reading*/
	if (datafile == NULL) { printf("can't open\n"); }
	else
	{
		fgets(message, 199, datafile);
		int length = strlen(message);
		message[length] = ' ';
		message[length + 1] = '\0';
		convertMorseToEnglish(message, output);
		printf("%s", output);
	}
}

// run command
// gcc -o convert main.c
// convert test.txt