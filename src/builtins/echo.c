/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:49:26 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/24 18:01:30 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `has_n_flag` checks if a command line argument contains the flag
 * "-n".
 * 
 * @param args The `args` parameter is a pointer to an array of strings. Each
 * string in the array represents a command-line argument.
 * @param i a pointer to an integer. It is used to keep track of the current
 * index in the `args` array that is being processed.
 * 
 * @return a boolean value, either true or false, based on whether the input
 * arguments contain the flag "-n" or not.
 */
bool	has_n_flag(char **args, int *i)
{
	int	j;

	j = 0;
	if (!args || !args[*i])
		return (false);
	if (args[*i][j] != '-' || args[*i][j + 1] != 'n')
		return (false);
	j = 2;
	while (args[*i][j])
	{
		if (args[*i][j] != 'n')
			return (false);
		j++;
	}
	(*i)++;
	return (has_n_flag(args, i), true);
}

/**
 * The ft_echo function prints the given arguments with optional newline
 * suppression.
 * 
 * @param args a pointer to an array of strings. Each element in the array
 * represents a separate argument that was passed to the `ft_echo` function.
 * 
 * @return The function `ft_echo` is returning an integer value of 0.
 */
int	ft_echo(char **args)
{
	int		i;
	bool	n_flag;

	if (!args || !args[0])
		return (ft_printf("\n"), 0);
	i = 0;
	n_flag = has_n_flag(args, &i);
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] && args[i + 1][0] != '\0')
			ft_printf(" ");
		i++;
	}
	if (n_flag == false)
		ft_printf("\n");
	return (0);
}
