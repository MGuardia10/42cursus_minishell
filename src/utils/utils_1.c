/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:52:47 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/28 10:51:57 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function "free_env" frees the memory allocated for a structure of type
 * "t_env" and its contents.
 * 
 * @param content The parameter `content` is a void pointer, which means it can
 * point to any type of data. In this case, it is expected to point to a
 * structure of type `t_env`.
 */
void	free_env(void *content)
{
	t_env	*env_content;

	env_content = content;
	free(env_content->key);
	if (env_content->value)
		free(env_content->value);
	free(env_content);
}

/**
 * The function checks if a given key already exists in a linked list of
 * environment variables.
 * 
 * @param envi A pointer to a pointer to a linked list of environment variables.
 * @param key The "key" parameter is a string that represents the key we are
 * checking for existence in the linked list.
 * 
 * @return a boolean value. It returns true if the key already exists in the
 * linked list of environment variables, and false otherwise.
 */
bool	already_exists(t_env_list **envi, char *key)
{
	t_env_list	*aux;

	aux = *envi;
	while (aux)
	{
		if (ft_strcmp(aux->content->key, key) == 0)
			return (true);
		aux = aux->next;
	}
	return (false);
}

/**
 * The function `is_builtin` checks if a given command is a built-in command in
 * a shell program.
 * 
 * @param cmd The `is_builtin` function checks if a given command is a built-in
 * command in a shell. The function compares the given command `cmd` with the 
 * list built-in commands such as "echo", "cd", "pwd", "export", "unset", "env",
 * and "exit".
 * 
 * @return The function `is_builtin` returns a boolean value (true or false)
 * indicating whether the input command `cmd` is one of the built-in commands.
 */
inline bool	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 \
			|| ft_strcmp(cmd, "cd") == 0 \
			|| ft_strcmp(cmd, "pwd") == 0 \
			|| ft_strcmp(cmd, "export") == 0 \
			|| ft_strcmp(cmd, "unset") == 0 \
			|| ft_strcmp(cmd, "env") == 0 \
			|| ft_strcmp(cmd, "exit") == 0);
}

/**
 * The function `env_to_arr` converts a linked list of environment variables
 * into an array of strings.
 * 
 * @param env The `env` parameter in the `env_to_arr` function is of type
 * `t_env_list *`, which seems to be a linked list structure containing
 * environment variables.
 * 
 * @return The function `env_to_arr` is returning an array of strings.
 */
char	**envi_to_arr(t_env_list *env)
{
	char	**arr;
	int		i;

	arr = malloc((ft_lstsize((t_list *)env) + 1) * sizeof(char *));
	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin(env->content->key, env->content->value);
		if (!arr[i])
			return (ft_free_matrix((void **)arr), NULL);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

/**
 * The function create_argv creates an array of strings from a given command
 * structure. It´s used to create the second argument for the execve function.
 * 
 * @param cmd The `create_argv` function takes a `t_command` structure as a
 * parameter. This structure likely contains information about a command to be
 * executed, such as the executable name (`cmd.exe`) and an array of arguments
 * (`cmd.args`). The function dynamically allocates memory to create an array of
 * strings (`
 * 
 * @return The function `create_argv` is returning a dynamically allocated array
 * of strings (char **), which contains the executable name followed by the
 * arguments from the input `t_command cmd`. The array is terminated with NULL.
 */
char	**create_argv(t_command cmd)
{
	char	**arr;
	int		i;

	arr = malloc((ft_arrsize((void **)cmd.args) + 2) * sizeof(char *));
	i = 0;
	arr[i] = ft_strdup(cmd.exe);
	if (!arr[i])
		return (ft_free_matrix((void **)arr), NULL);
	while (cmd.args[i])
	{
		arr[i + 1] = ft_strdup(cmd.args[i]);
		if (!arr[i + 1])
			return (ft_free_matrix((void **)arr), NULL);
		i++;
	}
	arr[i + 1] = NULL;
	return (arr);
}
