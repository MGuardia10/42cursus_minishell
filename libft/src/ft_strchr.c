/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:25:45 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:41:36 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function ft_strchr searches for a specific character in a string and
 * returns a pointer to the first occurrence of that character.
 * 
 * @param s The parameter "s" is a pointer to a constant character string. It
 * represents the string in which we want to search for the character "c".
 * @param c The parameter "c" is of type "int" and represents the character we
 * are searching for in the string "s".
 * 
 * @return a pointer to the first occurrence of the character 'c' in the string
 * 's'. If 'c' is not found, it returns a NULL pointer.
 */
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
