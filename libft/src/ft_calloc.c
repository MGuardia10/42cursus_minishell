/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:03:46 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:21:53 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The ft_calloc function allocates memory for an array and initializes it
 * to zero.
 * 
 * @param count The count parameter represents the number of elements you want
 * to allocate memory for. It specifies how many elements of size bytes each
 * you want to allocate memory for.
 * @param size The size parameter represents the size in bytes of each element
 * in the array.
 * 
 * @return a pointer to the allocated memory block.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	arr = (void *)malloc(count * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, (count * size));
	return (arr);
}
