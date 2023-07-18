//Jose Hichez
//PID 6186740
//"I affirm that I wrote this program myself without any help from any other people or sources from the internet."

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node_struct { // creates a struct to hold the variables
    char* words; // creates a character pointer
    struct node_struct* left; // sets node on the left side
    struct node_struct* right; // sets node on the right side
} Node;

struct node_struct* createNode(char* word);   //prototyping the function that creates Node

struct node_struct* insert(Node* root, char* words, bool caseSensitive); // prototyping function that inserts node

char toLowerCase(char letter); //prototyping lower case converter function

int compareStrings(char* string1, char* string2, bool isCaseSensitive); // prototyping compare strings unction

void deleteNode(Node** node); //prototyping function to delete node

struct node_struct* createNode(char* word) { // creates function to create a node, takes in a char var
    Node* node = (Node*)malloc(sizeof(Node)); // creates pointer to a node and assigns memory to it
    node->words = (char*)malloc(strlen(word) + 1); // allocates memory assigns the point to node
    strcpy(node->words, word); // returns pointer to the destination string
    node->left = NULL; // assigns the left node to a node
    node->right = NULL;//assigns right node to a node
    return node; //returns the node
}

struct node_struct* insert(Node* root, char* words, bool caseSensitive) { // creates a function to insert node, takes in node, char and a bool, returns int
    if (root == NULL) { // checks if root is null
        root = createNode(words); //creates a node with the word in it
    }
    else {
        int comparison = compareStrings(root->words, words, caseSensitive); // creates variable and assigns the result of comparing two strings  case sensitive
        if (comparison > 0) { // checks if the comparison return is 0
            root->right = insert(root->right, words, caseSensitive); // assigns value to the right node
        }
        else if (comparison < 0) { //checks if comparison
            root->left = insert(root->left, words, caseSensitive); // assigns the value t the left node
        }
    }

    return root; //returns the root
}

void inOrder(FILE* outFile, Node* node) { // starts function to print the node out takes a Node and a file
    if (node != NULL) { //if node is not null
        inOrder(outFile, node->left); // recursive call makes the node go all the way to the left
        fprintf(outFile, "%s\n", node->words); // Prints node to stdOut or to output file.
        inOrder(outFile, node->right); // recursive call makes the node go all the way to the right
    }
}

void deleteNode(Node** node) { //deletes node takes a node
    if (*node != NULL) { // if node is not null
        deleteNode(&(*node)->left); //  recursive call makes the node go all the way to the left and deletes it
        deleteNode(&(*node)->right); // recursive call makes the node go all the way to the right and deletes it
        free((*node)->words); // deletes content on the node
        free((*node)); //delete content from node
    }
}

int compareStringCaseSensitive(char* string1, char* string2) { //creates a function to compare strings case sensitive
    int isEqual; // function to hold if is equal in 3 values 1, -1 or 0
    int flag = 0; //flag to end one of the loops

    if (string1 == NULL && string2 == NULL) { // checks if null to end to return 0 and end
        return 0; //returns 0 to end
    }

    while ((*string1 != '\0' || *string2 != '\0') && (flag <= 0)) { // starts loop to compare
        if (*string1 == *string2) { // checks if strings are equal
            isEqual = 0; // if they are euqal assigns 0 to the varavle
        }
        else if (*string1 > *string2) { //if strings are not equal and string 1 is bigger and
            isEqual = 1; //if is bigger assigns 1 to is equal
            flag = 1;  //assigns 1 to the flag to end the loo[
        }
        else if (*string1 < *string2) { // checks if the string is smaller that the other one
            isEqual = -1; //returns -1 if is smaller
            flag = 1; // assigns 1 to flag
        }
        else { //if they are not equal then
            isEqual = -1; //is equal returns -1
            flag = 1; // returns flag 1
        }
        string1++; //increases string to continue looping
        string2++; //increases string 2 to continue looping
    }
    return isEqual; //returns is equal
}

int compareStringCaseInsensitive(char* string1, char* string2) { //creates case sensitive string comparison function, takes two strings
    int isEqual; // creates int var to check if is equal 1 if true, -1 if false and 0 if equal
    int flag = 0; // creates flag

    if (string1 == NULL && string2 == NULL) { // check if the strings are null to return initially
        return 0; // returns 0
    }

    while ((*string1 != '\0' || *string2 != '\0') && (flag <= 0)) { //starts comparison loop
        if (toLowerCase(*string1) == toLowerCase(*string2)) { // takes the strings to lower cases and  checks if they are equal
            isEqual = 0; //assigns is equal 0
        }
        else if (toLowerCase(*string1) > toLowerCase(*string2)) { //takes the strings to lower cases and
            isEqual = 1; // asssigns -1 when string 1 is grate
            flag = 1; //flag returns 1 to end loop
        }
        else if (toLowerCase(*string1) < toLowerCase(*string2)) { //takes the strings to lower cases and
            isEqual = -1; //assigns -1 when one is 2nd string is less
            flag = 1; //flag returns 1 to end loop
        }
        else {
            isEqual = -1; //is equal takes -1 when they are not equal
            flag = 1; //flag returns 1 to end loop
        }

        string1++; //increases the current char place to continue loop
        string2++; //increases the char on the second string to continue loop
    }
    return isEqual; //returns 1, -1 or 0 after logic was executed
}

int compareStrings(char* string1, char* string2, bool isCaseSensitive) { //creates method to compare strings receives a string and a bool returns an int
    if (isCaseSensitive) { // Checks if Case sensitive is true or false
        return compareStringCaseSensitive(string1, string2); //  if true returns the string case sensitive function
    }
    else {
        return compareStringCaseInsensitive(string1, string2); // if false uses string comparison non case sensitive function
    }
}

char toLowerCase(char letter) // A utility function which will be used to convert provided letter to lower case.
{
    char lowerCaseLetter; // Creates lowerCaseLetter variable.
    if (letter >= 65 && letter <= 90) // Checks if character is between capital letters A - Z
    {
        lowerCaseLetter = letter + 32; // Adds 32 to the capital letter to make the character lower case.
    }
    else {
        lowerCaseLetter = letter; // If parameter was already lower case then it will just assign it to be returned.
    }
    return lowerCaseLetter; // Returns to lower case.
}

int main(int argc, char* argv[]) { //beginning of main method and gets argument parameters
    int opt; //create in opt
    bool isCaseSensitive = false; // creates and initializes if is case sensitive
    char* fOutput = NULL; // creates pointer for output

    while ((opt = getopt(argc, argv, "co:")) != -1) { // starts loop to take the arguments
        switch (opt) { //logic to handle the flags
        case 'c': //if flag is c
            isCaseSensitive = true; //assigns case sensitive bool true
            break;  //breaks out of the switch
        case 'o': // if flag is o
            fOutput = optarg; // gets the out put string from command line
            break; //breaks out of the switch
        default:
            printf("Wrong argument parameters provided."); // handles the default message
        }
    }
    Node* node = NULL; //creates node null
    char string[1024]; // assigns memory to the char

    char* fInput = argv[argc - 1]; // gets the last from the program argument and assigns to file input string
    FILE* fileIn = NULL; // will be used for file input

    if (fInput != NULL && (compareStringCaseInsensitive(fInput, "bstsort") != 0)) { // checks if file input string is empty or is "bstsort"
        fileIn = fopen(fInput, "r"); // Opens file input at read level
        if (fileIn == NULL) { // checks if file input is null
            printf("Failed to open file input."); // alerts the user that something was wrong opening the file.
            return -1; // returns -1 if file fails to open
        }
    }
    else {
        printf("Type the words separated by space.\n"); // tells the user to input words separated by a space
        fgets(string, 1024, stdin); //creates fgets functions
        char delim[] = " "; // set delimiter to space
        char* strP = strtok(string, delim); // Breaks strings into token by the delimiter

        while (strP != NULL) { // iterates through string tokens
            if (strP[strlen(strP) - 1] == '\n') // checks if the last word has a new line in the string token
            {
                strP[strlen(strP) - 1] = '\0'; // Put an end of string if true
            }
            node = insert(node, strP, isCaseSensitive); // insert string tokens into node
            strP = strtok(NULL, delim); // get the next token separated by delimiter
        }
    }

    if (fileIn != NULL) // checks if file input is null
    {
        while (fgets(string, 1024, fileIn) != NULL) { // reads a line in the file and store into string
            if (string[strlen(string) - 1] != '\0') { // Checks the ending of the string isn't the end of strings
                string[strlen(string) - 1] = '\0'; // replace the new line with last of string
            }
            node = insert(node, string, isCaseSensitive); // insert string from file into the node
        }
        fclose(fileIn); // Close the input file once done
    }

    FILE* fileOut; // Create fileout variable
    if (fOutput != NULL) { // checks if file out is not null
        fileOut = fopen(fOutput, "w"); // open fie output and assign to fieOut variable.
    }
    else {
        fileOut = stdout; // Assigns fileout to stdout if file output is null
    }

    if (fileOut == NULL) { // checks if file out is null
        printf("Error in opening output File."); // if it is null print error message
        return -1; // return error code -1
    }

    printf("Printing words or storing them to output file.\n"); // print message that the words or bing stored in the file or to stdout.
    inOrder(fileOut, node); // calls inOrder which will print node in order to stdOut or to output file
    fclose(fileOut); // closes file
    deleteNode(&node); // deletes the node and free resources

    return 0;
}
