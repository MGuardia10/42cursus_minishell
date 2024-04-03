/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:25:40 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/02 16:40:28 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/inc/colors.h"

/**
 * The function `init_shell` initializes a shell structure.
 * 
 * @param shell The `shell` parameter is a pointer to a structure of type
 * `t_shell`.
 * @param argc is an integer that represents the argument count of the program.
 * @param argv is an array of strings that represents the arguments of the
 * program.
 * @param env is a pointer to an array of strings that represent the
 * environment variables.
 * 
 * @return The function is returning an integer value: 1 when there is an error
 * or argc != 1, and 0 when shell structure and environment list are
 * successfully created.
 * 
 */
int	init_shell(t_shell *shell, int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd(BRED"No args required\n"RES, STDERR_FILENO), 1);
	ft_memset(shell, 0, sizeof(t_shell));
	shell->stdin_dup = dup(STDIN_FILENO);
	shell->stdout_dup = dup(STDOUT_FILENO);
	if (shell->stdin_dup < 0 || shell->stdout_dup < 0)
		return (perror("minishell: dup"), 1);
	if (create_env_list(shell, env))
		return (ft_lstclear((t_list **)&shell->envi, free_env), 1);
	return (0);
}

/**
 * reads user input for a shell program and handles different exit statuses.
 * 
 * @param shell is a pointer to a structure named `t_shell`.
 */
void	manage_input(t_shell *shell)
{
	if (shell->exit_status == 0)
		shell->line_read = readline(BHCYN"😄 Minishell $ "RES);
	else
		shell->line_read = readline(BHRED"🤬 Minishell $ "RES);
	if (!shell->line_read)
	{
		rl_replace_line("", 0);
		printf("exit\n");
		if (g_signal_status == SIGINT_FATHER)
			exit(EXIT_FAILURE);
		exit(shell->exit_status);
	}
	if (ft_strlen(shell->line_read) > 0)
		add_history(shell->line_read);
}

/**
 * returns a new status based on the input status and the global signal status.
 * 
 * @param status The `status` parameter represents the exit status of a process.
 * It is typically a value returned by a program to indicate its termination
 * status. A status of 0 indicates successful execution, while non-zero values
 * indicate an error.
 * 
 * @return The function `manage_exit_status` is returning the value of
 `new_status`.
 */
int	manage_exit_status(int status)
{
	int	new_status;

	if (g_signal_status != INTERACTIVE && status != 0)
		new_status = g_signal_status;
	else
		new_status = status;
	g_signal_status = INTERACTIVE;
	return (new_status);
}

/**
 * The function `reset_shell` frees memory allocated for the shell's line read
 * and commands.
 * 
 * @param shell The `shell` parameter is a pointer to a `t_shell` struct.
 */
void	reset_shell(t_shell *shell)
{
	if (shell->line_read)
		free(shell->line_read);
	free_cmds(shell);
}
