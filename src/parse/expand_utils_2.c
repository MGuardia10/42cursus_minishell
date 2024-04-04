/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:13:37 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/04 18:36:16 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	move_iters(char *str, int *i, int *j)
{
	int	flag;

	flag = 0;
	while (isvalidchar(str[*i]))
	{
		if (str[*i] == '"')
		{
			if (str[*i + 1] && !ft_isspace(str[*i + 1]) \
						&& str[*i + 1] != '\'' && str[*i + 1] != '"')
			{
				flag = 1;
				*j += 1;
				*i += 1;
			}
			break ;
		}
		*i += 1;
	}
	return (flag);
}

int	isinvalidchar(char *str, int i)
{
	return (str[i] \
			&& !ft_isspace(str[i]) \
			&& (str[i] != '"' && !str[i + 1]) \
			&& (str[i] == '$' || !ft_isalpha(str[i])));
}
