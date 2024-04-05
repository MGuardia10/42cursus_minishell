/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:52:43 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/05 13:51:05 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `simple_cmds` manages input and output files for a shell command
 * and then either handles built-in commands or simple commands.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * 
 * @return the result of either `handle_builtins` function if the command is a
 * built-in command, or `handle_simple_commmands` function if it's not built-in.
 */
static int	simple_cmds(t_shell *shell)
{
	if (is_builtin(shell->cmds[0].exe))
		return (handle_builtins(shell, &shell->cmds[0]));
	signal_handler(ft_sigint_child, ft_sigquit);
	return (handle_simple_commmands(shell, &shell->cmds[0]));
}

/**
 * The function `compound_cmds` creates n_cmds child processes to execute a
 * series of commands in a shell, using pipes for communication between them.
 * 		====> pipefd[0] - READ END
 * 		====> pipefd[1] - WRITE END
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param n_cmds represents the total number of commands to be executed.
 * 
 * @return The function `compound_cmds` is returning the result of the
 * `wait_all_childs` function, which is the return value of the last child
 * process that was executed.
 */
static int	compound_cmds(t_shell *shell, int n_cmds)
{
	int	pipefd_1[2];
	int	pipefd_2[2];
	int	i;

	if (pipe(pipefd_1) != 0)
		(perror("pipe"), clean_exit(shell, EXIT_FAILURE));
	create_child(shell, pipefd_1, pipefd_2, 0);
	close(pipefd_1[1]);
	i = 1;
	while (i < n_cmds - 1)
	{
		if (pipe(pipefd_2) != 0)
			(perror("pipe"), clean_exit(shell, EXIT_FAILURE));
		create_child(shell, pipefd_1, pipefd_2, i);
		close(pipefd_1[0]);
		close(pipefd_2[1]);
		pipefd_1[0] = pipefd_2[0];
		i++;
	}
	create_child(shell, pipefd_1, pipefd_2, i);
	close(pipefd_1[0]);
	return (wait_all_childs(shell->last_pid));
}

/**
 * Determines whether to execute simple commands or compound commands based on
 * the number of commands in shell structure.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * 
 * @return executer function is returning the result of either the `simple_cmds`
 * function or the `compound_cmds` function.
 */
int	executer(t_shell *shell)
{
	if (resolve_heredocs(shell, shell->cmds, shell->n_cmds))
		return (1);
	write_signals(shell, true);
	if (shell->n_cmds == 1)
		return (simple_cmds(shell));
	signal_handler(ft_sigint_child, ft_sigquit);
	return (compound_cmds(shell, shell->n_cmds));
}
