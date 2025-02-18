/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:05:21 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/18 09:37:48 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void change_directory(t_mini *mini)
{
    char *path;
    char cwd[PATH_MAX]; // Pour stocker le chemin actuel

    path = expand_variables(mini->str + 3, mini->last_exit_status);
    if (path)
    {
        if (chdir(path) == -1)
            perror("cd");
        else
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                setenv("PWD", cwd, 1);
            }
            else
            {
                perror("getcwd");
            }
        }
        free(path);
    }
    else
    {
        printf("Error: failed to expand path\n");
    }
}
