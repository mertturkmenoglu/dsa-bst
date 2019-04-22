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

typedef struct {
    int id;
    char *name;
    int friends[MAX_FRIEND_SIZE];
    int friendsCount;
    struct Node *left;
    struct Node *right;
} Node;

typedef int Boolean;


void clearScreen(int osFlag);

void printMenu();

Boolean caseHandler(Node *head, int choice);

Node *createNewUser(int id, char *name, int *friends, int friendsCount);

void printUserInfo(Node *user);


int main() {
    /**
     * osFlag: Holds user operating system information for system commands
     * choice: Holds operation information
     * exitFlag: Holds true operation value about loops
     * head: Head of the Binary Search tree
     */
    int osFlag;
    int choice;
    Boolean exitFlag = False;
    Node *head = NULL;

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
            Boolean isSuccess = caseHandler(head, choice);
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
* @param head is the head of the binary search tree
* @param choice is the function number
*/
Boolean caseHandler(Node *head, int choice) {
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
Node *createNewUser(int id, char *name, int *friends, int friendsCount) {
    Node *newUser;
    // Memory allocation for struct
    newUser = (Node *) malloc(sizeof(Node));

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
void printUserInfo(Node *user) {
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