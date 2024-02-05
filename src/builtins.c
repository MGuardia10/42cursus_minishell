/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:31:21 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/05 09:15:08 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int	pwd(void)
{
	char buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) != NULL)
	{
		ft_printf("%s\n", buffer);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("pwd: Error");
		return (EXIT_FAILURE);
	}
}