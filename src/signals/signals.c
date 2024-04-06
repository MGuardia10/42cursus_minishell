/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:06:05 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/06 13:31:38 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `ft_sigint_heredoc` handles the SIGINT signal in a
 * non-interactive mode by setting a specific signal status and performing
 * certain actions.
 * 
 * @param signal an integer representing the signal that triggered the signal
 * handler.
 */
void	ft_sigint_heredoc(int signal)
{
	(void)signal;
	g_signal_status = SIGINT_HD;
	ioctl(STDIN_FILENO, TIOCSTI, "\r");
}

/**
 * The function `ft_sigint_child` is a signal handler for the SIGINT signal in a
 * child process.
 * 
 * @param signal an integer that represents the signal that triggered the signal
 * handler. Not used during the funcion.
 */
void	ft_sigint_child(int signal)
{
	(void)signal;
	g_signal_status = SIGINT_CHILD;
	ft_putchar_fd('\n', STDERR_FILENO);
}

/**
 * The function `ft_sigint` handles the SIGINT signal when shell is interactive.
 * 
 * @param signal an integer that represents the signal number that triggered the
 * signal handler. Not used during the function.
 */
void	ft_sigint(int signal)
{
	(void)signal;
	g_signal_status = SIGINT_FATHER;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
//	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * The function `ft_sigquit` handles the SIGQUIT signal by setting a global
 * signal status and printing a message to the standard error.
 * 
 * @param signal an integer that represents the signal number that triggered
 * the signal handler.
 */
void	ft_sigquit(int signal)
{
	(void)signal;
	g_signal_status = SIGQUIT_CHILD;
	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

/**
 * The function `signal_handler` sets up signal handlers for SIGINT (CTRL + C)
 * and SIGQUIT (CTRL + 4 or CTRL + \).
 * 
 * @param sigint_func The `sigint_func` parameter is a function pointer that
 * specifies the signal handler function to be called when the `SIGINT` signal
 * (interrupt signal) is received.
 * @param sigquit_func The `sigquit_func` parameter is a function pointer that
 * points to the function that will be called when the `SIGQUIT` signal is
 * received.
 */
void	signal_handler(sig_t sigint_func, sig_t sigquit_func)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_func;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sigquit_func;
	sigaction(SIGQUIT, &sa, NULL);
}
