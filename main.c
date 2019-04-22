/**
 * Data Structures and Algorithms
 * Assignment 2
 * Binary Search Tree
 *
 * Deadline: 23 April 2019 23.59
 *
 * A social media website holds user information on a binary search tree
 * Design the system which does given operations on the tree:
 *
 * 1. Each node holds user id, name-surname, an array of users friends ids,
 * left node address, right node address. In your design, each new node should
 * be allocated on a new memory address.
 *
 * 2. Write functions for given operations:
 *  a.  insertNewUser(): With a given ID, insert a new user without breaking
 *      tree structure.
 *  b.  deleteUser(): With a given ID, find user and delete it from the tree.
 *  c.  contains(): With a given ID, detect if the user in the tree or not.
 *      If user is in the tree, print name and surname information.
 *  d.  friends(): With a given ID, if the user exists, print users friends
 *      name and surname information.
 *  e.  size(): Print the element number.
 *  f.  printNext(): With a given ID, print name and surname
 *      information of all users in the subtree in ascending order with respect
 *      to their IDs.
 *  g.  printGreater(): With a given ID, print ID and name-surname information
 *      of all users whose IDs are greater then the given users.
 *  h.  printInOrder(): Print ID, name and surname information of all users in
 *      ascending order with respect to their IDs.
 * 3. In your main program, create a menu for calling all these functions. Until
 * user selects "exit", program should call the given function.
 *
 * Written and tested on Linux Mint 19 Cinnamon
 * Kernel 4.15.0-47-generic
 * gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0
 * GNU Make 4.1
 * Built for x86_64-pc-linux-gnu
 *
 * IDE:
 * CLion 2019.1.2
 * Build #CL-191.6707.69, built on April 18, 2019
 *
 * @author Mert Turkmenoglu
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

extern int errno;

#define True 1
#define False 0

#define MAX_NAME_SIZE 30
#define MAX_FRIEND_SIZE 50

#define MAX_PATH_SIZE 100
#define MAX_USER_INFO_SIZE 200

struct Node {
    int id;
    char *name;
    int friends[MAX_FRIEND_SIZE];
    int friendsCount;
    struct Node *left;
    struct Node *right;
};

typedef int Boolean;


void clearScreen(int osFlag);

void printMenu();

Boolean caseHandler(struct Node *root, int choice);

struct Node *createNewUser(int id, char *name, const int *friends, int friendsCount);

void printUserInfo(struct Node *user);

struct Node *search(struct Node *root, int id);

struct Node *parseString(char *str);

Boolean importUserFromFile(struct Node *root);

void friends(struct Node *root, int id);


int main() {
    /**
     * osFlag: Holds user operating system information for system commands
     * choice: Holds operation information
     * exitFlag: Holds true operation value about loops
     * root: Root element of the Binary Search tree
     */
    int osFlag;
    int choice;
    Boolean exitFlag = False;
    struct Node *root = NULL;

    printf("Welcome. For further operations, please state your Operating system:\n");
    printf("For Linux, press 1\n");
    printf("For Windows, press 2\n");

    /* Take operation system information from user */
    do {
        scanf("%d", &osFlag);
        if ((osFlag != 1) && (osFlag != 2))
            printf("You entered invalid number. Try again.\n");
        else
            exitFlag = True;
    } while (exitFlag != True);

    exitFlag = False;

    /**
     * Main loop. Depending on the input, it calls functions
     * or exits the loop
     */
    do {
        clearScreen(osFlag);
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if ((choice < 0) || (choice > 8)) {
            printf("You entered invalid number. Please check again\n");
        }
        if (choice == 0) {
            exitFlag = True;
        } else {
            Boolean isSuccess = caseHandler(root, choice);
            if (isSuccess == False) {
                exit(-1);
            }
        }
    } while (exitFlag != True);

    // Indicates successfull termination
    return 0;
}


/**
 * This function clears terminal screen
 * @param osFlag is operating system information
 */
void clearScreen(int osFlag) {
    if (osFlag == 1)
        system("clear");
    else
        system("cls");
}


/**
* caseHandler function handles input cases
* @param root is the root element of the binary search tree
* @param choice is the function number
*/
Boolean caseHandler(struct Node *root, int choice) {
    Boolean isSuccess = True;
    switch (choice) {
        case 1:
            printf("\nYou chose insertNewUser.\n");
            // TODO: insertNewUser call
            break;
        case 2:
            printf("\nYou chose deleteUser.\n");
            // TODO: deleteUser call
            break;
        case 3:
            printf("\nYou chose contains.\n");
            // TODO: contains call
            break;
        case 4:
            printf("\nYou chose friends.\n");
            // TODO: friends call
            break;
        case 5:
            printf("\nYou chose size.\n");
            // TODO: size call
            break;
        case 6:
            printf("\nYou chose printNext.\n");
            // TODO: printNext call
            break;
        case 7:
            printf("\nYou chose printGreater.\n");
            // TODO: printGreater call
            break;
        case 8:
            printf("\nYou chose printInOrder.\n");
            // TODO: printInOrder call
            break;
        default:
            // TODO: Improve error handling;
            printf("Error!");
            break;
    }
    return isSuccess;
}


/**
 * printMenu function prints function names
 * and numbers to terminal
 */
void printMenu() {
    printf("1. insertNewUser");
    printf("\n2. deleteUser");
    printf("\n3. contains");
    printf("\n4. friends");
    printf("\n5. size");
    printf("\n6. printNext");
    printf("\n7. printGreater");
    printf("\n8. printInOrder");
    printf("\n0. Exit");
    printf("\n---------------\n");
}


/**
 * Creates a new user with given params
 * @param id is the user id
 * @param name is user name
 * @param friends is the array of friend's ids
 * @param friendsCount is the total friend number
 * @return a new user instance
 */
struct Node *createNewUser(int id, char *name, const int *friends, int friendsCount) {
    struct Node *newUser;
    // Memory allocation for struct
    newUser = (struct Node *) malloc(sizeof(struct Node));

    // Value assignments
    newUser->id = id;
    strcpy(newUser->name, name);

    // Friend list assignment
    int i;
    for (i = 0; i < friendsCount; i++) {
        newUser->friends[i] = friends[i];
    }

    // Total friend count
    newUser->friendsCount = friendsCount;

    // A new node has no children
    // Left and right node pointers should be NULL
    newUser->left = NULL;
    newUser->right = NULL;

    // Return a pointer to new user
    return newUser;
}


/**
 * Print user information
 * @param user is the given user
 */
void printUserInfo(struct Node *user) {
    printf("**********\n");
    printf("ID:\t%d\n", user->id);
    printf("Name:\t%s\n", user->name);
    printf("Friend\'s ID\'s:\n");

    // Print user's friends' id's
    int i;
    for (i = 0; i < user->friendsCount; i++) {
        printf("%d\t", user->friends[i]);
    }

    printf("\n**********\n");
}


/**
 * Search the given user in the tree
 * @param id is the searched user's id
 * @param root is the root element of the tree
 */
struct Node *search(struct Node *root, int id) {
    // If root is null, return NULL
    if (root == NULL) {
        return NULL;
    }

    // If key is root's key, return root
    if (root->id == id) {
        return root;
    }

    // If id is greater than root's id
    // Look for the right sub-tree
    if (root->id < id)
        return search(root->right, id);

    // Id is less than root's id
    // Look for the left sub-tree
    return search(root->left, id);
}


/**
 * Parse the given string
 * @param str is the given string
 * @return a user with parsed information
 */
struct Node *parseString(char *str) {
    /**
     * temp string is for holding temporary information
     * after every loop, it will transform to other form
     * of information. (String to integer, string to string, etc.)
     * charToStr is a tool for reading a character
     * and appending to a string.
     */
    char temp[50];
    char charToStr[50];

    // Strings are empty at first place
    strcpy(temp, "");
    strcpy(charToStr, "");

    // Our character variable holds the first char of the string
    // i is the index variable
    char c = str[0];
    int i = 0;

    // Read id part
    while ((c != ',')) {
        sprintf(charToStr, "%c", str[i]);
        strcat(temp, charToStr);
        i++;
        c = str[i];
    }

    // Convert string to integer
    int id = atoi(temp);

    // Variable arranging before next part
    i++;
    c = str[i];
    strcpy(temp, "");
    strcpy(charToStr, "");

    // Read name part
    // Differently from id part, after name part
    // There is no obligation for friend's id part
    // There must be extra conditions for this state
    while ((c != ',') && (c != '\n') && (c != '\0')) {
        sprintf(charToStr, "%c", str[i]);
        strcat(temp, charToStr);
        i++;
        c = str[i];
    }

    // Copy temporary string to name
    char name[50];
    strcpy(name, temp);

    i++;
    c = str[i];
    strcpy(temp, "");
    strcpy(charToStr, "");
    int k = 0;
    int list[50];

    // Read friends part
    // Every id is seperated from the
    // previous one with a '-'
    // In loop, every else branch drops
    // means we got another id
    while ((c != '\n') && (c != '\0')) {
        if (isdigit(c)) {
            sprintf(charToStr, "%c", str[i]);
            strcat(temp, charToStr);
            i++;
            c = str[i];
        } else {
            // Add id to list
            list[k++] = atoi(temp);
            i++;
            c = str[i];
            strcpy(temp, "");
            strcpy(charToStr, "");
        }
    }

    // Return a new user with given information
    return createNewUser(id, name, list, k);
}


/**
 * Import user information from a file
 * @param root is the root element of the tree
 */
Boolean importUserFromFile(struct Node *root) {
    FILE *fptr;
    char filePath[MAX_PATH_SIZE];
    char tempStr[MAX_USER_INFO_SIZE];

    printf("Please enter file name: ");
    fscanf(stdin, "%s", filePath);

    // Open file in read mode
    fptr = fopen(filePath, "r");

    // Error handling
    if (fptr == NULL) {
        fprintf(stderr, "Error No: %d\n", errno);
        perror("Error: File not found\n");
        fprintf(stderr, "%s\n", strerror(errno));
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    // Read line by line and parse the string
    while (fgets(tempStr, MAX_USER_INFO_SIZE - 1, fptr) != NULL) {
        parseString(tempStr);
    }

    // Close file stream
    fclose(fptr);

    return True;
}


/**
 * Print a users friends
 * @param root is the root element of the tree
 * @param id is the users id to print friends
 */
void friends(struct Node *root, int id) {
    struct Node *user = search(root, id);
    int i;

    for (i = 0; i < user->friendsCount; i++) {
        printUserInfo(search(root, id));
    }
}