/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:38:26 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:23:34 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_isalpha` checks if a given character is an alphabetic
 * character.
 * 
 * @param c The parameter "c" is of type "int" and represents a character.
 * 
 * @return a boolean value indicating whether the given character is an
 * alphabetic character or not.
 */
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
