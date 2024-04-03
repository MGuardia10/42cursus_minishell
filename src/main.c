/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:02:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/03 18:56:23 by raalonso         ###   ########.fr       */
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
