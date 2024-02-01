/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:11:44 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 16:14:01 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	letter;

	letter = (char) c;
	while (*s)
	{
		if (*s == letter)
			return ((char *) s);
		s++;
	}
	if (letter == '\0')
		return ((char *) s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
