/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_readable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:48:29 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:39:24 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function checks if a file is readable by attempting to read from it and
 * returns a flag indicating the result.
 * 
 * @param file A string representing the file path.
 * 
 * @return a flag indicating whether the file is readable or not. If the file
 * is readable, the flag will be set to 1. If the file is not readable, the
 * flag will be set to 0.
 */
bool	ft_is_readable(char *file)
{
	int		fd;
	bool	flag;

	fd = open(file, O_RDONLY);
	if (read(fd, 0, 0) < 0)
		flag = false;
	else
		flag = true;
	close(fd);
	return (flag);
}
