/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:54:17 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:32 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quotes_count(char *line, int *i)
{
	int	count;

	count = 0;
	if (line[*i] == '"')
	{
		*i += 1;
		count++;
		while (line[*i] && line[*i] != '"')
			*i += 1;
		*i += 1;
	}
	else if (line[*i] == '\'')
	{
		*i += 1;
		count++;
		while (line[*i] && line[*i] != '\'')
			*i += 1;
		*i += 1;
	}
	return (count);
}

int	redir_count(char *line, int *i)
{
	int	count;

	count = 0;
	if (line[*i] == '|')
	{
		count++;
		*i += 1;
	}
	else if (line[*i] == '>')
	{
		count++;
		if (line[*i + 1] == '>')
			*i += 1;
		*i += 1;
	}
	else if (line[*i] == '<')
	{
		count++;
		if (line[*i + 1] == '<')
			*i += 1;
		*i += 1;
	}
	return (count);
}

int	num_of_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (!is_special_char(line[i]))
		{
			count++;
			while (line[i] && !is_special_char(line[i]))
				i++;
		}
		if (line[i] == ' ')
		{
			while (line[i] && line[i] == ' ')
				i++;
		}
		count += quotes_count(line, &i);
		count += redir_count(line, &i);
	}
	return (count);
}
