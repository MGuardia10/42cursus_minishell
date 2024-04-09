/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:50:33 by mguardia          #+#    #+#             */
/*   Updated: 2024/04/09 11:53:17 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `ft_all_digits` checks if a given string consists only of
 * digits.
 * 
 * @param str a string. It´s use for checking if all characters are digits.
 * 
 * @return a boolean value `true` if all characters in the input string are
 * digits, and `false` otherwise.
 */
static bool	ft_all_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * The function `create_shlvl` sets the environment variable SHLVL to 1s.
 * 
 * @param envi a pointer to a linked list structure `t_env_list` that represents
 * environment variables.
 * 
 * @return an integer value. If the function is successful, it returns 0. If
 * there is an error it returns 1.
 */
static int	create_shlvl(t_env_list **envi)
{
	t_env		*node_content;

	node_content = set_env_content("SHLVL=1");
	if (!node_content)
		return (1);
	if (create_new_env(envi, node_content))
	{
		free_env(node_content);
		return (1);
	}
	return (0);
}

/**
 * The function `set_shlvl` increments the value of the "SHLVL" environment
 * variable by 1 if it exists and is a valid integer, otherwise it creates the
 * variable with a value of 1.
 * 
 * @param envi a pointer to a structure `t_env_list` that contains environment
 * variables and their values. 
 *  
 * @return an integer that is the result of the `overwrite_env` function.
 */
int	set_shlvl(t_env_list **envi)
{
	char	*shlvl_value;
	char	*shlvl_new_value;
	char	*shlvl_new_value_with_equal;
	int		flag;

	shlvl_value = ft_getenv(*envi, "SHLVL", &flag);
	if ((!shlvl_value && flag == 1) || ft_all_digits(shlvl_value) == false)
		return (create_shlvl(envi));
	shlvl_new_value = ft_itoa(ft_atoi(shlvl_value) + 1);
	if (!shlvl_new_value)
		return (1);
	shlvl_new_value_with_equal = ft_strjoin("=", shlvl_new_value);
	free(shlvl_new_value);
	if (overwrite_env(envi, "SHLVL", shlvl_new_value_with_equal))
		return (free(shlvl_new_value_with_equal), 1);
	return (free(shlvl_new_value_with_equal), 0);
}
