/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:49:26 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/18 19:01:31 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `has_n_flag` checks if a command line argument contains the flag
 * "-n".
 * 
 * @param args The `args` parameter is a pointer to an array of strings (char
 * pointers). Each string in the array represents a command-line argument.
 * @param i The parameter `i` in the `has_n_flag` function is a pointer to an
 * integer. It is used to keep track of the current index in the `args` array
 * that is being processed. The function increments the value of `i` as it
 * processes each element in the array.
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
 * @param args The `args` parameter in the `ft_echo` function is a pointer to an
 * array of strings (char pointers). Each element in the array represents a
 * separate argument that was passed to the `ft_echo` function. The function
 * prints out these arguments to the standard output.
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

/*
	echo -n hola --> hola
	echo -nnnnnnn hola --> hola
	echo -n-nnnnnn -n  --> -n-nnnnnn -n (con salto de linea)
	echo -n -n -n --> nada
	echo -nnnnnnnnnnnn n-n -n n-n --> n-n -n n-n
	echo -n-n --> -n-n (con salto de linea)

	Cada vez que encuentre un guión seguido de una "n" y un espacio despues se
	ejecutará la flag -n y simepre que se cumplan dichas condiciones da igual
	cuantas -n o -nnnnnnnn hayan.
*/