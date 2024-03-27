/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:54:17 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/27 00:50:19 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Counts the number of quotes in a given line.
 *
 * @param line The input line to count quotes from.
 * @param i    The current index in the line.
 * @return     The number of quotes found in the line.
 */
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

/**
 * Counts the number of redirection symbols in a given line.
 *
 * @param line The line to count the redirection symbols in.
 * @param i    A pointer to the current index in the line.
 * @return     The number of redirection symbols found.
 */
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

/**
 * Counts the number of tokens in a given line.
 *
 * @param line The input line to count tokens from.
 * @return The number of tokens found in the line.
 */
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
