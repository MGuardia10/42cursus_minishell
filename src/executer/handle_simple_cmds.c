/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:12:07 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/28 12:55:54 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `child_task` executes a command with specified input and output
 * file descriptors in a shell environment.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param fd_in a integer that represents the file descriptor for infiles.
 * @param fd_out a integer that represents the file descriptor for outfiles.
 */
void	child_task(t_shell *shell, int fd_in, int fd_out)
{
	char	*path;
	char	**argv;
	char	**envi;
	int		status;

	status = 0;
	path = find_path(shell, shell->cmds->exe, shell->envi, &status);
	if (!path)
		exit(status);
	argv = create_argv(shell->cmds[0]);
	if (!argv)
		exit(EXIT_FAILURE);
	envi = envi_to_arr(shell->envi);
	if (!envi)
		exit(EXIT_FAILURE);
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO && fd_out != STDERR_FILENO)
		dup2(fd_out, STDOUT_FILENO);
	execve(path, argv, envi);
	perror("minishell");
	exit(127);
}

/**
 * The function forks a child process to execute a command and waits for it to
 * finish before returning the exit status.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param fd_in an integer that represents a file descriptor for the infile,
 * used to read input from a file.
 * @param fd_out an integer that represents a file descriptor for the outfile
 * where the child process should write its output.
 * 
 * @return the exit status of the child process. On success it returns 0. On
 * failure it returns a number > 0 && < 256.
 */
int	handle_simple_commmands(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		wstatus;

	pid = fork();
	if (pid < 0)
		(perror("fork"), clean_exit(shell, EXIT_FAILURE));
	if (pid == 0)
	{
		fd_in = manage_infiles(cmd->infiles, cmd->infile_count, -1);
		if (fd_in < 0)
			exit(EXIT_FAILURE);
		fd_out = manage_outfiles(cmd->outfiles, cmd->outfile_count, -1);
		if (fd_out < 0)
			exit(EXIT_FAILURE);
		child_task(shell, fd_in, fd_out);
	}
	if (pid > 0)
		wait(&wstatus);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (1);
}
