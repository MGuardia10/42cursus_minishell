/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:35:54 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:42:38 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function ft_tolower converts an uppercase letter to lowercase.
 * 
 * @param c The parameter "c" is of type int and represents a character.
 * 
 * @return The function `ft_tolower` returns the lowercase equivalent of the
 * input character `c`. If `c` is already lowercase, it returns `c` as is.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
