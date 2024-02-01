/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:42 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:42:04 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The ft_strlcpy function copies a string from src to dst, ensuring that the
 * destination string is null-terminated and does not exceed the specified size.
 * 
 * @param dst The `dst` parameter is a pointer to the destination string where
 * the copied string will be stored.
 * @param src The `src` parameter is a pointer to a constant character string
 * that we want to copy into the `dst` string.
 * @param dstsize The parameter `dstsize` represents the size of the
 * destination buffer `dst`. It specifies the maximum number of characters that
 * can be copied into `dst`, including the null-terminating character.
 * 
 * @return the length of the source string, which is stored in the variable
 * dst_len.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst_len);
}
