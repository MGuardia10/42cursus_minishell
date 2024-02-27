/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:46:54 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/26 17:02:52 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(t_env_list *envi, char *key, int *flag)
{
	t_env_list	*aux;

	aux = envi;
	while(aux)
	{
		if (ft_strcmp(key, aux->content->key) == 0)
			return (aux->content->value + 1);
		aux = aux->next;
	}
	*flag = 1;
	return (NULL);
}

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
				perror("cd");
			return (1);
		}
		return (0);
	}
	else if (chdir(arg) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
