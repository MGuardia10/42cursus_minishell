/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:46:34 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:42:59 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function ft_strrchr searches for the last occurrence of a character in
 * a string and returns a pointer to that character.
 * 
 * @param s The parameter "s" is a pointer to a constant character string.
 * It represents the string in which we want to search for the character "c".
 * @param c The parameter "c" is of type "int" and represents the character to
 * be searched for in the string "s". It is cast to an unsigned char before
 * comparison.
 * 
 * @return a pointer to the last occurrence of the character 'c' in the
 * string 's'. If the character is found, a pointer to that character is
 * returned. If the character is not found, NULL is returned.
 */
char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen((char *) s) + 1;
	while (i--)
	{
		if (*(s + i) == (unsigned char)c)
			return ((char *)(s + i));
	}
	return (NULL);
}
