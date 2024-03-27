/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:36:58 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/24 21:01:09 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	closed_quotes(char *line)
{
	int	i;
	int	count_d; // contador para cada quote
	int	count_s;

	i = 0;
	count_d = 0;
	count_s = 0;
	while (line[i])
	{
		// solo cuenta quotes que no esten dentro del otro tipo de quotes,
		// para ello se mira que el otro tipo sea par, significando que se ha cerrado.
		if (line[i] == '"' && count_s % 2 == 0)
			count_d++;
		else if (line[i] == '\'' && count_d % 2 == 0)
			count_s++;
		i++;
	}
	if (count_d % 2 == 0 && count_s % 2 == 0)
		return (0);
	return (1);
}

int	check_quotes(t_shell *shell)
{
	char	*new_line;
	char	*input;

	while(closed_quotes(shell->line_read) == 1) // comprobar si ya estan cerradas
	{
		new_line = ft_strjoin(shell->line_read, "\n");
		if (!new_line)
			return (1);
		free(shell->line_read);
		shell->line_read = new_line;
		input = readline(BCYN"> "RES);
		new_line = ft_strjoin(shell->line_read, input);
		if (!new_line)
			return (1);
		free(input);
		free(shell->line_read);
		shell->line_read = new_line;
	}
	return (0);
}