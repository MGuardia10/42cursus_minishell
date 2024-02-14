/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:47:00 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/14 09:23:57 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Prints the current working directory.
 * 
 * Retrieves the current working directory using the `getcwd` function and
 * prints it.
 * If an error occurs while retrieving the current working directory, it prints
 * an error message and returns 1.
 * 
 * @return Returns 0 if the current working directory is printed 
 *         successfully, otherwise returns 1.
 */
int	msh_pwd(void)
{
	char	buffer[PATH_MAX];

	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}
	ft_printf("%s\n", buffer);
	return (0);
}
