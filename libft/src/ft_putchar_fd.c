/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:47:41 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:40:27 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function ft_putchar_fd writes a single character to a specified
 * file descriptor.
 * 
 * @param c The parameter "c" is of type char and represents the character
 * that needs to be written to the file descriptor "fd".
 * @param fd The parameter "fd" is an integer that represents the file
 * descriptor of the file to which the character "c" will be written.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
