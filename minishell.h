/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:45:27 by lgrisel           #+#    #+#             */
/*   Updated: 2025/04/14 17:41:15 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftFINAL/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <linux/limits.h>
# include <limits.h>
# include <stdio.h>
# include <termios.h>
# include <signal.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

typedef struct s_node
{
	char			*data;
	int				type;
	struct s_node	*next;
}	t_node;

typedef struct s_cmd
{
	char	**args;
	int		arg_count;
	t_node	*start;
	t_node	*end;
}	t_cmd;

typedef struct s_env_node
{
	char				*var;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env
{
	char	**env_vars;
	int		count;
	int		last_exit_status;
	t_node	*tokens;
}	t_env;

typedef struct s_mini
{
	char	*str;
	char	*exp;
	int		last_exit_status;
	int		i;
	int		j;
	int		k;
	char	*current_token;
	char	*quoted_part;
	int		special;
	t_env	*env;
}	t_mini;

typedef struct s_expand
{
	char	*expanded;
	int		i;
	int		j;
	int		sq;
	int		dq;
	char	quote;
	int		in_quote;
}	t_expand;

extern pid_t	g_signal;

// Token types
# define INPUT_FILE 1
# define HEREDOC 2
# define OUTPUT_TRUNC 3
# define OUTPUT_APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7

# define MSGREDIR "minishell: syntax error near unexpected token `newline'\n"
# define MSGPIPE "minishell: syntax error near unexpected token `|'\n"

void		print_command_not_found(const char *cmd);
int			handle_path_errors(char *cmd);
char		*get_command_path(char *cmd, t_mini *mini);
int			check_file_permissions(char *cmd);
int			check_is_directory(char *path, char *cmd);

t_node		**clean_commands(t_node **commands, int index);
t_node		**allocate_commands(int count);
t_node		**split_commands(t_node *tokens, int *cmd_count);
int			handle_heredoc(char *delimiter, t_mini *mini);
int			apply_redirections(t_node *tokens, t_mini *mini);
char		**extract_command_args(t_node *tokens);
t_node		*extract_command_token(t_node *tokens);
int			ft_conststrcmp(char *s1, const char *s2);
int			execute_builtin(t_mini *mini, t_node *tokens);
char		*find_command_path(char *cmd, t_mini *mini);
int			execute_external_command(t_mini *mini, char **args);
int			handle_fork_error(t_node **commands, int i, int cmd_count,
				int pipe_fds[2][2]);
void		setup_child_pipes(int i, int cmd_count, int pipe_fds[2][2]);
int			execute_pipeline(t_mini *mini, t_node *tokens);

// parsing //
int			empty_line(char *line);
int			is_unclosedquote(char *str);
int			check_redir_syntax(t_node *list);
int			check_pipe_syntax(t_node *list);
int			has_heredoc(t_node *list);

void		init_tokenization(t_node **head, t_mini *n);
int			init_new_token(char **current_token, char c);
t_node		*create_token(char *value, int type);
void		add_token(t_node **head, t_node *new_token);
void		free_list(t_node *head);

int			get_token_type(char *word, t_mini *t);
char		*process_quoted_section(char *input, int *i, char quote_char);
int			append_to_token(char **current_token, char c);
int			is_special(char *quoted_part);
void		handle_special_char(t_node **head, t_mini *t, char *input, int *i);

t_node		*tokenize_input(char *input, t_mini *n);
void		display_tokens(t_node *head);

// ctrl //
void		set_sig_interactive(int i);
void		set_sig_executing(void);

// echo //
void		ft_echo(t_mini *mini, t_node *args);

// cd //
int			ft_cd(t_mini *mini, t_node *list);
int			handle_cd_error(char *path);

// exit //
void		ft_exit(t_mini *mini, t_node *list);

// pwd //
int			ft_pwd(t_mini *mini);
int			update_pwd(t_env *env);

// unset //
int			ft_unset(t_mini *mini, t_node *list);
int			check_env_match(char *env_var, const char *var_name);
int			check_token_match(char *token_data, const char *var_name);

// env //
int			ft_env(t_mini *mini, t_node *args);
char		*expand_variables(char *str, int last_exit_status, t_env *env);
char		*expand_exit_status(t_expand *exp, int last_exit_status);
size_t		calc_exp_siz(char *str, int last_exit_status, t_env *env);
int			add_env_value(t_env *env, const char *name, const char *value);
int			init_shell_vars(t_env *env);
char		*process_dollar_sign(char *str, int *i, t_expand *exp, t_env *env);
char		*expand_env_variable(char *str, int *i, t_expand *exp, t_env *env);
char		*expand_env_variable(char *str, int *i, t_expand *exp, t_env *env);
char		*get_env_value(t_env *env, const char *name);
int			set_env_value(t_env *env, const char *name, const char *value);
size_t		handle_dollar(char *str, int *i, int last_exit_status, t_env *env);

// env utils //
char		*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char		*ft_strcpy2(char *dest, const char *src);
void		free_env(t_env *env);
t_env		*init_env(char **envp);

//export//
int			ft_export(t_mini *mini, t_node *list);
int			add_env_var_no_value(t_env *env, const char *name);
char		*str_n_copy(char *dest, const char *src, int n);
int			is_valid_first_char(char c);
int			is_valid_subsequent_char(char c);
int			validate_var_name(char *arg, int name_len);
int			handle_export_arg(t_mini *mini, char *arg);
int			update_or_add_env_var(t_env *env, const char *var);
int			var_exists(t_env *env, char *arg);
void		free_env_list(t_env_node *head);
t_env_node	*build_sorted_env_list(t_env *env);

// utils //
void		init_mini(t_mini *mini, char **envp);
int			ft_varlen(char *str);
int			ft_isspace(char c);
int			isdigit_str(char *str);
void		free_all(t_node **commands, char **args, int cmd_count);
void		free_paths(char **paths);

#endif
