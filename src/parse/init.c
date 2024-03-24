/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/24 22:56:00 by raalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void printall(t_shell *shell)
{
	for (int i = 0; i < shell->n_cmds; i++)
	{
		printf("-------------------------\n\n");
		printf("EXE COMANDO: \n%s\n\n", shell->cmds[i].exe);
		printf("ARGUMENTOS(%d): \n", shell->cmds[i].args_count);
		for (int j = 0; shell->cmds[i].args[j]; j++)
			printf("%s\n", shell->cmds[i].args[j]);
		printf("\nINFILES(%d): \n", shell->cmds[i].infile_count);
		for (int j = 0; j < shell->cmds[i].infile_count; j++)
		{
			printf("Tipo redir -> %u\n", shell->cmds[i].infile[j].redir);
			printf("Filename -> %s\n\n", shell->cmds[i].infile[j].filename);
		}
		printf("OUTFILES(%d): \n", shell->cmds[i].outfile_count);
		for (int j = 0; j < shell->cmds[i].outfile_count; j++)
		{
			printf("Tipo redir -> %u\n", shell->cmds[i].outfile[j].redir);
			printf("Filename -> %s\n\n", shell->cmds[i].outfile[j].filename);
		}
		printf("-------------------------\n");
	}
}

int	create_cmd_array(t_shell *shell)
{
	char	**tokens;

	tokens = get_tokens(shell->line_read);
	if (!tokens)
		return (1);
	if (init_for_store(tokens, shell) == 1)
		return (1);
	if (store_tokens(tokens, shell) == 1)
		return (1);
	// printall(shell);
	ft_free_matrix((void *)tokens);
	return (0);
}

void	free_cmds(t_shell *shell)
{
	int i = 0;
	int	j = 0;
	while (i < shell->n_cmds)
	{
		while (j < shell->cmds[i].infile_count)
		{
			free(shell->cmds[i].infile[j].filename);
			j++;
		}
		while (j < shell->cmds[i].outfile_count)
		{
			free(shell->cmds[i].outfile[j].filename);
			j++;
		}
		while (j < shell->cmds[i].args_count)
		{
			free(shell->cmds[i].args[j]);
			j++;
		}
		free(shell->cmds[i].args);
		free(shell->cmds[i].exe);
		i++;
	}
}

int	init_line(t_shell *shell)
{
	if (check_quotes(shell) == 1) // QUITAR LO INECESARIO
		return (1);
	if (expand_line(shell) == 1) // GESTIONAR SI NO EXISTE ENV, CAMBIAR GETENV POR FT_GETENV, GESTIONAR $?, HEREDOC GESTIONAR EXPANSION DELIMITADOR
		return (1);
	if (create_cmd_array(shell) == 1)
		return (1);
	free_cmds(shell);
	return (0);
}