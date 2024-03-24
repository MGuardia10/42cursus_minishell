/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:20:44 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/24 17:23:18 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	store_exe(char **tokens, t_shell *shell, int *i, int *j)
{
	if (*i != 0)
	{
		*j += 1;
		*i += 1;
	}
	shell->cmds[*j].exe = ft_strdup(tokens[*i]);
	if (!shell->cmds[*j].exe)
		return (1);
	return (0);
}

int	store_redir(char **tokens, t_shell *shell, int *i, int j)
{
	if (isredir(tokens[*i]) == IN || isredir(tokens[*i]) == HEREDOC)
	{
		shell->cmds[j].infile[shell->cmds[j].infile_count].redir = isredir(tokens[*i]);
		*i += 1;
		shell->cmds[j].infile[shell->cmds[j].infile_count].filename = ft_strdup(tokens[*i]);
		if (!shell->cmds[j].infile[shell->cmds[j].infile_count].filename)
			return (1);
		shell->cmds[j].infile_count++;
	}
	else if (isredir(tokens[*i]) == OUT || isredir(tokens[*i]) == APPOUT)
	{
		shell->cmds[j].outfile[shell->cmds[j].outfile_count].redir = isredir(tokens[*i]);
		*i += 1;
		shell->cmds[j].outfile[shell->cmds[j].outfile_count].filename = ft_strdup(tokens[*i]);
		if (!shell->cmds[j].outfile[shell->cmds[j].outfile_count].filename)
			return (1);
		shell->cmds[j].outfile_count++;
	}
	return (0);
}

int	store_arg(char **tokens, t_shell *shell, int i, int j)
{
	shell->cmds[j].args[shell->cmds[j].args_count] = ft_strdup(tokens[i]);
	if (!shell->cmds[j].args[shell->cmds[j].args_count])
		return (1);
	shell->cmds[j].args_count++;
	return (0);
}

int	store_tokens(char **tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if ((tokens[i][0] == '|' && ft_strlen(tokens[i]) == 1) || (i == 0))
		{
			if (store_exe(tokens, shell, &i, &j) == 1)
				return (1);
		}
		else if (isredir(tokens[i]) != NONE)
		{
			if (store_redir(tokens, shell, &i, j) == 1)
				return (1);
		}
		else
		{
			if (store_arg(tokens, shell, i, j) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}