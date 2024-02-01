/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:13:59 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:40:03 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_memcmp` compares two blocks of memory and returns the
 * difference between the first differing byte, or 0 if the blocks are equal.
 * 
 * @param s1 A pointer to the first memory block to be compared.
 * @param s2 The parameter `s2` is a pointer to the second memory block that
 * you want to compare.
 * @param n The parameter `n` represents the number of bytes to compare between
 * the two memory areas `s1` and `s2`.
 * 
 * @return an integer value. If the comparison of the memory blocks pointed to
 * by s1 and s2 is equal, it returns 0. If they are not equal, it returns the
 * difference between the first differing bytes.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s1 + i) != *((unsigned char *)s2 + i))
			return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
		i++;
	}
	return (0);
}
