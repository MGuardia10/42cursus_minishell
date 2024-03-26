/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:25:34 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/25 14:30:19 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_tokens(char *line)
{
	int		i;
	int		j;
	int		last;
	char	**tokens;

	i = 0;
	j = 0;
	last = 0;
	tokens = (char **)malloc(sizeof(char *) * (num_of_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		if (!is_special_char(line[i]))
		{
			last = i;
			while (line[i] && !is_special_char(line[i]))
				i++;
			tokens[j] = ft_substr(line, last, i - last);
			if (!tokens)
				return (NULL);
			j++;
		}
		else
		{
			if (handle_special_char(line, tokens, &i, &j) == 1)
				return (NULL);
		}
	}
	tokens[j] = NULL;
	/*int l = 0;
	printf("TOKENS: \n");
	while (tokens[l])
	{
		printf("\n%s\n", tokens[l]);
		l++;	
	}*/
	return (tokens);
}
