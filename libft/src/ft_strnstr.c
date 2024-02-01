/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:10:31 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:43:05 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_strnstr` searches for the first occurrence of a substring
 * `needle` in a string `haystack` up to a specified length `len`.
 * 
 * @param haystack The `haystack` parameter is a pointer to the string in which
 * we want to search for the `needle` string.
 * @param needle The `needle` parameter is a pointer to the substring that we
 * are searching for within the `haystack` string.
 * @param len The parameter `len` represents the maximum number of characters
 * to search in the `haystack` string.
 * 
 * @return The function `ft_strnstr` returns a pointer to the first occurrence
 * of the `needle` string within the `haystack` string, up to a maximum of `len`
 * characters. If the `needle` string is empty, it returns a pointer to the
 * `haystack` string.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (haystack[i + j] == '\0' && needle[j] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
