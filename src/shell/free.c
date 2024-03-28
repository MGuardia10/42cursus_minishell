/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:24:47 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/28 12:52:39 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Frees the content of the input files for a specific command in the shell.
 * 
 * @param shell The shell structure.
 * @param i The index of the command in the shell's command array.
 */
void	free_infiles(t_command *cmd)
{
	int	i;

	if (!cmd->infiles)
		return ;
	i = 0;
	while (i < cmd->infile_count)
	{
		free(cmd->infiles[i].filename);
		if (cmd->infiles[i].redir == HEREDOC)
		{
			if (cmd->infiles[i].path)
			{
				if (unlink(cmd->infiles[i].path) != 0)
					perror("unlink");
				free(cmd->infiles[i].path);
			}
		}
		i++;
	}
	free(cmd->infiles);
}

/**
 * Frees the content of the output files for a specific command in the shell.
 *
 * @param shell The shell structure.
 * @param i The index of the command in the shell's command array.
 */
void	free_outfiles(t_command *cmd)
{
	int	i;

	if (!cmd->outfiles)
		return ;
	i = 0;
	while (i < cmd->outfile_count)
		free(cmd->outfiles[i++].filename);
	free(cmd->outfiles);
}

/**
 * The function `free_args` is used to free the memory allocated for the
 * arguments of a command structure.
 * 
 * @param cmd The parameter `cmd` is a pointer to a `t_command` struct.
 * 
 * @return If the `cmd->args` is `NULL`, then the function will return without
 * doing anything.
 */
void	free_args(t_command *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (i < cmd->args_count)
		free(cmd->args[i++]);
	free(cmd->args);
}

/**
 * Frees the memory allocated for the commands in the shell structure.
 * 
 * @param shell The shell structure containing the commands to be freed.
 */
void	free_cmds(t_shell *shell)
{
	int	i;

	if (!shell->cmds)
		return ;
	i = 0;
	while (i < shell->n_cmds)
	{
		if (shell->cmds[i].exe)
			free(shell->cmds[i].exe);
		free_infiles(&shell->cmds[i]);
		free_outfiles(&shell->cmds[i]);
		free_args(&shell->cmds[i]);
		i++;
	}
	free(shell->cmds);
}

/**
 * The function `free_shell` deallocates memory used by a shell structure.
 * 
 * @param shell The `shell` parameter is a pointer to a structure of type
 * `t_shell`.
 */
void	free_shell(t_shell *shell)
{
	if (shell->line_read)
		free(shell->line_read);
	ft_lstclear((t_list **)&shell->envi, free_env);
	free_cmds(shell);
	if (shell->home)
		free(shell->home);
}
