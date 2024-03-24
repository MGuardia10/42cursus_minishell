/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:30:43 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/05 13:15:17 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function ft_getenv searches for a specific key in a linked list of
 * environment variables and returns the corresponding value.
 * 
 * @param envi The `envi` parameter is a pointer to a linked list of environment
 * variables. Each node in the linked list contains a key-value pair 
 * representing an environment variable.
 * @param key The `key` parameter in the `ft_getenv` function represents the key
 * for which you want to retrieve the corresponding value from the environment.
 * @param flag The `flag` parameter in the `ft_getenv` function is a pointer to
 * an integer. It is used to indicate whether the specified key was found in the
 * environment list or not.
 * 
 * @return The function `ft_getenv` is returning a pointer to the value
 * associated with the given key in the environment list `envi`.
 * If the key is found, it returns a pointer to the value (excluding the first
 * character which is typically used as a delimiter). If the key is not found,
 * it sets the flag to 1 and returns NULL.
 */
char	*ft_getenv(t_env_list *envi, char *key, int *flag)
{
	t_env_list	*aux;

	aux = envi;
	*flag = 0;
	while (aux)
	{
		if (ft_strcmp(key, aux->content->key) == 0)
			return (aux->content->value + 1);
		aux = aux->next;
	}
	*flag = 1;
	return (NULL);
}

/**
 * The function `is_directory` checks if a path is a directory by using the
 * `stat` function and checking the mode of the file.
 * 
 * @param path The `path` parameter is a pointer to a string that represents the
 * path of the directory you want to check.
 * 
 * @return The function `is_directory` returns a boolean value indicating
 * whether the given path is a directory or not. It returns `true` if the path
 * is a directory and `false` if it is not.
 */
bool	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (false);
	return (S_ISDIR(statbuf.st_mode));
}
