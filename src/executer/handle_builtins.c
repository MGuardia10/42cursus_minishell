/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:50:28 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/22 11:11:02 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_builtin(t_shell *shell, char *cmd, char **args)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell->envi, shell->home, args[0]));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(&shell->envi, args));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(&shell->envi, args));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(&shell->envi, args));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(shell, args));
	return (1);
}

int	handle_builtins(t_shell *shell, t_command cmd, int fd_in, int fd_out)
{
	shell->infile_dup = dup2(fd_in, STDIN_FILENO);
	shell->outfile_dup = dup2(fd_out, STDOUT_FILENO);
	if (shell->outfile_dup < 0 || shell->infile_dup < 0)
		return (close(fd_in), close(fd_out), perror("minishell: dup2"), 1);
	shell->exit_status = exec_builtin(shell, cmd.exe, cmd.args);
	close(fd_in);
	close(fd_out);
	dup2(shell->stdin_dup, shell->infile_dup);
	dup2(shell->stdout_dup, shell->outfile_dup);
	return (shell->exit_status);
}
