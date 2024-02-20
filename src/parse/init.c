/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/20 23:16:52 by raalonso         ###   ########.fr       */
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

int	num_of_cmds(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '|' || line[i] == '>')
		{
			count++;
			if (line[i] == '|' || line[i] == '>')
			{
				count++;
				if (line[i + 1] == '>')
					i += 1;
			}
			while (line[i + 1] == ' ')
				i++;
		}
		i++;
	}
	printf("%d\n", count);
	return (count);
}

char	**get_tokens(char *line)
{
	int		i;
	int		j;
	int		last;
	char	**cmds;

	i = 0;
	j = 0;
	last = 0;
	cmds = (char **)malloc(sizeof(char *) * (num_of_cmds(line) + 1));
	while (line[i])
	{
		if (line[i] == ' ')
		{
			cmds[j] = ft_substr(line, last, i - last);
			if (!cmds[j])
				return (NULL);
			last = i + 1;
			j++;
		}
		else if (line[i] == '|' || line[i] == '>')
		{
			cmds[j] = ft_substr(line, last, i - last);
			if (!cmds[j])
				return (NULL);
			last = i + 1;
			j++;
			if (line[i + 1] == '>')
			{
				cmds[j] = ft_substr(line, i, 2);
				i++;
			}
			else
				cmds[j] = ft_substr(line, i, 1);
			j++;
		}
		i++;
	}
	cmds[j] = ft_substr(line, last, i - last);
	if (!cmds[j])
		return (NULL);
	cmds[j + 1] = NULL;
	int l = 0;
	while (cmds[l])
	{
		printf("\n%s\n", cmds[l]);
		l++;	
	}
	return (cmds);
}

int	create_cmd_array(t_shell *shell)
{
	char	**tokens;
	tokens = get_tokens(shell->line_read);
	if (!tokens)
		return (1);
	ft_free_matrix((void *)tokens);
	return (0);
}

int	init_line(t_shell *shell)
{
	if (check_quotes(shell) == 1)
		return (1);
	if (expand_line(shell) == 1)
		return (1);
	create_cmd_array(shell);
	return (0);
}