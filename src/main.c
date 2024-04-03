/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:02:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/03 21:47:56 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	if (init_shell(&shell, argc, argv, env))
		return (EXIT_FAILURE);
	while (1)
	{
		signal_handler(ft_sigint, SIG_IGN);
		write_signals(&shell, false);
		manage_input(&shell);
		if (init_line(&shell))
		{
			free(shell.line_read);
			shell.exit_status = 1;
			continue ;
		}
		shell.exit_status = manage_exit_status(executer(&shell));
		reset_shell(&shell);
	}
}
