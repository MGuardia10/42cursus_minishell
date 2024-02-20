/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/02/20 18:12:52 by raalonso         ###   ########.fr       */
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

char	*extractenv(char *line, int i)
{
	char	*env;
	char	*exp_env;
	int		j;

	j = i;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '"' && line[i] != '\n')
		i++;
	env = ft_substr(line, j, i - j);
	if (!env)
		return (NULL);
	exp_env = getenv(env);
	if (!exp_env)
		return (NULL);
	free(env);
	return (exp_env);
}

int	expand_env(t_shell *shell)
{
	char	*env;
	char	*exp = NULL;
	char	*aux;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (shell->line_read[i] != '\0')
	{
		if (shell->line_read[i] == '$')
		{
			env = extractenv(shell->line_read, i + 1);
			if (!env)
				return (1);
			if (!exp)
				exp = ft_substr(shell->line_read, j, i);
			else
			{
				aux = ft_strjoin(exp, ft_substr(shell->line_read, j, i - j));
				free(exp);
				exp = aux;
			}
			aux = ft_strjoin(exp, env);
			free(exp);
			exp = aux;
			while (shell->line_read[i] != '\0' && shell->line_read[i] != ' ' && shell->line_read[i] != '"' && shell->line_read[i] != '\n')
				i++;
			j = i;
		}
		i++;
	}
	if (!exp)
		exp = ft_substr(shell->line_read, j, i);
	else
	{
		aux = ft_strjoin(exp, ft_substr(shell->line_read, j, i));
		free(exp);
		exp = aux;
	}
	free(shell->line_read);
	shell->line_read = exp;
	return (0);
}

int	init_line(t_shell *shell)
{
	if (check_quotes(shell) == 1)
		return (1);
	if (expand_env(shell) == 1) // expandir las variables de entorno del input (pendiente: no expandir variables dentro de comillas simples, leaks)
		return (1);
	printf("\n%s\n", shell->line_read);
	return (0);
}