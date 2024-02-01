/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:41:10 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:41:51 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_striteri` iterates through a string and applies a given
 * function to each character, along with its index.
 * 
 * @param s A pointer to a string (array of characters) that we want to
 * iterate over.
 * @param f The parameter "f" is a function pointer that points to a function
 * with the following signature: void (*f)(unsigned int, char*). This means
 * that "f" is a pointer to a function that takes two arguments - an unsigned 
 * int and a char pointer - and returns void.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int		i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
