/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:46:54 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/14 09:24:47 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Changes the current working directory.
 *
 * @param dir The directory to change to. If NULL or empty,
 * changes to the home directory.
 * @return Returns 0 if the directory change is successful,
 * otherwise returns 1.
 */
int	msh_cd(char *dir)
{
	if (!dir || dir[0] == '\0')
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			return (1);
		}
		return (0);
	}
	else if (chdir(dir) != 0)
	{
		perror(dir);
		free(dir);
		return (1);
	}
	return (0);
}
