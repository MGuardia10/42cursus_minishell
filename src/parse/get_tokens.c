/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:25:34 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 15:35:07 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_word(char **tokens, char *line, int *i, int *j)
{
	int	last;

	last = *i;
	while (line[*i] && !is_special_char(line[*i]))
		*i += 1;
	tokens[*j] = ft_substr(line, last, *i - last);
	if (!tokens)
		return (1);
	*j += 1;
	return (0);
}

char	**get_tokens(char *line)
{
	int		i;
	int		j;
	char	**tokens;

	i = 0;
	j = 0;
	tokens = (char **)malloc(sizeof(char *) * (num_of_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		if (!is_special_char(line[i]))
		{
			if (get_word(tokens, line, &i, &j) == 1)
				return (NULL);
		}
		else
		{
			if (handle_special_char(line, tokens, &i, &j) == 1)
				return (NULL);
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

//