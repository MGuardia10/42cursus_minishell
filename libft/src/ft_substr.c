/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:00:30 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:42:45 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_substr` takes a string `s`, a starting index `start`, and
 * a length `len`, and returns a newly allocated substring of `s` starting 
 * at `start` with a length of `len`.
 * 
 * @param s A pointer to a constant character string (input string).
 * @param start The start parameter is the index at which to start extracting
 * the substring from the input string.
 * @param len The parameter "len" represents the length of the substring that
 * you want to extract from the string "s".
 * 
 * @return a pointer to a newly allocated substring of the input string 's'.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			slen;
	unsigned int	i;
	char			*dest;

	slen = ft_strlen(s);
	if (start > slen)
		return (NULL);
	if (len > slen - start)
		len = slen - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!s || !dest)
		return (NULL);
	i = 0;
	while (start < slen && i < len && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
