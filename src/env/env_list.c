/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:34:58 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/13 18:10:08 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `set_env_key_value` takes a string `env_str` and creates a new
 * node in a linked list, setting the key and value of the node based on the
 * string.
 * 
 * @param new_node A pointer to a struct of type t_env_list, which represents a
 * node in a linked list.
 * @param env_str A string containing the environment variable in the format
 * "key=value".
 * 
 * @return an integer value. If the function is successful, it returns 0. If
 * there is an error, it returns 1.
 */
t_env	*set_env_content(char *env_str)
{
	int		len_to_equal;
	t_env	*content;

	content = ft_calloc(1, sizeof(t_env));
	if (!content)
		return (NULL);
	len_to_equal = 0;
	while (env_str[len_to_equal] && env_str[len_to_equal] != '=')
		len_to_equal++;
	content->key = ft_substr(env_str, 0, len_to_equal);
	if (!content->key)
		return (free(content), NULL);
	content->value = ft_substr(env_str, len_to_equal, \
													ft_strlen(env_str));
	if (!content->value)
		return (free(content->key), free(content), NULL);
	return (content);
}

/**
 * The function "overwrite_env" updates the value of a given key in a linked
 * list of environment variables.
 * 
 * @param envi A pointer to a pointer to a linked list of environment variables.
 * @param key A string representing the key of the environment variable to be
 * overwritten.
 * @param value The "value" parameter is a string that represents the new value
 * that you want to assign to the environment variable with the specified key.
 * 
 * @return an integer value.
 */
int	overwrite_env(t_env_list **envi, char *key, char *value)
{
	t_env_list	*aux;

	if (!value || value[0] == '\0')
		return (0);
	aux = *envi;
	while (aux)
	{
		if (ft_strcmp(aux->content->key, key) == 0)
		{
			free(aux->content->value);
			aux->content->value = ft_strdup(value);
			if (!aux->content->value)
				return (1);
			return (0);
		}
		aux = aux->next;
	}
	return (1);
}

/**
 * The function creates a new environment variable and adds it to a linked list
 * if it doesn't already exist, or overwrites the existing variable if it does.
 * 
 * @param envi A pointer to a pointer to a linked list of environment variables
 * (t_env_list).
 * @param node_content The parameter `node_content` is of type `t_env` and
 * contains the information for the new environment node that needs to be
 * created.
 * 
 * @return an integer value. If the function is successful, it returns 0. If
 * there is an error, it returns 1.
 */
int	create_new_env(t_env_list **envi, t_env *node_content)
{
	t_env_list	*new_node;

	if (already_exists(envi, node_content->key) == true)
	{
		if (overwrite_env(envi, node_content->key, node_content->value))
			return (1);
	}
	else
	{
		new_node = (t_env_list *)ft_lstnew((void *)node_content);
		if (!new_node)
			return (free_env((void *)node_content), 1);
		ft_lstadd_back((t_list **)envi, (t_list *)new_node);
	}
	return (0);
}

/**
 * The function creates a linked list of environment variables from an array of
 * strings.
 * 
 * @param shell A pointer to a structure of type t_shell.
 * @param env A double pointer to a character array, which represents the
 * environment variables.
 * 
 * @return an integer value. If the function is successful, it will return 0. If
 * there is an error, it will return 1.
 */
int	create_env_list(t_shell *shell, char **env)
{
	int			i;
	t_env		*node_content;

	i = -1;
	while (env[++i])
	{
		node_content = set_env_content(env[i]);
		if (!node_content)
			return (1);
		if (create_new_env(&shell->envi, node_content))
			return (free_env(node_content), 1);
	}
	return (0);
}
