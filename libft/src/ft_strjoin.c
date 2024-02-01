/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:04:16 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:41:55 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_strjoin` concatenates two strings `s1` and `s2` and returns
 * a new string.
 * 
 * @param s1 The parameter `s1` is a pointer to a constant character string. It
 * represents the first string that you want to join.
 * @param s2 s2 is a pointer to a constant character string. It represents the
 * second string that needs to be joined with the first string (s1).
 * 
 * @return a pointer to a newly allocated string that is the concatenation of
 * the two input strings, s1 and s2.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dst;
	unsigned int	total_len;
	unsigned int	i;
	unsigned int	j;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}
