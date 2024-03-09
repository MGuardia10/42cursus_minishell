/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:49:26 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/09 11:18:05 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The ft_echo function prints the given arguments with an optional flag to omit
 * the newline character at the end.
 * 
 * @param args The `args` parameter in the `ft_echo` function is a pointer to 
 * an array of strings. Each element in the `args` array represents a 
 * command-line argument passed to the function.
 * 
 * @return an integer value of 0.
 */
int	ft_echo(char **args)
{
	int	flag;
	int	i;

	flag = 0;
	if (!args || !args[0])
		return (ft_printf("\n"), 0);
	if (ft_strcmp(args[0], "-n") == 0)
	{
		flag = 1;
		i = 1;
	}
	else
		i = 0;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] && args[i + 1][0] != '\0')
			ft_printf(" ");
		i++;
	}
	if (flag == 0)
		ft_printf("\n");
	return (0);
}

// gestionar muchos guiones y guiones sueltos