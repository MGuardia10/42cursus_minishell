/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:02:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/27 13:15:52 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/inc/libft.h"
#include "../libft/inc/colors.h"

// void	leaks(void)
// {
// 	system("leaks -q minishell");
// }

int	manage_status(int status)
{
	t_sig_mode new_status;
	
	// printf("g_status --> %d\n", g_signal_status);
	if (g_signal_status != INTERACTIVE && g_signal_status != NON_INTERACTIVE \
											&& status != 0)
	{
		new_status = g_signal_status;
		g_signal_status = INTERACTIVE;
		return (new_status);
	}
	g_signal_status = INTERACTIVE;
	return (status);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	(void)argv;

	if (argc != 1)
		return (ft_putstr_fd(BRED"No args required\n"RES, 2), EXIT_FAILURE);
	ft_memset(&shell, 0, sizeof(t_shell));
	shell.stdin_dup = dup(STDIN_FILENO);
	shell.stdout_dup = dup(STDOUT_FILENO);
	if (shell.stdin_dup < 0 || shell.stdout_dup < 0)
		return (perror("minishell: dup"), EXIT_FAILURE);
	if (create_env_list(&shell, env))
		return (ft_lstclear((t_list **)&shell.envi, free_env), EXIT_FAILURE);
	// atexit(leaks);
	while (1)
	{
		signal_handler(ft_sigint, SIG_IGN);
		shell.line_read = readline("Minishell $ "RES);
		if (!shell.line_read)
		{
			// rl_replace_line("", 0);
			printf("exit\n");
			if (g_signal_status == SIGINT_FATHER)
				clean_exit(&shell, EXIT_FAILURE);
			clean_exit(&shell, EXIT_FAILURE); // shell.exit_status
		}
		add_history(shell.line_read); // hace
		if (init_line(&shell))
		{
			free(shell.line_read);
			shell.exit_status = 1;
			continue ;
		}
		shell.exit_status = manage_status(executer(&shell));
		printf("\nexit status --> [ %d ]\n", shell.exit_status);
		free_cmds(&shell);
		free(shell.line_read);
	}
	return (0);
}
