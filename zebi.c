/* Add this to your minishell.h file */

// Structure to store heredoc information
typedef struct s_heredoc
{
    char *delimiter;
    int pipe_fd[2];
    struct s_heredoc *next;
} t_heredoc;

// Function prototypes
t_heredoc *collect_heredocs(t_node *tokens);
int process_heredocs(t_heredoc *heredocs, t_mini *mini);
void free_heredocs(t_heredoc *heredocs);

/* New implementation for collect_heredocs.c */

#include "../minishell.h"

static t_heredoc *create_heredoc_node(char *delimiter)
{
    t_heredoc *new_node;

    new_node = malloc(sizeof(t_heredoc));
    if (!new_node)
        return (NULL);
    new_node->delimiter = ft_strdup(delimiter);
    if (!new_node->delimiter)
    {
        free(new_node);
        return (NULL);
    }
    new_node->next = NULL;
    return (new_node);
}

static void add_heredoc(t_heredoc **heredocs, t_heredoc *new_node)
{
    t_heredoc *current;

    if (!*heredocs)
    {
        *heredocs = new_node;
        return;
    }
    current = *heredocs;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

t_heredoc *collect_heredocs(t_node *tokens)
{
    t_node *current;
    t_heredoc *heredocs;
    t_heredoc *new_node;

    heredocs = NULL;
    current = tokens;
    while (current)
    {
        if (current->type == HEREDOC && current->next)
        {
            new_node = create_heredoc_node(current->next->data);
            if (!new_node)
            {
                free_heredocs(heredocs);
                return (NULL);
            }
            add_heredoc(&heredocs, new_node);
            current = current->next;
        }
        current = current->next;
    }
    return (heredocs);
}

void free_heredocs(t_heredoc *heredocs)
{
    t_heredoc *current;
    t_heredoc *next;

    current = heredocs;
    while (current)
    {
        next = current->next;
        if (current->delimiter)
            free(current->delimiter);
        free(current);
        current = next;
    }
}

/* Modified process_heredocs.c */

#include "../minishell.h"

static int setup_pipe_and_signals(int pipe_fds[2])
{
    if (pipe(pipe_fds) == -1)
    {
        perror("minishell: pipe");
        return (-1);
    }
    set_sig_executing();
    return (0);
}

static int process_line(char *line, char *delimiter, int pipe_fd, t_mini *mini)
{
    char *expanded_line;

    if (line[ft_strlen(line) - 1] == '\n')
        line[ft_strlen(line) - 1] = '\0';
    if (ft_strcmp(line, delimiter) == 0)
    {
        free(line);
        return (1);
    }
    else
    {
        expanded_line = expand_variables(line,
                mini->last_exit_status, mini->env, 1);
        free(line);
        line = expanded_line;
    }
    ft_putstr_fd(line, pipe_fd);
    ft_putstr_fd("\n", pipe_fd);
    free(line);
    return (0);
}

static int read_lines(char *delimiter, int pipe_fd, t_mini *mini)
{
    char *line;
    int result;

    while (1)
    {
        line = readline("> ");
        if (g_signal == 130)
            break;
        if (!line)
        {
            fd_printf(2,
                "minishell: warning: here-document delimited by end-of-file\n");
            break;
        }
        result = process_line(line, delimiter, pipe_fd, mini);
        if (result == 1)
            break;
    }
    return (0);
}

int process_heredocs(t_heredoc *heredocs, t_mini *mini)
{
    t_heredoc *current;

    current = heredocs;
    while (current)
    {
        if (setup_pipe_and_signals(current->pipe_fd) == -1)
            return (-1);
        read_lines(current->delimiter, current->pipe_fd[1], mini);
        close(current->pipe_fd[1]);
        current = current->next;
    }
    return (0);
}

/* Modified apply_redirections.c */

#include "../minishell.h"

static int handle_input_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd);
        perror("minishell: dup2");
        return (-1);
    }
    close(fd);
    return (0);
}

static int handle_output_trunc(char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        perror("minishell: dup2");
        return (-1);
    }
    close(fd);
    return (0);
}

static int handle_output_append(char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        perror("minishell: dup2");
        return (-1);
    }
    close(fd);
    return (0);
}

// New function to handle a heredoc that's already been processed
static int handle_processed_heredoc(int pipe_fd)
{
    if (dup2(pipe_fd, STDIN_FILENO) == -1)
    {
        close(pipe_fd);
        perror("minishell: dup2");
        return (-1);
    }
    close(pipe_fd);
    return (0);
}

static int process_redirection(t_node *current, t_node *tokens, 
                             t_mini *mini, t_heredoc **heredocs)
{
    int result;
    static int heredoc_index = 0;
    t_heredoc *current_heredoc;

    result = 0;
    if (current->type == INPUT_FILE && current->next)
        result = handle_input_file(current->next->data);
    else if (current->type == OUTPUT_TRUNC && current->next)
        result = handle_output_trunc(current->next->data);
    else if (current->type == OUTPUT_APPEND && current->next)
        result = handle_output_append(current->next->data);
    else if (current->type == HEREDOC && current->next)
    {
        // Find the right heredoc in our list
        current_heredoc = *heredocs;
        for (int i = 0; i < heredoc_index && current_heredoc; i++)
            current_heredoc = current_heredoc->next;
        
        if (current_heredoc)
        {
            result = handle_processed_heredoc(current_heredoc->pipe_fd[0]);
            heredoc_index++;
        }
    }
    return (result);
}

int apply_redirections(t_node *tokens, t_mini *mini)
{
    t_node *current;
    int result;
    static t_heredoc *heredocs = NULL;
    static int first_call = 1;

    // On first call to this function in a command line, collect and process all heredocs
    if (first_call)
    {
        heredocs = collect_heredocs(tokens);
        if (heredocs)
        {
            if (process_heredocs(heredocs, mini) == -1)
            {
                free_heredocs(heredocs);
                heredocs = NULL;
                first_call = 0;
                return (-1);
            }
        }
        first_call = 0;
    }

    current = tokens;
    while (current)
    {
        if ((current->type == INPUT_FILE || current->type == OUTPUT_TRUNC
                || current->type == OUTPUT_APPEND || current->type == HEREDOC)
            && current->next)
        {
            result = process_redirection(current, tokens, mini, &heredocs);
            if (result == -1)
            {
                // Only free heredocs after the last command in a pipeline
                // We'll rely on execute_pipeline to reset first_call
                return (1);
            }
            current = current->next;
        }
        current = current->next;
    }
    
    return (0);
}

/* Modifications to exec.c */

// At the end of execute_pipeline, add:
int execute_pipeline(t_mini *mini, t_node *tokens)
{
    // ... existing code ...
    
    // Add this at the end, before returning
    // Reset the static variables in apply_redirections for the next command line
    reset_heredoc_processing();
    
    return (free_all(commands, NULL, cmd_count), exit_status);
}

// Add this function to reset the heredoc processing state
void reset_heredoc_processing(void)
{
    // This is a function you need to implement that will reset the static variables
    // in apply_redirections
}

// Add this function declaration to minishell.h
void reset_heredoc_processing(void);