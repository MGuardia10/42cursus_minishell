/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:20:44 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 23:53:25 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	store_tokens(char **tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (isredir(tokens[i]) != NONE)
		{
			if (store_redir(tokens, shell, &i, j) == 1)
				return (1);
		}
		else if ((ft_strcmp(tokens[i], "|") == 0) || (i == 0))
		{
			if (store_exe(tokens, shell, &i, &j) == 1)
				return (1);
		}
		else
		{
			if (store_arg(tokens, shell, i, j) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
