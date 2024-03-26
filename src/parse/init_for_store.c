/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_store.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:27:12 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/25 14:00:36 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int count_cmd(char **tokens, t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) == 1)
			count++;
		i++;
	}
	shell->n_cmds = count;
	return (count);
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
		shell->cmds[j].infile = (t_io_files *)malloc(sizeof(t_io_files) * shell->cmds[j].infile_count); 
		if (!shell->cmds[j].infile)
			return (1);
		shell->cmds[j].infile_count = 0;
		shell->cmds[j].outfile = (t_io_files *)malloc(sizeof(t_io_files) * shell->cmds[j].outfile_count);
		if (!shell->cmds[j].outfile)
			return (1);
		shell->cmds[j].outfile_count = 0;
		j++;
	}
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
		if ((ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) == 1))
		{
			shell->cmds[j].args = (char **)malloc(sizeof(char *) * arg_count + 1);
			if (!shell->cmds[j].args)
				return (1);
			shell->cmds[j].args[arg_count] = NULL;
			arg_count = 0;
			j++;
			i++;
		}
		else if (isredir(tokens[i]) != NONE)
			i++;
		else if (i != 0)
			arg_count++;
		i++;
	}
	shell->cmds[j].args = (char **)malloc(sizeof(char *) * arg_count + 1);
	if (!shell->cmds[j].args)
		return (1);
	shell->cmds[j].args[arg_count] = NULL;
	return (0);
}

int	init_for_store(char **tokens, t_shell *shell)
{
	shell->cmds = (t_command *)malloc(sizeof(t_command) * count_cmd(tokens, shell)); // ACORDARSE LIBERAR COMANDOS + TODO SU CONTENIDO
	if (!shell->cmds)
		return (1);
	if (io_files_alloc(tokens, shell) == 1)
		return (1);
	if (arg_alloc(tokens, shell) == 1)
		return (1);
	return(0);
}