#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define token types
#define INPUT_FILE 1
#define HEREDOC 2
#define OUTPUT_TRUNC 3
#define OUTPUT_APPEND 4
#define PIPE 5
#define CMD 6
#define ARG 7

// Linked list structure
typedef struct s_node {
    char *content;
    int token;
    int dollar_in_single;
    struct s_node *next;
} t_node;

// Function to create a new node
t_node *create_node(char *content, int token, int dollar_in_single) {
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->content = strdup(content);
    new_node->token = token;
    new_node->dollar_in_single = dollar_in_single;
    new_node->next = NULL;
    return new_node;
}

// Function to append a node to the linked list
void append_node(t_node **head, char *content, int token, int dollar_in_single) {
    t_node *new_node = create_node(content, token, dollar_in_single);
    if (!new_node)
        return;
    if (!*head) {
        *head = new_node;
    } else {
        t_node *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

// Function to determine the token type
int get_token_type(char *word) {
    if (strcmp(word, "|") == 0) return PIPE;
    if (strcmp(word, ">") == 0) return OUTPUT_TRUNC;
    if (strcmp(word, ">>") == 0) return OUTPUT_APPEND;
    if (strcmp(word, "<") == 0) return INPUT_FILE;
    if (strcmp(word, "<<") == 0) return HEREDOC;
    if (strcmp(word, "echo") == 0 || strcmp(word, "cd") == 0 || strcmp(word, "pwd") == 0 ||
        strcmp(word, "exit") == 0 || strcmp(word, "export") == 0 || strcmp(word, "env") == 0 || strcmp(word, "unset") == 0) 
        return CMD;
    return ARG; // Default to argument
}

// Function to parse the input while handling quotes
void parse_input(char *input, t_node **head) {
    int i = 0, in_single = 0, in_double = 0;
    char buffer[1024]; // Temporary storage
    int buf_index = 0;
    int dollar_in_single = 0;

    while (input[i]) {
        if (input[i] == '\'') in_single = !in_single;
        else if (input[i] == '"' && !in_single) in_double = !in_double;
        else {
            if (in_single && input[i] == '$') dollar_in_single = 1;
            if (!isspace(input[i]) || in_single || in_double || strchr("|<>", input[i])) {
                if (strchr("|<>", input[i]) && !in_single && !in_double) {
                    if (buf_index > 0) {
                        buffer[buf_index] = '\0';
                        append_node(head, buffer, get_token_type(buffer), dollar_in_single);
                        buf_index = 0;
                        dollar_in_single = 0;
                    }
                    buffer[0] = input[i];
                    buffer[1] = '\0';
                    append_node(head, buffer, get_token_type(buffer), 0);
                } else {
                    buffer[buf_index++] = input[i];
                }
            } else {
                if (buf_index > 0) {
                    buffer[buf_index] = '\0';
                    append_node(head, buffer, get_token_type(buffer), dollar_in_single);
                    buf_index = 0;
                    dollar_in_single = 0;
                }
            }
        }
        i++;
    }
    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        append_node(head, buffer, get_token_type(buffer), dollar_in_single);
    }
}

// Function to print the linked list
void print_list(t_node *head) {
    while (head) {
        printf("Content: %s, Token: %d, Dollar in Single: %d\n", head->content, head->token, head->dollar_in_single);
        head = head->next;
    }
}

int main() {
    t_node *head = NULL;
    char input[] = "echo|exit";
    parse_input(input, &head);
    print_list(head);
    return 0;
}
