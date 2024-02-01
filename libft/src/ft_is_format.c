/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:44:07 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:23:23 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function "check_format" compares the last characters of two strings and
 * returns 1 if they match, otherwise it returns 0.
 * 
 * @param str A pointer to a character array representing a string.
 * @param format The "format" parameter is a string that represents a specific
 * file extension or pattern that we want to check against.
 * 
 * @return either 0 (the extension is incorrect) or 1 (the extension is correct).
 */
bool	ft_is_format(char *str, char *format)
{
	int	len_str;
	int	len_format;
	int	i;

	len_str = ft_strlen(str);
	len_format = ft_strlen(format);
	i = 1;
	while (str[len_str - i] && format[len_format - i])
	{
		if (str[len_str - i] != format[len_format - i])
			return (false);
		i++;
	}
	return (true);
}
