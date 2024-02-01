/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:18:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:41:46 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_strdup` takes a string as input and returns a dynamically
 * allocated copy of that string.
 * 
 * @param s1 s1 is a pointer to a character array (string) that we want to
 * duplicate.
 * 
 * @return a pointer to a newly allocated memory block that contains a
 * duplicate of the input string `s1`.
 */
char	*ft_strdup(char *s1)
{
	char	*dst;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
