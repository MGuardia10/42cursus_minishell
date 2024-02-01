/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_custom_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:01:40 by mguardia          #+#    #+#             */
/*   Updated: 2024/02/01 15:22:34 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * The function `ft_custom_error` prints an error message to the standard error
 * output and exits the program with a failure status.
 * 
 * @param error The parameter "error" is a pointer to a character array (string)
 * that represents the error message to be displayed.
 */
void	ft_custom_error(char *error)
{
	write(STDERR_FILENO, "Error: ", 7);
	ft_putstr_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
