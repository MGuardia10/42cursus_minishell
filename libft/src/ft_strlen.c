/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:56:05 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:42:09 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_strlen` calculates the length of a string by iterating
 * through each character until it reaches the null terminator.
 * 
 * @param s The parameter "s" is a pointer to a character array (string).
 * 
 * @return the length of the string `s` as a `size_t` value.
 */
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
