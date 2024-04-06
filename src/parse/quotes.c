/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:36:58 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/06 20:38:17 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Checks if the given line has balanced quotes.
 * 
 * @param line The line to check for balanced quotes.
 * @return 0 if the line has balanced quotes, 1 otherwise.
 */
int	check_quotes(char *line)
{
	int	i;
	int	count_d;
	int	count_s;

	i = 0;
	count_d = 0;
	count_s = 0;
	while (line[i])
	{
		if (line[i] == '"' && count_s % 2 == 0)
			count_d++;
		else if (line[i] == '\'' && count_d % 2 == 0)
			count_s++;
		i++;
	}
	if (count_d % 2 == 0 && count_s % 2 == 0)
		return (0);
	ft_dprintf(
		STDERR_FILENO,
		"minishell: syntax error: unable to locate closing quotation.\n");
	return (1);
}
