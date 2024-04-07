#include "mtll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Function to check if a string is a valid integer
bool isInteger(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

int main() {
    // Initialization
    struct list *list = (struct list *)malloc(sizeof(struct list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char line[50];
    char command[20];
    char num_str[20];
    char listid[20];
    char input[20];
    char ind[20];

    while (true) { // Loop indefinitely
        // Read input from stdin
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

//        printf("input>>>%s\n", line);

        if (strcmp(line, "NEW") == 0 || strcmp(line, "VIEW") == 0 || strcmp(line, "TYPE") == 0 || 
            strcmp(line, "REMOVE") == 0 || strcmp(line, "INSERT") == 0 || strcmp(line, "DELETE") == 0) {
            printf("INVALID COMMAND: %s\n", line);
            continue;
        }

        // Remove leading and trailing whitespace
        char *trimmed_line = line;
        while (isspace(*trimmed_line)) {
            trimmed_line++;
        }
        int len = strlen(trimmed_line);
        while (len > 0 && isspace(trimmed_line[len - 1])) {
            trimmed_line[--len] = '\0';
        }

        if (isspace(*line) || isspace(line[strlen(line) - 1])) {
            if (strncmp(trimmed_line, "NEW", strlen("NEW")) == 0 || 
                strncmp(trimmed_line, "REMOVE", strlen("REMOVE")) == 0 || 
                strncmp(trimmed_line, "TYPE", strlen("TYPE")) == 0 || 
                strncmp(trimmed_line, "VIEW", strlen("VIEW")) == 0 || 
                strncmp(trimmed_line, "INSERT", strlen("INSERT")) == 0 || 
                strncmp(trimmed_line, "DELETE", strlen("DELETE")) == 0) {
                printf("INVALID COMMAND: INPUT\n");
            } else {
                printf("INVALID COMMAND: INPUT\n");
            }
            continue;
        }

        if (strstr(trimmed_line, "INSERT") != NULL) {
            // Read the first three strings as before
            if (sscanf(trimmed_line, "%s %s %s", command, listid, ind) == 3) {
                // Read the last string until newline character
                int last_index = strlen(command) + strlen(listid) + strlen(ind) + 3; // Account for spaces and null terminator
                if (sscanf(trimmed_line + last_index, "%[^\n]", input) == 1) {
                    if (strcmp(command, "INSERT") == 0) {
                        // Convert listid and ind strings to integers
                        int listId, index;
                        if (!isInteger(listid) || (!isInteger(ind) && (ind[0] != '-' || !isInteger(ind + 1)))) {
                            printf("INVALID COMMAND: INSERT\n");
                            continue;
                        } else {
                            // Convert strings to integers
                            sscanf(listid, "%d", &listId);
                            sscanf(ind, "%d", &index);
                            
                            // Check if integers are non-negative
                            if (listId < 0) {
                                printf("INVALID COMMAND: INSERT\n");
                            } else {
                                InsertNewNode(head, listId, index, input);
                            }
                        }
                    }
                } else {
                    printf("INVALID COMMAND: INSERT\n");
                }
            } else {
                printf("INVALID COMMAND: INSERT\n");
            }
            continue;
        }


        if (strstr(trimmed_line, "DELETE") != NULL && head != NULL) {
            // Split the trimmed line into tokens
            char *token = strtok(trimmed_line, " ");
            if (token == NULL || strcmp(token, "DELETE") != 0) {
                printf("INVALID COMMAND: DELETE\n");
                continue;
            }

            int token_count = 0;
            char *tokens[3];  // Maximum of three tokens: "DELETE", listid, ind
            
            while (token != NULL && token_count < 3) {
                tokens[token_count++] = token;
                token = strtok(NULL, " ");
            }
            
            // Check if the correct number of tokens is obtained
            if (token_count != 3) {
                printf("INVALID COMMAND: DELETE\n");
                continue;
            }
            
            // Extract listid and ind from tokens
            char *listid = tokens[1];
            char *ind = tokens[2];
            
            // Validate listid and ind
            int listId, index;
            if (!isInteger(listid) || (!isInteger(ind) && (ind[0] != '-' || !isInteger(ind + 1)))) {
                printf("INVALID COMMAND: DELETE\n");
                continue;
            }
            
            // Convert strings to integers
            sscanf(listid, "%d", &listId);
            sscanf(ind, "%d", &index);
            
            // Check if listId is non-negative
            if (listId < 0) {
                printf("INVALID COMMAND: DELETE\n");
            } else {
                DeleteNode(&head, listId, index);
            }
            
            continue;
        }


        // Parse the command
        if (strcmp(trimmed_line, "VIEW ALL") == 0) {
            if (noList == true) {
                printf("Number of lists: 0\n");
            } else {
                mtll_viewAll(head);
            }

        } else if (sscanf(trimmed_line, "%s %s", command, num_str) == 2) {
            int num;
            if (!isInteger(num_str) || sscanf(num_str, "%d", &num) != 1) {
                if (strcmp(command, "NEW") == 0 || strcmp(command, "VIEW") == 0 || strcmp(command, "TYPE") == 0 || strcmp(command, "REMOVE") == 0) {
                    if (strlen(num_str) == 0) {
                        printf("INVALID COMMAND: %s\n", command);
                    } else {
                        printf("INVALID COMMAND: %s\n", command);
                    }
                } else {
                    printf("INVALID COMMAND: INPUT\n");
                }
                continue;
            }
            // Process valid commands with non-negative numbers
            if (strcmp(command, "NEW") == 0) {
                if (num < 0) {
                    printf("INVALID COMMAND: NEW\n");
                } else {
                    mtll_new(num);
                }
            } else if (strcmp(command, "VIEW") == 0) {
                if (noList == true || num < 0) {
                    printf("INVALID COMMAND: %s\n", command);
                } else {
                    mtll_view(head, num);
                }
            } else if (strcmp(command, "TYPE") == 0) {
                if (noList == true || num < 0) {
                    printf("INVALID COMMAND: %s\n", command);
                } else {
                    mtll_type(head, num);
                }
            } else if (strcmp(command, "REMOVE") == 0) {
                if (noList == true || num < 0) {
                    printf("INVALID COMMAND: %s\n", command);
                } else {
                    mtll_remove(&head, num);
                }
            } else {

                printf("INVALID COMMAND: INPUT\n");
            }
        } else if (strcmp(trimmed_line, "VIEW") == 0 || strcmp(trimmed_line, "NEW") == 0 ||
                   strcmp(trimmed_line, "TYPE") == 0 || strcmp(trimmed_line, "REMOVE") == 0) {
            printf("INVALID COMMAND: INPUT\n");         
        } else {
            printf("INVALID COMMAND: INPUT\n");
        }
    }
    free(list);

    return 0;
}
