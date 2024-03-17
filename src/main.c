/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:02:41 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/17 15:36:37 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/inc/libft.h"
#include "../libft/inc/colors.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

int	main(void)
{
	t_shell	shell;
	
	atexit(leaks);
	while (1)
	{
		shell.line_read = readline(BCYN"Minishell $ "RES);
		if (!shell.line_read || shell.line_read[0] == '\0')
			continue ;
		init_line(&shell);
		free(shell.line_read);
		return (0);
	}
	return (0);
}
