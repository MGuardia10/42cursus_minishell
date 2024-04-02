/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:39:14 by raalonso          #+#    #+#             */
/*   Updated: 2024/04/02 19:51:20 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*match_quotes(char *token, int f)
{
	char	*aux = NULL;

	if (token[0] == '"' || token[0] == '\'')
	{
		if (token[ft_strlen(token) - 1] == '"'
			|| token[ft_strlen(token) - 1] == '\'')
		{
			aux = ft_substr(token, 0, ft_strlen(token) - 1);
			if (!aux)
				return (NULL);
			if (token[0] == '"')
			{
				free (token);
				token = ft_strjoin(aux, "\"");
			}
			else if (token[0] == '\'')
			{
				free (token);
				token = ft_strjoin(aux, "'");
			}
			if (!token)
				return (NULL);
			free(aux);
		}
		else
		{
			if (token[0] == '"')
				aux = ft_strjoin(token, "\"");
			else if (token[0] == '\'')
				aux = ft_strjoin(token, "'");
			if (!aux)
				return (NULL);
			free (token);
			token = aux;
		}
	}
	if (f == 0)
	{
		aux = ft_strtrim(token, "\"'");
		if (!aux)
			return (NULL);
		free(token);
		token = aux;
	}
	printf("\n%s\n", token);
	return (token);
}

void	join_word(char *line, char **tokens, int *i, int j)
{
	char	*aux;
	char	*new_part;
	int		last;

	last = *i;
	aux = ft_substr(tokens[j], 0, ft_strlen(tokens[j]) - 1);
	if (!aux)
		exit(1);
	free(tokens[j]);
	tokens[j] = aux;
	while (line[*i] && !is_special_char(line[*i]))
		*i += 1;
	new_part = ft_substr(line, last, (*i - last) + 1);
	if (!new_part)
		exit(1);
	aux = ft_strjoin(tokens[j], new_part);
	if (!aux)
		exit(1);
	free(tokens[j]);
	free(new_part);
	tokens[j] = aux;
}

char	*check_next_quotes(char *line, char **tokens, int *i, int j)
{
	int		f;

	f = 0;
	*i += 1;
	// poner yo aqui las comillas a los que vengan sin (words)
	// para distingir pipes
	while (line[*i] && !is_special_char_two(line[*i]))
	{
		if (line[*i] && (line[*i] == '"' || line[*i] == '\''))
		{
			f = 1;
			*i += 1;
		}
		if (line[*i] && !is_special_char(line[*i]))
			join_word(line, tokens, i, j);
	}
	tokens[j] = match_quotes(tokens[j], f);
	if (!tokens[j])
		return (NULL);
	return (tokens[j]);
}
