#include "mtll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include <stdbool.h>

struct list *head = NULL;
struct list *current = NULL;
int counter = 0;
bool noList = true;
int indexNode = 0;

struct mtll *mtll_create() {
    struct mtll* list = (struct mtll*)malloc(sizeof(struct mtll)); // allocates memory from heap
    if (list == NULL) {
        fprintf(stderr, "Failed to create mtll list\n");
        exit(EXIT_FAILURE);
    }
    list->head_node = NULL; // creates an empty list
    return list; // returns the list
}

void mtll_remove(struct list **list_ptr, int num) {
    if (*list_ptr == NULL) {
        fprintf(stderr, "Error: Invalid list\n");
        return;
    }

    struct list *prev = NULL;
    struct list *current = *list_ptr;

    // Traverse the list to find the mtll with the specified count
    while (current != NULL) {
        if (current->head_list->count == num) {
            printf("List %d has been removed.\n", num);
            printf("\n");

            // Free all nodes within the mtll
            struct mtll_node *currentNode = current->head_list->head_node;
            while (currentNode != NULL) {
                struct mtll_node *temp = currentNode;
                currentNode = currentNode->next;
                free(temp->data); // Free the data
                free(temp);       // Free the node itself
            }

            // Free the mtll itself
            struct mtll *tempMtll = current->head_list;
            current->head_list = NULL;
            free(tempMtll);

            // Remove the list node from the main list
            if (prev == NULL) {
                *list_ptr = current->next_list;
                free(current);
                if (*list_ptr != NULL) { // Check if the list is not empty
                    mtll_viewAll(head); // Only call mtll_viewAll if the list is not empty
                } else {
                    printf("Number of lists: 0\n");
                    noList = true;
                }
                return;
            } else {
                prev->next_list = current->next_list;
                free(current);
                if (*list_ptr != NULL) { // Check if the list is not empty
                    mtll_viewAll(head); // Only call mtll_viewAll if the list is not empty
                } else {
                    printf("Number of lists: 0\n");
                    noList=true;
                }
                return;
            }
        }
        prev = current;
        current = current->next_list;
    }

    // If the specified list number is not found, print a message
    printf("INVALID COMMAND: REMOVE\n");
}

void InsertList(struct mtll* mtll) {
    struct list *lk = (struct list *)malloc(sizeof(struct list));
    if (lk == NULL){
        fprintf(stderr, "Failed to allocate memory for list node\n");
        exit(EXIT_FAILURE);
    }
    lk->head_list = mtll;
    lk->next_list = NULL; // Make sure next_list is initialized to NULL
    if (head == NULL) {
        head = lk;
    } else {
        struct list *linkedlist = head;
        while(linkedlist->next_list != NULL) {
            linkedlist = linkedlist->next_list;
        }
        linkedlist->next_list = lk;
    }
    mtll->count = counter;
    counter++;
}

void InsertNode(struct mtll *mtll, void *data, char *type, int indexNode) {
    struct mtll_node *node = (struct mtll_node *)malloc(sizeof(struct mtll_node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }

    if (strcmp(type, "float") == 0) {
        node->data = malloc(sizeof(float));
        if (node->data == NULL) {
            exit(EXIT_FAILURE);
        }
        *((float *)node->data) = atof((char *)data); // Convert string to float
    } else if (strcmp(type, "int") == 0) {
        node->data = malloc(sizeof(int));
        if (node->data == NULL) {
            exit(EXIT_FAILURE);
        }
        *((int *)node->data) = atoi((char *)data); // Convert string to int
    } else if (strcmp(type, "char") == 0) {
        node->data = malloc(sizeof(char));
        if (node->data == NULL) {
            exit(EXIT_FAILURE);
        }
        *((char *)node->data) = *((char *)data); // Assign character directly
    } else if (strcmp(type, "string") == 0) {
        node->data = strdup((char *)data); // Duplicate string
        if (node->data == NULL) {
            exit(EXIT_FAILURE);
        }
    } else {
        // Handle unsupported types here
        fprintf(stderr, "Unsupported data type: %s\n", type);
        exit(EXIT_FAILURE);
    }

    strcpy(node->type, type);
    node->indexNode = indexNode;
    node->next = NULL;

    if (mtll->head_node == NULL) {
        mtll->head_node = node;
    } else {
        struct mtll_node *current = mtll->head_node;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

void mtll_viewAll(struct list *list) {
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    int i = 0;
    struct list *currCount = list;
    while (currCount != NULL) {
        i++;
        currCount = currCount->next_list;
    }
    printf("Number of lists: %d\n", i);
    struct list *current = list;
    while (current != NULL) {
        struct mtll *currentMtll = current->head_list;
        printf("List %d\n", currentMtll->count);
        struct mtll_node *currentNode = currentMtll->head_node;
        while (currentNode != NULL) {
            // Print or process currentNode if needed
            currentNode = currentNode->next;
        }
        current = current->next_list;
    }
}

void mtll_view(struct list *list, int num) {
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }

    struct list *current = list;
    while (current != NULL) {
        struct mtll *currentMtll = current->head_list;
        if (currentMtll->count == num) {
            struct mtll_node *currentNode = currentMtll->head_node;
            while (currentNode != NULL) {
                if (strcmp(currentNode->type, "int") == 0) {
                    printf("%d", *((int *)currentNode->data));
                } else if (strcmp(currentNode->type, "float") == 0) {
                    printf("%.2f", *((float *)currentNode->data));
                } else if (strcmp(currentNode->type, "char") == 0) {
                    printf("%c", *((char *)currentNode->data));
                } else if (strcmp(currentNode->type, "string") == 0) {
                    printf("%s", (char *)currentNode->data);
                }
                if (currentNode->next != NULL) {
                    printf(" -> ");
                } else {
                    printf("\n");
                }
                currentNode = currentNode->next;
            }
            return; // Once found and printed the list, exit the function
        }
        current = current->next_list;
    }
    // If the specified list number is not found, print a message
    printf("INVALID COMMAND: VIEW\n");
}

void mtll_type(struct list *list, int num) {
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }

    struct list *current = list;
    while (current != NULL) {
        struct mtll *currentMtll = current->head_list;
        if (currentMtll->count == num) {
            struct mtll_node *currentNode = currentMtll->head_node;
            while (currentNode != NULL) {
                printf("%s", currentNode->type);
                if (currentNode->next != NULL) {
                    printf(" -> ");
                } else {
                    printf("\n");
                }
                currentNode = currentNode->next;
            }
            return; // Once found and printed the list, exit the function
        }
        current = current->next_list;
    }
    // If the specified list number is not found, print a message
    printf("INVALID COMMAND: TYPE\n");
}


// Function to check if a string represents a scientific number
bool isScientificNumber(const char *str) {
    int len = strlen(str);
    if (len < 3) // Minimum length for a scientific number is 'xey'
        return false;

    // Check for the presence of 'e' or 'E'
    char *e_position = strchr(str, 'e');
    if (e_position == NULL)
        e_position = strchr(str, 'E');
    if (e_position == NULL)
        return false;

    // Check if the part before 'e' or 'E' can be converted to a valid float
    char number_before_e[e_position - str + 1];
    strncpy(number_before_e, str, e_position - str);
    number_before_e[e_position - str] = '\0';
    if (atof(number_before_e) == 0 && number_before_e[0] != '0') // atof returns 0 for invalid input
        return false;

    // Check if the part after 'e' or 'E' can be converted to a valid integer
    char *endptr;
    strtol(e_position + 1, &endptr, 10);
    if (*endptr != '\0') // The entire string should be converted to an integer
        return false;

    return true;
}

// Function to process the input and insert nodes into the multi-type linked list
void mtll_new(int num) {
    struct mtll *new_list = mtll_create();
    if (new_list == NULL) {
        fprintf(stderr, "HEAP MEMORY ALLOCATION ERROR\n");
        exit(EXIT_FAILURE);
    }

    char buffer[129];
    new_list->count = 0;

    for (int i = 0; i < num; i++) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            exit(EXIT_FAILURE);
        }   

        // Remove trailing newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Convert scientific notation string to float
        char float_buffer[20]; // Buffer for storing converted float
        if (isScientificNumber(buffer)) {
            double value;
            sscanf(buffer, "%lf", &value);
            snprintf(float_buffer, sizeof(float_buffer), "%.2f", value);
            InsertNode(new_list, float_buffer, "float", indexNode);
            indexNode++;
        } else {
            buffer[strcspn(buffer, "\n")] = '\0'; // remove any trailing white lines

            if (strcmp(buffer, "-0") == 0) {
                strcpy(buffer, "0");
            }

            // Check if the buffer contains any non-printable characters
            bool has_nonprintable = false;
            for (int j = 0; buffer[j] != '\0'; j++) {
                if (!isprint(buffer[j])) {
                    has_nonprintable = true;
                    break;
                }
            }

            if (has_nonprintable || strchr(buffer, '%') != NULL) { // Check if the buffer contains non-printable characters or '%'
                InsertNode(new_list, buffer, "string", indexNode); // Treat as string if contains non-printable characters or '%'
                indexNode++;
            } else if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
                if (strchr(buffer, '.') != NULL) {
                    InsertNode(new_list, buffer, "float", indexNode);
                    indexNode++;
                } else {
                    InsertNode(new_list, buffer, "int", indexNode);
                    indexNode++;
                }
            } else if (strlen(buffer) == 1) {
                InsertNode(new_list, buffer, "char", indexNode);
                indexNode++;
            } else {
                if (strchr(buffer, '{') || strchr(buffer, '}')) {
                    printf("INVALID COMMAND: NEW\n");
                    return;
                }
                InsertNode(new_list, buffer, "string", indexNode); // Treat as string for other cases
                indexNode++;
            }
        }
    }
    // Print the contents of the list
    InsertList(new_list);
    indexNode = 0;
    noList = false;
    struct mtll_node *currentNode = new_list->head_node;
    printf("List %d: ", new_list->count);
    if (num == 0) {
        printf("\n");
    }
    while (currentNode != NULL) {
        if (strcmp(currentNode->type, "int") == 0) {
            printf("%d", *((int *)currentNode->data));
        } else if (strcmp(currentNode->type, "float") == 0) {
            printf("%.2f", *((float *)currentNode->data));
        } else if (strcmp(currentNode->type, "char") == 0) {
            printf("%c", *((char *)currentNode->data));
        } else if (strcmp(currentNode->type, "string") == 0) {
            printf("%s", (char *)currentNode->data);
        }
        if (currentNode->next != NULL) {
            printf(" -> ");
        } else {
            printf("\n");
        }
        currentNode = currentNode->next;
    }
}

int highestNumberIndex(struct list *list, int listid) {
    if (list == NULL) {
        fprintf(stderr, "Error: NULL list\n");
        exit(EXIT_FAILURE);
    }
    
    int count = 0;  // Initialize count
    
    struct list *current = list;
    while (current != NULL) {
        struct mtll *currentMtll = current->head_list;
        if (currentMtll != NULL && currentMtll->count == listid) {
            struct mtll_node *currentNode = currentMtll->head_node;
            while (currentNode != NULL) {
                count++;  // Increment count for each node
                currentNode = currentNode->next;
            }
            break; // Break the loop once the specific mtll is found
        }
        current = current->next_list;
    }
    
    // Return count - 1
    return count;
}

void DeleteNode(struct list **list_ptr, int num, int index) {
    if (*list_ptr == NULL) {
        fprintf(stderr, "Error: NULL list\n");
        return;
    }

    int indexAfter = highestNumberIndex(*list_ptr, num);
    if (index < 0 && index >= -indexAfter && index <= -1) {
        index = indexAfter + index;
    }
    if (index < -indexAfter) {
        printf("INVALID COMMAND: DELETE\n");
        return;
    }
    
    struct list *current_list = *list_ptr;
    struct mtll *current_mtll;
    
    // Find the list with the specified number (num)
    while (current_list != NULL) {
        if (current_list->head_list != NULL && current_list->head_list->count == num) {
            current_mtll = current_list->head_list;
            break;
        }
        current_list = current_list->next_list;
    }
    
    // If no list with the specified number is found
    if (current_list == NULL) {
        printf("INVALID COMMAND: DELETE\n");
        return;
    }
    
    // Find the node with the specified index in the mtll
    struct mtll_node *current_node = current_mtll->head_node;
    struct mtll_node *prev_node = NULL;
    
    while (current_node != NULL) {
        if (current_node->indexNode == index) {
            // Adjust next pointers to skip the selected node
            if (prev_node == NULL) {
                current_mtll->head_node = current_node->next;
            } else {
                prev_node->next = current_node->next;
            }
            
            // Free memory for the selected node
            free(current_node->data);
            free(current_node);
            
            // Decrement indexNode for nodes after the deleted node
            struct mtll_node *temp = current_mtll->head_node;
            while (temp != NULL) {
                if (temp->indexNode > index) {
                    temp->indexNode--;
                }
                temp = temp->next;
            }
            
            // Print the new list
            printf("List %d: ", current_mtll->count);
            struct mtll_node *currentNodex = current_mtll->head_node;
            if (currentNodex == NULL) {
                printf("\n");
            }
            while (currentNodex != NULL) {
                if (strcmp(currentNodex->type, "int") == 0) {
                    printf("%d", *((int *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "float") == 0) {
                    printf("%.2f", *((float *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "char") == 0) {
                    printf("%c", *((char *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "string") == 0) {
                    printf("%s", (char *)currentNodex->data);
                }
                if (currentNodex->next != NULL) {
                    printf(" -> ");
                } else {
                    printf("\n");
                }
                currentNodex = currentNodex->next;
            }
            return;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }
    
    printf("INVALID COMMAND: DELETE\n");
}



void InsertNewNode(struct list *list, int num, int index, void *value) {
    if (list == NULL) {
        printf("INVALID COMMAND: INSERT\n");
        return;
    }
    bool newNode = false;
    bool NegativeIndex = false;
    struct list *current = list;
    while (current != NULL) {
        struct mtll *currentMtll = current->head_list;
        int indexAfter = highestNumberIndex(list, num);
        if (index == indexAfter) {
            newNode = true;
        }
        if (index < 0 && index >= -indexAfter && index <= -1) {
            NegativeIndex = true;
        }
        if (index < -indexAfter && indexAfter != 0) {
            printf("INVALID COMMAND: INSERT\n");
        }

        if (currentMtll != NULL && currentMtll->count == num && index < indexAfter && NegativeIndex == false) {
            struct mtll_node *currentNode = currentMtll->head_node;
            while (currentNode != NULL) {
                if (currentNode->indexNode >= index) {
                    currentNode->indexNode++; // Increment indexNode for nodes after the specified index
                }
                currentNode = currentNode->next;
            }
            char float_buffer[20];
            if (isScientificNumber(value)) {
                double scival;
                sscanf(value, "%lf", &scival);
                snprintf(float_buffer, sizeof(float_buffer), "%.2f", scival);
                InsertNode(currentMtll, float_buffer, "float", index);
                sortNodes(currentMtll);
                struct mtll_node *currentNodex = currentMtll->head_node;
                printf("List %d: ", currentMtll->count);
                while (currentNodex != NULL) {
                    if (strcmp(currentNodex->type, "int") == 0) {
                        printf("%d", *((int *)currentNodex->data));
                    } else if (strcmp(currentNodex->type, "float") == 0) {
                        printf("%.2f", *((float *)currentNodex->data));
                    } else if (strcmp(currentNodex->type, "char") == 0) {
                        printf("%c", *((char *)currentNodex->data));
                    } else if (strcmp(currentNodex->type, "string") == 0) {
                        printf("%s", (char *)currentNodex->data);
                    }
                    if (currentNodex->next != NULL) {
                        printf(" -> ");
                    } else {
                        printf("\n");
                    }
                    currentNodex = currentNodex->next;
                }
                return;
                
            }

            // Insert the new node at the specified index
            char *type = typeChecker(value);
            InsertNode(currentMtll, value, type, index);
            sortNodes(currentMtll);
            struct mtll_node *currentNodex = currentMtll->head_node;
            printf("List %d: ", currentMtll->count);
            while (currentNodex != NULL) {
                if (strcmp(currentNodex->type, "int") == 0) {
                    printf("%d", *((int *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "float") == 0) {
                    printf("%.2f", *((float *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "char") == 0) {
                    printf("%c", *((char *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "string") == 0) {
                    printf("%s", (char *)currentNodex->data);
                }
                if (currentNodex->next != NULL) {
                    printf(" -> ");
                } else {
                    printf("\n");
                }
                currentNodex = currentNodex->next;
            }
            return;
        } else if (newNode == true) {
            if (currentMtll != NULL && currentMtll->count == num) {
            char *type = typeChecker(value);
            InsertNode(currentMtll, value, type, index);
            sortNodes(currentMtll);
            struct mtll_node *currentNodex = currentMtll->head_node;
            printf("List %d: ", currentMtll->count);
            while (currentNodex != NULL) {
                if (strcmp(currentNodex->type, "int") == 0) {
                    printf("%d", *((int *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "float") == 0) {
                    printf("%.2f", *((float *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "char") == 0) {
                    printf("%c", *((char *)currentNodex->data));
                } else if (strcmp(currentNodex->type, "string") == 0) {
                    printf("%s", (char *)currentNodex->data);
                }
                if (currentNodex->next != NULL) {
                    printf(" -> ");
                } else {
                    printf("\n");
                }
                currentNodex = currentNodex->next;
            }
            return;
            }

        } else if (NegativeIndex == true) {
            index = indexAfter + index + 1;
            InsertNewNode(current, num, index, value);
            return;
        }
        current = current->next_list;
    }
    printf("INVALID COMMAND: INSERT\n");
}


char *typeChecker(void *buffer) {
    if (buffer == NULL) {
        fprintf(stderr, "Error: NULL buffer\n");
        return NULL;
    }

    char *str_buffer = (char *)buffer;

    // Convert scientific notation string to float
    if (isScientificNumber(str_buffer)) {
        return "float";
    } else {
        if (strcmp(str_buffer, "-0") == 0) {
            strcpy(str_buffer, "0");
        }
        // Check if the buffer contains any non-printable characters
        bool has_nonprintable = false;
        for (int j = 0; str_buffer[j] != '\0'; j++) {
            if (!isprint(str_buffer[j])) {
                has_nonprintable = true;
                break;
            }
        }
        if (has_nonprintable || strchr(str_buffer, '%') != NULL) { // Check if the buffer contains non-printable characters or '%'
            return "string";
        } else if (isdigit(str_buffer[0]) || (str_buffer[0] == '-' && isdigit(str_buffer[1]))) {
            if (strchr(str_buffer, '.') != NULL) {
                return "float";
            } else {
                return "int";
            }
        } else if (strlen(str_buffer) == 1) {
            return "char";
        } else {
            if (strchr(str_buffer, '{') || strchr(str_buffer, '}')) {
                printf("INVALID COMMAND: INSERT\n");
                return NULL; // Error: No return value for this case
            }
            return "string";
        }
    }
}

void sortNodes(struct mtll *mtll) {
    if (mtll == NULL || mtll->head_node == NULL) {
        return; // If the list is empty or NULL, nothing to sort
    }
    
    int swapped;
    struct mtll_node *ptr1;
    struct mtll_node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = mtll->head_node;

        while (ptr1->next != lptr) {
            if (ptr1->indexNode > ptr1->next->indexNode) {
                swapNodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void swapNodes(struct mtll_node *a, struct mtll_node *b) {
    int tempIndex = a->indexNode;
    void *tempData = a->data;
    char tempType[20];
    strcpy(tempType, a->type);

    a->indexNode = b->indexNode;
    a->data = b->data;
    strcpy(a->type, b->type);

    b->indexNode = tempIndex;
    b->data = tempData;
    strcpy(b->type, tempType);
}
