/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_compound_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:03:34 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/30 09:47:11 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * It´s a helper function because of norminette. It sets up input and output
 * file descriptors forlast child when there are more than one command.
 * 
 * @param sh is a pointer to a structure of type `t_shell`.
 * @param fd The `fd` parameter is an integer array used to store file
 * descriptors for input and output files.
 * @param fd1 an integer array that is used to store file descriptors related to
 * the pipes.
 * @param i is an integer that represents the index of the command being
 * processed.
 */
static void	manage_io_files_helper(t_shell *sh, int *fd, int *fd1, int i)
{
	fd[0] = manage_infiles(sh->cmds[i].infiles, sh->cmds[i].infile_count, \
												fd1[0]);
	fd[1] = manage_outfiles(sh->cmds[i].outfiles, sh->cmds[i].outfile_count, \
												-1);
}

/**
 * handles input and output file management for a shell process based on the 
 * index position of the command being processed.
 * 
 * @param sh a pointer to a structure of type `t_shell`.
 * @param fd1 is a pointer to an integer that represents a file descriptor
 * for the first a pipe.
 * @param fd2 is a pointer to an integer that represents a file descriptor
 * for the second a pipe.
 * @param i an integer that represents the index of the current command being 
 * processed within the shell.
 * 
 * @return a pointer to an integer array `fd`. This array contains file
 * descriptors for input and output files.
 */
static int	*manage_io_files(t_shell *sh, int *fd1, int *fd2, int i)
{
	int	*fd;

	fd = ft_calloc(2, sizeof(int));
	if (!fd)
		exit(EXIT_FAILURE);
	if (i == 0)
	{
		close(fd1[0]);
		fd[0] = manage_infiles(sh->cmds[i].infiles, \
										sh->cmds[i].infile_count, -1);
		fd[1] = manage_outfiles(sh->cmds[i].outfiles, \
										sh->cmds[i].outfile_count, fd1[1]);
	}
	else if (i < sh->n_cmds - 1)
	{
		close(fd2[0]);
		fd[0] = manage_infiles(sh->cmds[i].infiles, \
										sh->cmds[i].infile_count, fd1[0]);
		fd[1] = manage_outfiles(sh->cmds[i].outfiles, \
										sh->cmds[i].outfile_count, fd2[1]);
	}
	else
		manage_io_files_helper(sh, fd, fd1, i);
	return (fd);
}

/**
 * The function `exec_child` executes a command in a child process with specified
 * input and output file descriptors.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param cmd a pointer to a structure of `t_command`. Contains ifo about the
 * command being processed.
 * @param fd_in an integer representing the fd for the input file. 
 * @param fd_out an integer representing the fd for the output file.
 */
static void	exec_child(t_shell *shell, t_command *cmd, int fd_in, int fd_out)
{
	char	*path;
	char	**argv;
	char	**envi;
	int		status;

	status = 0;
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO && fd_out != STDERR_FILENO)
		dup2(fd_out, STDOUT_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO && fd_out != STDERR_FILENO)
		close(fd_out);
	if (is_builtin(cmd->exe) == true)
		exit(exec_builtin(shell, cmd->exe, cmd->args, cmd->args_count));
	path = find_path(shell, cmd->exe, shell->envi, &status);
	if (!path)
		exit(status);
	argv = create_argv(*cmd);
	envi = envi_to_arr(shell->envi);
	if (!argv || !envi)
		exit(EXIT_FAILURE);
	execve(path, argv, envi);
	(perror("minishell"), exit(127));
}

/**
 * creates a child process, manages input/output files, and executes a command
 * in the child process.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param fd1 is a pointer to an integer that represents a file descriptor
 * for the first a pipe.
 * @param fd2 is a pointer to an integer that represents a file descriptor
 * for the second a pipe.
 * @param i an integer that represents the index of the command being processed.
 */
void	create_child(t_shell *shell, int *fd1, int *fd2, int i)
{
	t_command	*cmd;
	int			*io_files;

	shell->last_pid = fork();
	if (shell->last_pid < 0)
		(perror("fork"), clean_exit(shell, EXIT_FAILURE));
	if (shell->last_pid == 0)
	{
		io_files = manage_io_files(shell, fd1, fd2, i);
		if (io_files[0] < 0 || io_files[1] < 0)
			exit(EXIT_FAILURE);
		cmd = &shell->cmds[i];
		exec_child(shell, cmd, io_files[0], io_files[1]);
	}
}

/**
 * waits for all child processes to finish and returns the exit status of the
 * last child process that was specified.
 * 
 * @param last_pid an integer that is the process ID of the last child process.
 * 
 * @return an integer representing the exit status of the last child process.
 */
int	wait_all_childs(int last_pid)
{
	pid_t	curr_child;
	int		status_child;
	int		exit_code;

	curr_child = 0;
	status_child = 0;
	exit_code = 0;
	while (1)
	{
		curr_child = waitpid(-1, &status_child, 0);
		if (curr_child <= 0)
			break ;
		if (curr_child == last_pid && WIFEXITED(status_child))
			exit_code = WEXITSTATUS(status_child);
	}
	return (exit_code);
}
