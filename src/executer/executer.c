/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:52:43 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/22 17:35:12 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	simple_cmds(t_shell *shell)
{
	int	fd_in;
	int	fd_out;

	fd_in = manage_infiles(shell, shell->cmds[0].infiles, \
												shell->cmds[0].infile_count);
	if (fd_in < 0)
		return (1);
	fd_out = manage_outfiles(shell->cmds[0].outfiles, \
												shell->cmds[0].outfile_count);
	if (fd_out < 0)
		return (1);
	if (is_builtin(shell->cmds[0].exe))
		return (handle_builtins(shell, shell->cmds[0], fd_in, fd_out));
	return (handle_simple_commmands(shell, fd_in, fd_out));
}

int	compound_cmds(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	executer(t_shell *shell)
{
	if (shell->n_cmds == 1)
		return (simple_cmds(shell));
	else
		return (compound_cmds(shell));
	return (0);
}
