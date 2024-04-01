/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:50:28 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/01 12:32:18 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * checks the command provided and executes the corresponding built-in function.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param cmd a string that represents the command the user has entered.
 * @param args an array of string that represents the arguments of the command.
 * 
 * @return The function is returning an integer value. On success, the return
 * value is 0, otherwise the return value will be a number > 0 and < 256.
 */
int	exec_builtin(t_shell *shell, char *cmd, char **args, int args_count)
{
	if (!cmd)
		return (0);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell, shell->envi, args[0]));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(shell));
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(shell, &shell->envi, args));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(&shell->envi, args));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(&shell->envi, args[0]));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(shell, args, args_count));
	return (1);
}

/**
 * The function `handle_builtins` manages built-in commands in a shell, handling
 * input and output redirection.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param cmd a structure that contains info about the command to be executed.
 * @param fd_in represents the file descriptor for the input file or stream that
 * the built-in command will read from. It is used to redirect the standard
 * input (stdin) for the command being executed.
 * @param fd_out represents the file descriptor for the output file where the
 * standard output of the command should be redirected. It is used to redirect
 * the standard output (stdout) for the command being executed.
 * 
 * @return an integer that represents the result of executing the built-in
 * command.
 */
int	handle_builtins(t_shell *shell, t_command *cmd)
{
	int	fd_in;
	int	fd_out;
	int	exit_code;

	fd_in = manage_infiles(cmd->infiles, cmd->infile_count, -1);
	if (fd_in < 0)
		return (1);
	fd_out = manage_outfiles(cmd->outfiles, cmd->outfile_count, -1);
	if (fd_out < 0)
		return (1);
	shell->infile_dup = dup2(fd_in, STDIN_FILENO);
	shell->outfile_dup = dup2(fd_out, STDOUT_FILENO);
	if (shell->outfile_dup < 0 || shell->infile_dup < 0)
	{
		close(fd_in); 
		close(fd_out);
		perror("dup2");
		clean_exit(shell, EXIT_FAILURE);
	}
	exit_code = exec_builtin(shell, cmd->exe, cmd->args, cmd->args_count);
	close(fd_in);
	close(fd_out);
	dup2(shell->stdin_dup, shell->infile_dup);
	dup2(shell->stdout_dup, shell->outfile_dup);
	return (exit_code);
}
