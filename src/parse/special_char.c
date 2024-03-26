/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:39:53 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:22 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quotes_token(char *line, char **cmds, int *i, int *j)
{
	int	last;

	last = 0;
	if (line[*i] == '"')
	{
		*i += 1;
		last = *i;
		while (line[*i] && line[*i] != '"')
			*i += 1;
	}
	else if (line[*i] == '\'')
	{
		*i += 1;
		last = *i;
		while (line[*i] && line[*i] != '\'')
			*i += 1;
	}
	cmds[*j] = ft_substr(line, last - 1, (*i - last) + 2);
	if (!cmds[*j])
		return (1);
	*i += 1;
	*j += 1;
	return (0);
}

int	infile_token(char *line, char **tokens, int *i, int *j)
{
	int	last;

	last = *i;
	if (line[*i + 1] == '<')
	{
		*i += 2;
		tokens[*j] = ft_substr(line, last, *i - last);
		if (!tokens[*j])
			return (1);
		*j += 1;
	}
	else
	{
		*i += 1;
		tokens[*j] = ft_substr(line, last, *i - last);
		if (!tokens[*j])
			return (1);
		*j += 1;
	}
	return (0);
}

int	outfile_token(char *line, char **tokens, int *i, int *j)
{
	int	last;

	last = *i;
	if (line[*i + 1] == '>')
	{
		*i += 2;
		tokens[*j] = ft_substr(line, last, *i - last);
		if (!tokens[*j])
			return (1);
		*j += 1;
	}
	else
	{
		*i += 1;
		tokens[*j] = ft_substr(line, last, *i - last);
		if (!tokens[*j])
			return (1);
		*j += 1;
	}
	return (0);
}

int	pipe_token(char *line, char **tokens, int *i, int *j)
{
	int	last;

	last = *i;
	*i += 1;
	tokens[*j] = ft_substr(line, last, *i - last);
	if (!tokens[*j])
		return (1);
	*j += 1;
	return (0);
}

int	handle_special_char(char *line, char **tokens, int *i, int *j)
{
	if (line[*i] == '"' || line[*i] == '\'')
	{
		if (quotes_token(line, tokens, i, j) == 1)
			return (1);
	}
	else if (line[*i] == '|')
	{
		if (pipe_token(line, tokens, i, j) == 1)
			return (1);
	}
	else if (line[*i] == '>')
	{
		if (outfile_token(line, tokens, i, j) == 1)
			return (1);
	}
	else if (line[*i] == '<')
	{
		if (infile_token(line, tokens, i, j) == 1)
			return (1);
	}
	else if (line[*i] == ' ')
		while (line[*i] == ' ')
			*i += 1;
	return (0);
}
