/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:48:01 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:41:14 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_putnbr_fd` prints an integer to a file descriptor.
 * 
 * @param n The number to be printed.
 * @param fd The parameter `fd` represents the file descriptor of the file
 * where the output will be written. It is an integer value that specifies the
 * file or stream to which the output will be directed.
 */
void	ft_putnbr_fd(int n, int fd)
{
	long int	num;

	num = n;
	if (num < 0)
	{
		num *= -1;
		ft_putchar_fd('-', fd);
	}
	if (num > 9)
		ft_putnbr_fd(num / 10, fd);
	ft_putchar_fd(((num % 10) + '0'), fd);
}
