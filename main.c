/**
 * Data Structures and Algorithms
 * Assignment 2
 * Binary Search Tree
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
#include <unistd.h>

extern int errno;

#define True 1
#define False 0

#define MAX_NAME_LENGTH 50
#define MAX_FRIEND_SIZE 50

#define MAX_PATH_SIZE 100
#define MAX_USER_INFO_SIZE 200

struct Node {
    int id;
    char name[MAX_NAME_LENGTH];
    int friends[MAX_FRIEND_SIZE];
    int friendsCount;
    struct Node *left;
    struct Node *right;
};

typedef int Boolean;

void printMenu();

struct Node *caseHandler(struct Node *root, int choice);

struct Node *createNewUser(int id, char *name, const int *friends, int friendsCount);

void printUserInfo(struct Node *user);

struct Node *search(struct Node *root, int id);

struct Node *parseString(char *str);

struct Node *importFromFile(struct Node *root);

void friends(struct Node *root, int id);

Boolean manualInput(struct Node *root);

int size(struct Node *root);

Boolean deleteUserHandler(struct Node *root);

struct Node *deleteUser(struct Node *root, int id);

struct Node *findMinimumValueNode(struct Node *root);

Boolean containsHandler(struct Node *root);

Boolean friendsHandler(struct Node *root);

Boolean printNextHandler(struct Node *root);

Boolean printGreaterHandler(struct Node *root);

struct Node *insertToTree(struct Node *root, struct Node *user);

void printInOrder(struct Node *root);

void printGreater(struct Node *root, int id);

int main() {
    /**
     * choice: Holds operation information
     * exitFlag: Holds true operation value about loops
     * root: Root element of the Binary Search tree
     */

    int choice;
    Boolean exitFlag = False;
    struct Node *root = NULL;

    /**
     * Main loop. Depending on the input, it calls functions
     * or exits the loop
     */
    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if ((choice < 0) || (choice > 10)) {
            printf("You entered invalid number. Please check again\n");
        }
        if (choice == 0) {
            exitFlag = True;
        } else {
            root = caseHandler(root, choice);
        }
    } while (exitFlag != True);

    // Indicates successfull termination
    return 0;
}


/**
* caseHandler function handles input cases
* @param root is the root element of the binary search tree
* @param choice is the function number
*/
struct Node *caseHandler(struct Node *root, int choice) {
    switch (choice) {
        case 1:
            printf("\nYou chose manualInput\n");
            manualInput(root);
            break;
        case 2:
            printf("\nYou chose importFromFile.\n");
            root = importFromFile(root);
            break;
        case 3:
            printf("\nYou chose deleteUser.\n");
            deleteUserHandler(root);
            break;
        case 4:
            printf("\nYou chose contains.\n");
            containsHandler(root);
            break;
        case 5:
            printf("\nYou chose friends.\n");
            friendsHandler(root);
            break;
        case 6:
            printf("\nYou chose size.\n");
            printf("%d\n", size(root));
            break;
        case 7:
            printf("\nYou chose printNext.\n");
            printNextHandler(root);
            break;
        case 8:
            printf("\nYou chose printGreater.\n");
            printGreaterHandler(root);
            break;
        case 9:
            printf("\nYou chose printInOrder.\n");
            printInOrder(root);
            break;
        default:
            // TODO: Improve error handling;
            printf("Error!");
            break;
    }
    return root;
}


/**
 * printMenu function prints function names
 * and numbers to terminal
 */
void printMenu() {
    printf("\n1. Add a new user to tree manually(manualInput)");
    printf("\n2. Add users from a file(importFromFile)");
    printf("\n3. Delete a user from tree(deleteUser)");
    printf("\n4. Search for a user(contains)");
    printf("\n5. Print friends of a user(friends)");
    printf("\n6. Print user count(size)");
    printf("\n7. printNext");
    printf("\n8. printGreater");
    printf("\n9. printInOrder");
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
struct Node *createNewUser(int id, char name[MAX_NAME_LENGTH], const int *friends, int friendsCount) {
    struct Node *user;
    // Memory allocation for struct
    user = malloc(sizeof(struct Node));

    // Value assignments
    user->id = id;
    strcpy(user->name, name);

    // Friend list assignment
    int i;
    for (i = 0; i < friendsCount; i++) {
        user->friends[i] = friends[i];
    }

    // Total friend count
    user->friendsCount = friendsCount;

    // A new node has no children
    // Left and right node pointers should be NULL
    user->left = NULL;
    user->right = NULL;

    // Return a pointer to new user
    return user;
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

    list[k++] = atoi(temp);

    // Return a new user with given information
    return createNewUser(id, name, list, k);
}


/**
 * Import user information from a file
 * @param root is the root element of the tree
 */
struct Node *importFromFile(struct Node *root) {
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
    int userCounter = 0;
    // Read line by line and parse the string
    while (fgets(tempStr, MAX_USER_INFO_SIZE - 1, fptr) != NULL) {
        struct Node *tmp = parseString(tempStr);
        if (search(root, tmp->id) == NULL) {
            struct Node *tempNode = insertToTree(root, tmp);
                root = tempNode;
            userCounter++;
            if(userCounter % 10 == 0) {
                printInOrder(root);
            }
        }
    }

    // Close file stream
    fclose(fptr);

    return root;
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
        printUserInfo(search(root, user->friends[i]));
    }
}


/**
 * Insert a given user to the tree without breaking structure
 * @param root is the root element of the tree
 * @param user is the new user to add the tree
 * @return a pointer to node
 */
struct Node *insertToTree(struct Node *root, struct Node *user) {
    // If the root is empty, root is now the user
    if (root == NULL)
        root = user;

    // If root is not empty
    // Search for right and left branches
    // Find an appropriate terminal for user

    // Look for left branch
    if (user->id < root->id) {
        root->left = insertToTree(root->left, user);
    } else if (user->id > root->id) {
        // Look for right branch
        root->right = insertToTree(root->right, user);
    }

    // Return a pointer to node
    return root;
}


/**
 * Insert a new user to tree manually
 * @param root is the root element of the tree
 * @return successful status
 */
Boolean manualInput(struct Node *root) {
    int i;
    int id;
    char name[MAX_NAME_LENGTH];
    int friendsCount;
    int list[MAX_FRIEND_SIZE];

    printf("\nPlease enter user id: \n");
    scanf("%d", &id);

    if (search(root, id) == NULL) {
        printf("\nPlease enter user name: \n");
        scanf("%s", name);

        printf("\nPlease enter users friend count: ");
        scanf("%d", &friendsCount);

        for (i = 0; i < friendsCount; i++) {
            printf("\nPlease enter friend id: ");
            scanf("%d", &list[i]);
        }
        struct Node *tmpNode = insertToTree(root, createNewUser(id, name, list, friendsCount));
        if (root == NULL)
            root = tmpNode;
        return True;
    } else {
        printf("\nUser is already in the tree");
        return False;
    }
}


/**
 * Calculates element number of a given tree recursively
 * If root of the given(instance) tree is NULL, it is either empty
 * or it is a terminal node.
 * Otherwise iterate over left and right branches of the node
 * Size of a tree = Right hand-side tree element count +
 * Left hand-side tree element count + Root itself
 * size = rhs + lhs + 1
 * @param root is the root element of the given tree
 * @return element number of the tree
 */
int size(struct Node *root) {
    return (root == NULL) ? 0 : (size(root->right) + size(root->left) + 1);
}


/**
 * This function handles user delete operations
 * @param root is the root of the tree
 * @return successful status
 */
Boolean deleteUserHandler(struct Node *root) {
    int id;
    printf("\nPlease enter user id: ");
    scanf("%d", &id);

    if (search(root, id) != NULL) {
        root = deleteUser(root, id);
        return True;
    } else {
        return False;
    }
}


/**
 * This function deletes a user from a tree
 * It assumes that user is in the tree
 * @param root is the root element of the tree
 * @param id is the user's id
 * @return successful status
 */
struct Node *deleteUser(struct Node *root, int id) {
    /*
     * If the root of the tree is NULL
     * then tree is empty.
     */
    if (root == NULL)
        return root;

    /*
     * If given id is less than currently looked node's id
     * user is in the left hand-side sub-tree of this node
     *
     * If given id is greater than currently looked node's id
     * user is in the right hand-side sub-tree of this node
     *
     * If id is equal to this node's id, it is the searched user.
     * Search for the node is completed. It should be deleted.
     *
     *
     */
    if (id < root->id) {
        root->left = deleteUser(root->left, id);
    } else if (id > root->id) {
        root->right = deleteUser(root->right, id);
    } else {
        /*
         * If the root has one (left or right)
         * swap the other child node with the parent
         * then free the memory for the old parent node
         */
        if (root->left == NULL) {
            struct Node *tempNode = root->right;
            free(root);
            return tempNode;
        } else if (root->right == NULL) {
            struct Node *tempNode = root->left;
            free(root);
            return tempNode;
        }

        /*
         * If node has two children, node with the smallest id on the
         * right hand-side sub-tree should be moved to this node
         */
        struct Node *tempNode = findMinimumValueNode(root->right);
        root->id = tempNode->id;

        /*
         * Then the moved node should be deleted.
         * Call the function again recursively
         */
        root->right = deleteUser(root->right, tempNode->id);
    }
    return root;
}


/**
 * This function finds the node which has the minimum id value
 * @param root is the root element of the tree
 * @return node which has the minimum id
 */
struct Node *findMinimumValueNode(struct Node *root) {
    struct Node *currentNode = root;

    /*
     * While currently looked node has a left hand-side child node
     * go to that node and look again.
     */
    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    /*
     * Finally, return the most left hand-side child node
     */
    return currentNode;
}


/**
 * This function handles user search operations
 * @param root is the root element of the tree
 * @return successful status
 */
Boolean containsHandler(struct Node *root) {
    int id;
    printf("\nPlease enter user id: ");
    scanf("%d", &id);
    struct Node *tempUser = search(root, id);
    if (tempUser != NULL) {
        printf("\nUser is in the tree. Informations: \n");
        printUserInfo(tempUser);
        return True;
    } else {
        printf("\nUser is not in the tree\n");
        return False;
    }
}


/**
 * This function handles friend printing operations
 * @param root is the root element of the tree
 * @return successful status
 */
Boolean friendsHandler(struct Node *root) {
    int id;
    printf("\nPlease enter user id: ");
    scanf("%d", &id);
    struct Node *tempUser = search(root, id);

    if (tempUser != NULL) {
        friends(root, id);
        return True;
    } else {
        printf("\nUser is not in the tree\n");
        return False;
    }
}


/**
 * This function handles printing tree
 * @param root is the root element of the tree
 * @return successful status
 */
Boolean printNextHandler(struct Node *root) {
    int id;
    printf("Please enter user id: ");
    scanf("%d", &id);

    struct Node *tempNode = search(root, id);

    if (tempNode != NULL) {
        printInOrder(tempNode);
        return True;
    } else {
        printf("\nUser is not in the tree");
        return False;
    }
}


/**
 * This function prints nodes of a given tree
 * @param root is the root element of the tree
 */
void printInOrder(struct Node *root) {
    /*
     * If root is not NULL, print left hand-side tree elements
     * then print the root
     * then print the right hand-side tree elements
     */
    if (root != NULL) {
        printInOrder(root->left);
        printUserInfo(root);
        printInOrder(root->right);
    }
}


/**
 * This function handles printing operations
 * @param root is the root element of the tree
 * @return successful status
 */
Boolean printGreaterHandler(struct Node *root) {
    int id;
    printf("\nPlease enter user id: ");
    scanf("%d", &id);

    if (search(root, id) != NULL) {
        printGreater(root, id);
        return True;
    } else {
        printf("\nUser is not in the tree\n");
        return False;
    }
}


/**
 * This function prints information of users
 * whose id's is greater then given id
 * @param root is the root element of the tree
 * @param id is the given user's id
 */
void printGreater(struct Node *root, int id) {
    if (root != NULL) {
        printGreater(root->left, id);
        if (root->id > id)
            printUserInfo(root);
        printGreater(root->right, id);
    }
}