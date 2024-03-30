/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:26:04 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/30 09:08:20 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	count_digits(int n)
{
	size_t	count;

	count = 0;
	if (!n)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

/**
 * The function `ft_itoa` converts an integer into a string representation.
 * 
 * @param n The parameter `n` is an integer that we want to convert to a string.
 * 
 * @return a dynamically allocated string that represents the integer value
 * passed as an argument.
 */
char	*ft_itoa(int n)
{
	size_t	count;
	char	digit;
	char	*dst;

	count = count_digits(n);
	dst = (char *)ft_calloc(count + 1, sizeof(char));
	if (!dst)
		return (NULL);
	if (n < 0)
		dst[0] = '-';
	if (n == 0)
		dst[--count] = '0';
	while (n != 0)
	{
		digit = n % 10;
		dst[--count] = digit + '0';
		n /= 10;
	}
	return (dst);
}
