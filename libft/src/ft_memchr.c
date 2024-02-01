/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:01:30 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:39:54 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function ft_memchr searches for a specific character in a given memory
 * block and returns a pointer to the first occurrence of that character, or
 * NULL if it is not found.
 * 
 * @param s The parameter `s` is a pointer to the memory area to be searched.
 * It is of type `const void *`, which means it can point to any type of data.
 * @param c The parameter `c` is the character that we are searching for in
 * the memory block `s`. It is of type `int` because it can represent any
 * character value as well as the special value `EOF` (end-of-file).
 * @param n The parameter `n` represents the number of bytes to search in the
 * memory block `s`.
 * 
 * @return a pointer to the first occurrence of the character 'c' in the memory
 * block 's'. If the character is not found, it returns NULL.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
