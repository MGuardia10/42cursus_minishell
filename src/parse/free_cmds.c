/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:24:47 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:06 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_infiles_content(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < shell->cmds[i].infile_count)
	{
		free(shell->cmds[i].infile[j].filename);
		j++;
	}
}

void	free_outfiles_content(t_shell *shell, int i)
{
	int	j;

	j = 0;
	while (j < shell->cmds[i].outfile_count)
	{
		free(shell->cmds[i].outfile[j].filename);
		j++;
	}
}

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
		free(shell->cmds[i].infile);
		free(shell->cmds[i].outfile);
		free(shell->cmds[i].args);
		free(shell->cmds[i].exe);
		i++;
	}
	free(shell->cmds);
}
