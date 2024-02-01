/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:47:46 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:40:38 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_putendl_fd` writes a string followed by a newline character
 * to a file descriptor.
 * 
 * @param s A pointer to a string that needs to be written to the fd.
 * @param fd The parameter "fd" is an integer representing the file descriptor
 * of the file where the string "s" will be written.
 */
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
