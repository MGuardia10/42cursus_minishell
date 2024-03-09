/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:00:05 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/09 11:17:37 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function ft_env prints the key-value pairs of the environment variables
 * stored in the envi (environment variables list).
 * 
 * @param env_list A pointer to a linked list of environment variables. Each
 * node in the linked list contains a key-value pair representing an environment
 * variable.
 * @param args The "args" parameter is a pointer to a structure of type
 * "t_line_p".
 * @return 0.
 */
int	ft_env(t_env_list **envi, char **args)
{
	t_env_list	*aux;

	if (args && args[0])
		return (0);
	aux = *envi;
	while (aux)
	{
		if (aux->content->value && aux->content->value[0] != '\0')
			printf("%s%s\n", aux->content->key, aux->content->value);
		aux = aux->next;
	}
	return (0);
}

// actualizar SHLVL