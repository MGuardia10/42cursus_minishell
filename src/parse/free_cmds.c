/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:24:47 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/27 10:56:42 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Frees the content of the input files for a specific command in the shell.
 * 
 * @param shell The shell structure.
 * @param i The index of the command in the shell's command array.
 */
void	free_infiles_content(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < shell->cmds[i].infile_count)
	{
		free(shell->cmds[i].infiles[j].filename);
		j++;
	}
}

/**
 * Frees the content of the output files for a specific command in the shell.
 *
 * @param shell The shell structure.
 * @param i The index of the command in the shell's command array.
 */
void	free_outfiles_content(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < shell->cmds[i].outfile_count)
	{
		free(shell->cmds[i].outfiles[j].filename);
		j++;
	}
}

/**
 * Frees the memory allocated for the commands in the shell structure.
 * 
 * @param shell The shell structure containing the commands to be freed.
 */
void	free_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < shell->n_cmds)
	{
		free_infiles_content(shell, i);
		free_outfiles_content(shell, i);
		while (j < shell->cmds[i].args_count)
		{
			free(shell->cmds[i].args[j]);
			j++;
		}
		j = 0;
		free(shell->cmds[i].infiles);
		free(shell->cmds[i].outfiles);
		free(shell->cmds[i].args);
		free(shell->cmds[i].exe);
		i++;
	}
	free(shell->cmds);
}
