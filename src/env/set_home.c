/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:42:35 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/24 17:37:59 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function creates a substring from a given string up to the second
 * occurrence of the '/' character.
 * 
 * @param value a string to extract a specific part of the path.
 * 
 * @return a string that represents the home directory path based on the
 * input `value`.
 */
static char	*create_from_pwd(char *value)
{
	int		i;
	char	*ptr;
	char	*home;

	i = 0;
	ptr = ft_strchr(value, '/');
	while (++i < 3)
	{
		if (!ptr && i == 2)
			return (ft_strdup(""));
		else if (!ptr)
			break ;
		else
		{
			ptr++;
			ptr = ft_strchr(ptr, '/');
		}
	}
	if (!ptr)
		home = ft_substr(value, 0, ft_strlen(value));
	else
		home = ft_substr(value, 0, ft_strlen(value) - ft_strlen(ptr));
	return (home);
}

/**
 * The function `find_home` retrieves the home directory path based on the
 * current working directory.
 * 
 * @param envi The `envi` parameter is of type `t_env_list *`, which is a
 * pointer to a structure representing an environment variable list.
 * @param flag The `flag` parameter is a pointer to an integer that is used to
 * indicate the status of the function execution.
 * 
 * @return The function `find_home` is returning the `home` variable.
 */
char	*find_home(t_env_list *envi, int *flag)
{
	char	*value;
	char	*home;

	value = ft_getenv(envi, "PWD", flag);
	if (!value && *flag == 0)
		return (NULL);
	else if (!value && *flag == 1)
		return (ft_strdup(""));
	else
		home = create_from_pwd(value);
	return (home);
}

/**
 * sets the home directory path in a shell structure based on the HOME
 * environment variable.
 * 
 * @param shell a pointer to a `t_shell` struct.
 * 
 * @return an integer value. If the function is successful, it returns 0. If
 * there is an error, it returns 1.
 */
int	set_home(t_shell *shell)
{
	int		flag;
	char	*home_env;

	home_env = ft_getenv(shell->envi, "HOME", &flag);
	if (!home_env && flag == 1)
	{
		shell->home = find_home(shell->envi, &flag);
		if (!shell->home)
			return (1);
	}
	else if (!home_env && flag == 0)
		return (1);
	else
		shell->home = ft_strdup(home_env);
	return (0);
}
