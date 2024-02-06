/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:31:21 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/06 12:05:40 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/inc/libft.h"

int	msh_pwd(void)
{
	char buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		perror("pwd: error\n");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}

int	msh_cd(char *dir)
{
	if (!dir)
	{
		if (chdir(getenv("HOME")) != 0) // usa la variable de entorno HOME cuando no se introduce parametro.
		{
			perror("cd: error\n");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	if (dir[0] == '\0')
		return (EXIT_SUCCESS); // si se introduce string vacia no hace nada.
	if (chdir(dir) != 0)
	{
		perror(dir);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*int	msh_echo(char *args[])
{
	
}

void msh_exit(int t)
{
	// aqui se liberará la memoria que haga falta y se terminaran todos los procesos.
	ft_printf("exit\n");
	exit(t);
}*/