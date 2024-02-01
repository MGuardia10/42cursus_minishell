/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:47:06 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:42:26 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_strncmp` compares two strings up to a specified length and
 * returns the difference between the first differing characters.
 * 
 * @param s1 The parameter `s1` is a pointer to a constant character array,
 * which represents the first string to be compared.
 * @param s2 The parameter `s2` is a pointer to a constant character string.
 * It is the second string that you want to compare with `s1`.
 * @param n The parameter `n` in the `ft_strncmp` function represents the
 * maximum number of characters to compare between the two strings `s1` and `s2`
 * 
 * @return an integer value.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
