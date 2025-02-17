/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:45:27 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/17 10:34:33 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftFINAL/libft.h"
# include <unistd.h>
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
void	change_directory(t_mini *mini);

char	*expand_exit_status(char *expanded, int *j, int last_exit_status);
char	*expand_env_variable(char *str, int *i, char *expanded, int *j);
char	*process_dollar_sign(char *str, int *i, char *expanded, int *j, int last_exit_status);
char	*expand_variables(char *str, int last_exit_status);
int		ft_varlen(char *str);

#endif
