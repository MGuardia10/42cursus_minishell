/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:23:48 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/03 21:48:41 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Determines the type of redirection based on the given token.
 *
 * @param token The token to check for redirection.
 * @return The type of redirection (OUT, IN, APPOUT, HEREDOC, or NONE).
 */
t_redir	isredir(char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (OUT);
	else if (ft_strcmp(token, "<") == 0)
		return (IN);
	else if (ft_strcmp(token, ">>") == 0)
		return (APPOUT);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	return (NONE);
}

/**
 * Checks for unexpected tokens in the given array of tokens.
 * An unexpected token is defined as a redirection symbol or a pipe symbol
 * that is not in the expected position.
 *
 * @param tokens The array of tokens to check.
 * @return 1 if there are unexpected tokens, 0 otherwise.
 */
int	unexpected_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (isredir(tokens[i]) != NONE || ft_strcmp(tokens[i], "|") == 0)
		{
			if ((isredir(tokens[i + 1]) != NONE
					|| ft_strcmp(tokens[i + 1], "|") == 0)
				|| (ft_strcmp(tokens[i], "|") == 0 && i == 0))
			{
				ft_fprintf(
					STDERR_FILENO,
					"minishell: syntax error near unexpected token `%s'.\n",
					tokens[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

/**
 * Counts the number of commands in an array of tokens.
 * A command is determined by the presence of the '|' character.
 *
 * @param tokens The array of tokens.
 * @param shell The shell structure.
 * @return The number of commands found.
 */
int	count_cmd(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) == 1)
			count++;
		i++;
	}
	return (count);
}
