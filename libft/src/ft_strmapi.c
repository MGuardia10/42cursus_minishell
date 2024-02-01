/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:26:43 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:42:16 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_strmapi` takes a string `s` and applies a function `f` to
 * each character, returning a new string with the modified characters.
 * 
 * @param s A pointer to a null-terminated string that we want to apply the
 * function `f` to.
 * @param f The parameter `f` is a function pointer that takes two arguments:
 * an unsigned integer `i` and a character `s[i]`. The function `f` is expected
 * to return a character.
 * 
 * @return a dynamically allocated string (char *) that has been modified by
 * the function f.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	size_t	s_len;
	char	*dst;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	dst = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!dst)
		return (NULL);
	while (s[i])
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
