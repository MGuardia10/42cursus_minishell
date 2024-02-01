/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:46:31 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:21:49 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The ft_bzero function sets the first n bytes of the memory pointed to by s
 * to zero.
 * 
 * @param s The parameter "s" is a void pointer that represents the memory
 * address of the starting point of the memory block to be zeroed out.
 * @param n The parameter `n` represents the number of bytes to be set to zero
 * in the memory block pointed to by `s`.
 */
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
