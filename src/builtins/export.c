/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:00:44 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/07 19:06:14 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * takes a linked list of environment variables and creates an array of strings
 * containing the keys of each variable, sorted in ascending order.
 * 
 * @param envi The parameter `envi` is of type `t_env_list*`, which is a pointer
 * to a linked list of type `t_env_list`.
 * 
 * @return a pointer to a character array (char **) or NULL if an error occurs.
 */
char	**create_sort_key_list(t_env_list *envi)
{
	int		i;
	char	**key_list;

	key_list = ft_calloc(ft_lstsize((t_list *)envi), sizeof(char *));
	if (!key_list)
		return (NULL);
	i = 0;
	while (envi)
	{
		if (ft_strcmp(envi->content->key, "_") != 0)
		{
			key_list[i] = ft_strdup(envi->content->key);
			if (!key_list[i])
				return (ft_free_matrix((void **)key_list), NULL);
			i++;
		}
		envi = envi->next;
	}
	key_list[i] = NULL;
	ft_sort_ascii(key_list);
	return (key_list);
}

/**
 * The function "print_env_var" prints the key-value pair of an environment
 * variable in a specific format.
 * 
 * @param key The key parameter is a pointer to a string that represents
 * the name of an environment variable.
 * @param value The "value" parameter is a string that represents the value of 
 * an environment variable.
 */
void	print_env_var(char *key, char *value)
{
	printf("declare -x %s", key);
	if (value && value[0] != '\0')
		printf("=\"%s\"", value + 1);
	printf("\n");
}

/**
 * prints the environment variables in a sorted order, excluding the variable
 * with the key "_".
 * 
 * @param envi A pointer to a pointer to a linked list of environment variables.
 * 
 * @return an integer value.
 */
static int	print_export(t_shell *shell, t_env_list **envi)
{
	t_env_list	*first_node;
	char		**key_list;
	int			i;

	first_node = *envi;
	key_list = create_sort_key_list(*envi);
	if (!key_list)
		(perror("malloc"), clean_exit(shell, EXIT_FAILURE));
	i = 0;
	while (key_list[i])
	{
		if (ft_strcmp(key_list[i], (*envi)->content->key) == 0)
		{
			print_env_var((*envi)->content->key, (*envi)->content->value);
			*envi = first_node;
			i++;
		}
		else
			*envi = (*envi)->next;
	}
	return (ft_free_matrix((void **)key_list), 0);
}

/**
 * The function "check_export_errors" checks if there are any errors in the
 * content of a given argument for an export command.
 * 
 * @param arg arg is a pointer to a structure of type t_line_p.
 * 
 * @return an integer value.
 */
static int	check_export_errors(char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

/**
 * is used to add or update environment variables based on the input arguments,
 * and it also has the functionality to print the current list of environment
 * variables if no arguments are provided.
 * 
 * @param env_list A pointer to a linked list of environment variables. Each
 * node in the linked list contains a key-value pair representing an environment
 * variable.
 * @param args args is a pointer to a linked list of strings. Each string
 * represents an argument passed to the export function.
 * 
 * @return an integer value.
 */
int	ft_export(t_shell *shell, t_env_list **envi, char **args)
{
	int		i;
	int		exit_code;
	t_env	*node_content;

	if (!args || !args[0])
		return (print_export(shell, envi));
	i = -1;
	exit_code = 0;
	while (args[++i])
	{
		if (check_export_errors(args[i]))
		{
			exit_code = 1;
			ft_dprintf(2, "Minishell: export: `%s': not a valid identifier\n", \
				args[i]);
			continue ;
		}
		node_content = set_env_content(args[i]);
		if (!node_content)
			(perror("malloc"), clean_exit(shell, EXIT_FAILURE));
		if (create_new_env(envi, node_content))
			(perror("malloc"), clean_exit(shell, EXIT_FAILURE));
	}
	return (exit_code);
}
