/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:45:27 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/18 09:37:30 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftFINAL/libft.h"
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_mini
{
	char	*str;
	char	*tmpstr;
	char	**args;
	int		last_exit_status;
}	t_mini;

typedef struct s_expand
{
	char	*expanded;
	int		j;
}	t_expand;

int		only_space(t_mini *mini);
int		is_space(char c);
int		isdigit_str(char *str);
size_t	strlenus(char *str);
size_t	strlenws(char *str);
int		count_words_skipall(const char *s);
char	**ft_split_all(const char *str);

// echo //

void	ft_echo(char *str);
void	print_words_with_spaces(char *str, int *i);
int		handle_n_option(char *str, int *i);

// cd //

/// @brief Changes the current directory and updates PWD
/// @param mini Structure containing the minishell information
void	change_directory(t_mini *mini);

// exit //

void	ft_exit(t_mini *mini);
void	clean_exit(t_mini *mini, int i);
void	clean(t_mini *mini);

// env //

/// @brief Processes a dollar sign encountered during expansion
/// @param str The string to analyze
/// @param i Pointer to the index in the string, will be updated
/// @param exp Structure containing the result string and its current index
/// @param last_exit_status The exit code of the last command
/// @return Pointer to the updated result string
char	*process_dollar_sign(char *str, int *i, t_expand *exp, int last_exit_status);
/// @brief Gets the size of an environment variable
/// @param str The string containing the variable name starting at index i
/// @param i Pointer to the index in the string, will be updated to point after the variable name
/// @return The size of the environment variable's value, or 0 if not found
size_t	get_var_size(char *str, int *i);
/// @brief Main function that expands all variables in a string
/// @param str The string to analyze
/// @param last_exit_status The exit code of the last command
/// @return A new string with all variables expanded, or NULL if error
char	*expand_variables(char *str, int last_exit_status);
/// @brief Calculates the total size needed after expansion
/// @param str The string to analyze
/// @param last_exit_status The exit code of the last command
/// @return The total calculated size, plus 1 for the final null character
size_t	calculate_expanded_size(char *str, int last_exit_status);
/// @brief Handles the expansion of a dollar sign found in a string
/// @param str The string containing the '$' character
/// @param i Pointer to the index in the string, will be updated
/// @param last_exit_status The exit code of the last executed command
/// @return The size the variable will take once expanded
size_t	handle_dollar(char *str, int *i, int last_exit_status);
/// @brief Expands an environment variable into the result string
/// @param str The string containing the variable name
/// @param i Pointer to the index in the string, will be updated
/// @param exp Structure containing the result string and its current index
/// @return  new string with all variables expanded, or NULL if error
char	*expand_env_variable(char *str, int *i, t_expand *exp);
/// @brief Expands the exit code ($?) into the result string
/// @param exp Structure containing the result string and its current index
/// @param last_exit_status The exit code of the last command
/// @return Pointer to the updated result string
char	*expand_exit_status(t_expand *exp, int last_exit_status);
/// @brief Calculates the length of a variable name in a string
/// @param str The string containing the variable name
/// @return The length of the variable name
int		ft_varlen(char *str);

#endif
