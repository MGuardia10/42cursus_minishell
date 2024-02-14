/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:00:54 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/14 14:50:28 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function "check_unset_errors" checks if a given string contains any
 * invalid characters for an unset command.
 * 
 * @param arg The parameter `arg` is a pointer to a structure type `t_line_p`.
 * 
 * @return an integer value. If the first character is a digit, it returns 1.
 * Otherwise, it checks each character in the string `str` and if any
 * character is not alphanumeric or an underscore, it returns 1 too. If all
 * characters in the string are either alphanumeric or '_', it returns 0.
 */
int	check_unset_errors(t_line_p *arg)
{
	char	*str;
	int		i;

	str = arg->content;
	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

/**
 * The function `delete_env` is used to remove a node from a linked list based
 * on a given key value.
 * 
 * @param envi A pointer to a pointer to a linked list of environment variables
 * (t_env_list).
 * @param str The parameter `str` is a pointer to a character array, which
 * represents the key of the environment variable that needs to be deleted.
 * 
 * @return void.
 */
void	delete_env(t_env_list **envi, char *str)
{
	t_env_list	*last_node;
	t_env_list	*curr_node;

	last_node = NULL;
	curr_node = *envi;
	while (curr_node && ft_strcmp(curr_node->content->key, str))
	{
		last_node = curr_node;
		curr_node = curr_node->next;
	}
	if (!curr_node)
		return ;
	if (last_node == NULL)
		*envi = curr_node->next;
	else
		last_node->next = curr_node->next;
	ft_lstdelone((t_list *)curr_node, free_env);
}

/**
 * The function ft_unset removes environment variables from a linked list if
 * they exist.
 * 
 * @param envi A pointer to a pointer to a linked list of environment variables.
 * @param args args is a linked list of strings, where each string represents an
 * argument passed to the unset command.
 * 
 * @return an integer value of 0.
 */
int	ft_unset(t_env_list **envi, t_line_p *args)
{
	while (args)
	{
		if (check_unset_errors(args))
		{
			printf("Minishell: unset: `%s': ", args->content);
			printf("not a valid identifier\n");
		}
		else if (already_exists(envi, args->content) == true)
			delete_env(envi, args->content);
		args = args->next;
	}
	return (0);
}
