/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/19 21:03:42 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/inc/colors.h"

// Antes de inicializar comprobar que si hay comillas (simples o dobles) en el input, esten cerradas.
// Si no, seguir pidiendo input hasta que se cierren, como en bash. Si si :
// 		1º Hacer la expansion de todas las variables de entorno en el input, si hay.
// 		2º Hacer el parseo del input :
//			- Separar el input en tokens.
//			- Hacer agrupaciones de tokens llamados comandos. (exe, array de args, tipo de redir)
//			- Guardar los comandos en en el array de t_command.
//		3º Comprobar que todos los exe existan, si no, dar error.
// Despues se pasa a la ejecución :
// En la ejecucción cada comando ejecutado es un proceso hijo.
// El proceso de la minishell debe esperar a sus procesos hijos hasta que terminen,
// pero gestionando el envio de señales (Ctrl C, etc) enviandolas a sus procesos hijos en ejecución.
// 		1º Separar entre si es builtin o no.

int	closed_quotes(t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (shell->line_read[i] != '\0')
	{
		if (shell->line_read[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

void	check_quotes(t_shell *shell)
{
	char	*new_line;
	char	*input;

	while(closed_quotes(shell) == 1) // comprobar si ya estan cerradas
	{
		new_line = ft_strjoin(shell->line_read, "\n");
		free(shell->line_read);
		shell->line_read = new_line;
		input = readline(BCYN"> "RES);
		new_line = ft_strjoin(shell->line_read, input);
		free(input);
		free(shell->line_read);
		shell->line_read = new_line;
	}
}

int	init_line(t_shell *shell)
{
	check_quotes(shell); // bucle para cerrar comillas
	return (0);
}