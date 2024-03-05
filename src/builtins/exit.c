/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:56:53 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/05 13:14:00 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(t_shell *shell)
{
	ft_putstr_fd("exit\n", 2);
	if (!shell->cmds->args || !shell->cmds->args[0])
		return (EXIT_FAILURE); // Aqui retorna uno pero debe salirse del programa, asique habria que hacer alguna flag.
	if (ft_arrsize((void **)shell->cmds->args) > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE); // Aqui sin embargo no se sale del programa.
	}
	else
	{
		// verificar el argumento que se ha pasado es numero entre 0 - 255
		// ver los codigos de errores para casos: numero negativo, argumento no
		// numerico, numero > 255.
		ft_putstr_fd("Solo un argumento rey te falta verificarlo crack\n", 2);
	}
	// liberar toda la memoria
	// retornar codigo de exit - no se si desde aqui con "exit"
	exit(EXIT_FAILURE);
}
