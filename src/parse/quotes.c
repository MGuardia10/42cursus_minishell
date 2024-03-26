/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:36:58 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:19 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	ft_fprintf(
		STDERR_FILENO,
		"minishell: syntax error: unable to locate closing quotation.\n");
	return (1);
}
