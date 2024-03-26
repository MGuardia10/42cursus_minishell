/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_store.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:27:12 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:12 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	alloc_io_files_mem(t_shell *shell, int j)
{
	shell->cmds[j].infile = (t_io_files *)malloc(
			sizeof(t_io_files) * shell->cmds[j].infile_count);
	if (!shell->cmds[j].infile)
		return (1);
	shell->cmds[j].infile_count = 0;
	shell->cmds[j].outfile = (t_io_files *)malloc(
			sizeof(t_io_files) * shell->cmds[j].outfile_count);
	if (!shell->cmds[j].outfile)
		return (1);
	shell->cmds[j].outfile_count = 0;
	return (0);
}

int	io_files_alloc(char **tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) == 1)
			j++;
		if (isredir(tokens[i]) == IN || isredir(tokens[i]) == HEREDOC)
			shell->cmds[j].infile_count++;
		else if (isredir(tokens[i]) == OUT || isredir(tokens[i]) == APPOUT)
			shell->cmds[j].outfile_count++;
		i++;
	}
	j = 0;
	while (j < shell->n_cmds)
	{
		if (alloc_io_files_mem(shell, j) == 1)
			return (1);
		j++;
	}
	return (0);
}

int	alloc_arg_mem(t_shell *shell, int *arg_count, int *i, int *j)
{
	shell->cmds[*j].args = (char **)malloc(sizeof(char *) * *arg_count + 1);
	if (!shell->cmds[*j].args)
		return (1);
	shell->cmds[*j].args[*arg_count] = NULL;
	*arg_count = 0;
	*j += 1;
	*i += 1;
	return (0);
}

int	arg_alloc(char **tokens, t_shell *shell)
{
	int	i;
	int	j;
	int	arg_count;

	i = 0;
	j = 0;
	arg_count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (alloc_arg_mem(shell, &arg_count, &i, &j) == 1)
				return (1);
		}
		else if (isredir(tokens[i]) != NONE)
			i++;
		else if (i != 0)
			arg_count++;
		i++;
	}
	if (alloc_arg_mem(shell, &arg_count, &i, &j) == 1)
		return (1);
	return (0);
}

int	init_for_store(char **tokens, t_shell *shell)
{
	shell->cmds = (t_command *)malloc(
			sizeof(t_command) * count_cmd(tokens, shell));
	if (!shell->cmds)
		return (1);
	if (io_files_alloc(tokens, shell) == 1)
		return (1);
	if (arg_alloc(tokens, shell) == 1)
		return (1);
	return (0);
}
