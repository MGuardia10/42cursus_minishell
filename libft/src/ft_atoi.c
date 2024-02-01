/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:50:41 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:21:41 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	is_space(char c)
{
	if (c == ' ')
		return (1);
	else if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

static int	is_sign(char c)
{
	if (c == '-')
		return (1);
	else if (c == '+')
		return (1);
	return (0);
}

/**
 * The ft_atoi function converts a string representation of an integer to an
 * actual integer value.
 * 
 * @param str The parameter `str` is a pointer to a character array, which 
 * represents the string that we want to convert to an integer.
 * 
 * @return the converted integer value of the input string.
 */
int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (is_sign(str[i]))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
