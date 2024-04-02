/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:54:17 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/02 18:34:04 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Counts the number of words in a given line starting from a specific index.
 *
 * @param line The input line to count words from.
 * @param i The starting index to count words from.
 * @return The number of words found in the line.
 */
int	words_count(char *line, int *i)
{
	int	count;

	count = 0;
	if (line[*i] && !is_special_char_two(line[*i]))
	{
		count++;
		while (line[*i] && !is_special_char_two(line[*i]))
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
		if (line[i] == ' ')
		{
			while (line[i] && line[i] == ' ')
				i++;
		}
		count += words_count(line, &i);
		count += redir_count(line, &i);
	}
	return (count);
}
