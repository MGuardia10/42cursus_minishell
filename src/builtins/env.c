/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:00:05 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/30 10:33:08 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `ft_env` prints out the key-value pairs of environment variables
 * stored in a linked list.
 * 
 * @param envi a pointer to a pointer to a structure representing an environment
 * list. The structure contains key-value pairs for environment variables.
 * @param args a pointer to a pointer to a character array. It is used to pass
 * arguments to the function.
 * 
 * @return the function returns 0.
 */
int	ft_env(t_env_list **envi, char *arg)
{
	t_env_list	*aux;

	if (arg)
	{
		ft_fprintf(STDERR_FILENO, "env: %s: ", arg);
		ft_fprintf(STDERR_FILENO, "No such file or directory\n");
		return (127);
	}
	aux = *envi;
	while (aux)
	{
		if (aux->content->value && aux->content->value[0] != '\0')
			printf("%s%s\n", aux->content->key, aux->content->value);
		aux = aux->next;
	}
	return (0);
}
