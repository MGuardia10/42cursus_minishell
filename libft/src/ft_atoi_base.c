/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:26:14 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:21:34 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	get_digit(char c, int digits_in_base)
{
	int	max_digit;

	if (digits_in_base < 10)
		max_digit = digits_in_base + '0';
	else
		max_digit = digits_in_base - 10 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;
	int	digit;

	result = 0;
	sign = 0;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	digit = get_digit(ft_tolower(*str), str_base);
	while (digit >= 0)
	{
		result = result * str_base + (digit * sign);
		++str;
		digit = get_digit(ft_tolower(*str), str_base);
	}
	return (result);
}
