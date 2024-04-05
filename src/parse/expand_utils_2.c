/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:13:37 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/05 16:06:25 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `move_iters` iterates through a string, moving two pointers `i`
 * and `j` based on certain conditions related to valid characters and quotation
 * marks.
 * 
 * @param str The `str` parameter is a pointer to a character array or string.
 * @param i The parameter `i` in the `move_iters` function is a pointer to an
 * integer. It is used as an index to iterate over the characters in the `str`
 * string.
 * @param j The variable `j` in the `move_iters` function is used to keep track
 * of the number of iterations or movements made within the string `str`.
 * 
 * @return The function `move_iters` returns the value of the `flag` variable.
 */
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

/**
 * The function isinvalidchar checks if a character in a string is invalid
 * based on certain conditions.
 * 
 * @param str The `str` parameter is a pointer to a character array or string.
 * @param i The parameter `i` in the `isinvalidchar` function represents the
 * index of the character in the string `str`.
 * 
 * @return The function returns a boolean value indicating whether the character
 * at index `i` in the string `str` is considered invalid.
 */
int	isinvalidchar(char *str, int i)
{
	return (str[i] \
			&& !ft_isspace(str[i]) \
			&& (str[i] != '"' && !str[i + 1]) \
			&& (str[i] == '$' || !ft_isalpha(str[i])));
}
