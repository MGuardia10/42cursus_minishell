/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:25:06 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:40:22 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function ft_memset sets a specified number of bytes in a memory block
 * to a specified value.
 * 
 * @param b The parameter "b" is a void pointer that points to the memory block
 * that needs to be filled with a specific value.
 * @param c The parameter "c" is an integer that represents the value to be set.
 * It will be casted to an unsigned char before being assigned to each byte in
 * the memory block.
 * @param len The parameter "len" represents the length of the memory block that
 * needs to be filled with the specified value.
 * 
 * @return a pointer to the memory block that was passed as the first argument.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*aux;

	aux = b;
	while (len-- > 0)
		*aux++ = (char) c;
	return (b);
}
