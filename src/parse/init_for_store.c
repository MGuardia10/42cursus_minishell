/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_store.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:27:12 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/30 12:11:08 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Allocates memory for input and output files in the shell command structure.
 * 
 * @param shell The shell structure.
 * @param j The index of the command in the shell structure.
 * @return Returns 0 on success, 1 on failure.
 */
int	alloc_io_files_mem(t_shell *shell, int j)
{
	shell->cmds[j].infiles = (t_io_files *)malloc(
			sizeof(t_io_files) * shell->cmds[j].infile_count);
	if (!shell->cmds[j].infiles)
		return (1);
	shell->cmds[j].infile_count = 0;
	shell->cmds[j].outfiles = (t_io_files *)malloc(
			sizeof(t_io_files) * shell->cmds[j].outfile_count);
	if (!shell->cmds[j].outfiles)
		return (1);
	shell->cmds[j].outfile_count = 0;
	return (0);
}

/**
 * Allocates memory for input and output files in the shell structure.
 * Counts the number of input and output files for each command.
 * 
 * @param tokens The array of tokens representing the command line input.
 * @param shell The shell structure containing information about the commands.
 * @return 0 if successful, 1 if memory allocation fails.
 */
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

/**
 * Allocates memory for storing command arguments in the shell structure.
 * 
 * @param shell The shell structure.
 * @param arg_count Pointer to the argument count.
 * @param i Pointer to the variable i.
 * @param j Pointer to the variable j.
 * @return Returns 0 if memory allocation is successful, 1 otherwise.
 */
int	alloc_arg_mem(t_shell *shell, int *arg_count, int *i, int *j)
{
	shell->cmds[*j].args = (char **)malloc(sizeof(char *) * (*arg_count + 1));
	if (!shell->cmds[*j].args)
		return (1);
	shell->cmds[*j].args[*arg_count] = NULL;
	*arg_count = 0;
	*j += 1;
	*i += 1;
	return (0);
}

/**
 * @brief Allocates memory for storing arguments in the shell structure.
 * 
 * This function counts the number of arguments in the given tokens array and
 * allocates memory in the shell structure to store the arguments. It skips
 * over redirection symbols and increments the argument count for each token
 * that is not a redirection symbol or the first token in the array.
 * 
 * @param tokens The array of tokens to count the arguments from.
 * @param shell The shell structure to allocate memory in.
 * @return Returns 0 on success, 1 on failure.
 */
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

/**
 * Initializes the necessary data structures for storing parsed tokens 
 * in the shell.
 * 
 * @param tokens The array of tokens to be parsed.
 * @param shell The shell structure to store the parsed data.
 * @return Returns 0 on success, 1 on failure.
 */
int	init_for_store(char **tokens, t_shell *shell)
{
	shell->n_cmds = count_cmd(tokens);
	shell->cmds = ft_calloc(shell->n_cmds, sizeof(t_command));
	if (!shell->cmds)
		return (1);
	if (io_files_alloc(tokens, shell) == 1)
		return (1);
	if (arg_alloc(tokens, shell) == 1)
		return (1);
	return (0);
}
