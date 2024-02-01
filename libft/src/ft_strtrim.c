/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:24:52 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:42:50 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_strtrim` trims the characters specified in the `set`
 * parameter from the beginning and end of the string `s1`.
 * 
 * @param s1 The parameter `s1` is a pointer to a string that you want to trim.
 * @param set The "set" parameter is a string that contains a set of characters
 * that we want to remove from the beginning and end of the "s1" string.
 * 
 * @return a trimmed version of the input string `s1`.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	s1_len = ft_strlen(s1);
	while (ft_strchr(set, s1[s1_len]) && s1_len != 0)
		s1_len--;
	return (ft_substr(s1, 0, s1_len + 1));
}
