/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:47:00 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/26 18:39:49 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Prints the current working directory. Retrieves the current working 
 * directory using the `getcwd` function and prints it.
 * If an error occurs while retrieving the current working directory, it prints
 * an error message and returns 1.
 * 
 * @return Returns 0 if the current working directory is printed successfully,
 * otherwise returns 1.
 */
int	ft_pwd(t_shell *shell)
{
	char	buffer[PATH_MAX];

	if (!getcwd(buffer, PATH_MAX))
		(perror("getcwd"), clean_exit(shell, EXIT_FAILURE));
	ft_printf("%s\n", buffer);
	return (0);
}
