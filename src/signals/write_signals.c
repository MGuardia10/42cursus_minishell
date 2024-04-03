/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:10:11 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/31 13:02:05 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `write_signals` toggles the ECHOCTL flag in the terminal
 * settings based on the value of the `write_signal` parameter.
 * 
 * @param shell The `shell` parameter is a pointer to a structure of type
 * `t_shell`.
 * @param write_signal The `write_signal` parameter is a boolean value that
 * determines whether to enable or disable the `ECHOCTL` flag in the terminal
 * settings.
 */
void	write_signals(t_shell *shell, bool write_signal)
{
	struct termios	termios_p;

	if (tcgetattr(STDIN_FILENO, &termios_p) != 0)
		(perror("tcgetattr"), clean_exit(shell, EXIT_FAILURE));
	if (write_signal == false)
		termios_p.c_lflag &= ~ECHOCTL;
	else
		termios_p.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &termios_p) != 0)
		(perror("tcsetattr"), clean_exit(shell, EXIT_FAILURE));
}
