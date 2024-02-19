/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/18 19:23:12 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_line(t_shell *shell)
{
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
}