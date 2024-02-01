/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:49:34 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:41:40 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_strcmp` compares two strings and returns the difference
 * between the first differing characters.
 * 
 * @param s1 The parameter `s1` is a pointer to a constant character array,
 * which represents the first string to be compared.
 * @param s2 The parameter `s2` is a pointer to a constant character array
 * (string) that represents the second string to be compared.
 * 
 * @return the difference between the ASCII values of the characters at the
 * first differing position in the two strings.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
