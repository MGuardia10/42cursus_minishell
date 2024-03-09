/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/06 17:49:01 by raalonso         ###   ########.fr       */
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

int	num_of_tokens(char *line)
{
	int	i;
	int	aux;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '"' && line[i] != '\'')
		{
			count++;
			while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '"' && line[i] != '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			aux = i;
			count++;
			while (line[i] && line[i] != '"')
				i++;
			i++;
			if (i - aux == 0)
				count--;
		}
		else if (line[i] == '\'')
		{
			i++;
			aux = i;
			count++;
			while (line[i] && line[i] != '\'')
				i++;
			i++;
			if (i - aux == 0)
				count--;
		}
		else if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
		}
		else if (line[i] == '|')
		{
			//if (line[i + 1] == '|')
				// unexpected token error
			count++;
			i++;
		}
		else if (line[i] == '>')
		{
			count++;
			if (line[i + 1] == '>')
				i++;
			i++;
		}
	}
	printf("%d\n", count);
	return (count);
}

int	is_special_char(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '"' || c == '\'')
		return (0);
	return (1);
}

int	quotes_token(char *line, char **cmds, int *i, int *j)
{
	int last;

	*i += 1;
	last = *i;
	if (line[*i] == '"')
	{
		while (line[*i] && line[*i] != '"')
			*i += 1;
	}
	else if (line[*i] == '\'')
	{
		while (line[*i] && line[*i] != '\'')
			*i += 1;	
	}
	cmds[*j] = ft_substr(line, last, *i - last);
	if (!cmds[*j])
		return (1);
	*i += 1;
	*j += 1;
	return (0);
}

int	handle_special_char(char *line, char **cmds, int *i, int *j)
{
	int	last;
	
	if (line[*i] == '"' || line[*i] == '\'')
	{
		if (quotes_token(line, cmds, i, j) == 1)
			return (1);
	}
	else if (line[*i] == ' ')
	{
		while (line[*i] == ' ')
			*i += 1;
	}
	else if (line[*i] == '|')
	{
		last = *i;
		*i += 1;
		cmds[*j] = ft_substr(line, last, *i - last);
		if (!cmds[*j])
			return (1);
		*j += 1;
	}
	else if (line[*i] == '>')
	{
		last = *i;
		if (line[*i + 1] == '>')
		{
			*i += 2;
			cmds[*j] = ft_substr(line, last, *i - last);
			if (!cmds[*j])
				return (1);
			*j += 1;
		}
		else
		{
			*i += 1;
			cmds[*j] = ft_substr(line, last, *i - last);
			if (!cmds[*j])
				return (1);
			j += 1;
		}
	}
	return (0);
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
	cmds = (char **)malloc(sizeof(char *) * (num_of_tokens(line) + 1));
	while (line[i])
	{
		if (is_special_char(line[i]) == 1)
		{
			last = i;
			while (line[i] && is_special_char(line[i]) == 1)
				i++;
			cmds[j] = ft_substr(line, last, i - last);
			if (!cmds)
				return (NULL);
			j++;
		}
		else
		{
			if (handle_special_char(line, cmds, &i, &j) == 1)
				return (NULL);
		}
	}
	cmds[j] = NULL;
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
	if (expand_line(shell) == 1) // ARREGLAR EXPANSION CUANDO ENV ESTA DENTRO DE COMILLAS SIMPLES DENTRO DE COMILLAS DOBLES, SE DEBERIA EXPANDIR.
		return (1);
	create_cmd_array(shell);
	return (0);
}