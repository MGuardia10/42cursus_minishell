/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:46:54 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/05 13:02:27 by mguardia         ###   ########.fr       */
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
int	ft_cd(t_env_list *envi, char *arg)
{
	int	flag;

	flag = 0;
	if (!arg || arg[0] == '\0')
	{
		if (chdir(ft_getenv(envi, "HOME", &flag)) != 0)
		{
			if (flag == 1)
				ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			else
				perror("minishell: cd");
			return (1);
		}
	}
	else if (chdir(arg) != 0)
		return (ft_fprintf(2, "minishell: cd: %s: ", arg), perror(NULL), 1);
	return (0);
}
