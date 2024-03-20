/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalonso <raalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:43:59 by raalonso          #+#    #+#             */
/*   Updated: 2024/03/20 23:12:00 by raalonso         ###   ########.fr       */
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
		if (line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i] != '"' && line[i] != '\'')
		{
			count++;
			while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i] != '"' && line[i] != '\'')
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
			if (i - aux == 1)
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
			if (i - aux == 1)
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
		else if (line[i] == '<')
		{
			count++;
			if (line[i + 1] == '<')
				i++;
			i++;
		}
	}
	return (count);
}

bool	is_special_char(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<' || c == '"' || c == '\'')
		return (true);
	return (false);
}

int	quotes_token(char *line, char **cmds, int *i, int *j)
{
	int last = 0;

	if (line[*i] == '"')
	{
		*i += 1;
		last = *i;
		while (line[*i] && line[*i] != '"')
			*i += 1;
	}
	else if (line[*i] == '\'')
	{
		*i += 1;
		last = *i;
		while (line[*i] && line[*i] != '\'')
			*i += 1;
	}
	if ((*i - last) + 2 == 2)
		return (0);
	cmds[*j] = ft_substr(line, last - 1, (*i - last) + 2); // lo devuelvo con comillas para diferenciar redirs.
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
			*j += 1;
		}
	}
	else if (line[*i] == '<')
	{
		last = *i;
		if (line[*i + 1] == '<')
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
			*j += 1;
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
		if (!is_special_char(line[i]))
		{
			last = i;
			while (line[i] && !is_special_char(line[i]))
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
	/*int l = 0;
	printf("TOKENS: \n");
	while (cmds[l])
	{
		printf("\n%s\n", cmds[l]);
		l++;	
	}*/
	return (cmds);
}

int count_cmd(char **tokens, t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) == 1)
			count++;
		i++;
	}
	shell->n_cmds = count;
	return (count);
}

int	rmquotes(char **tokens)
{
	int		i;
	char 	*aux;
	
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '"')
		{
			aux = tokens[i];
			tokens[i] = ft_strtrim(tokens[i], "\"");
			if (!tokens[i])
				return (1);
			free(aux);
		}
		else if (tokens[i][0] == '\'')
		{
			aux = tokens[i];
			tokens[i] = ft_strtrim(tokens[i], "\'");
			if (!tokens[i])
				return (1);
			free(aux);
		}
		i++;
	}
	return (0);
}

t_redir isredir(char *token)
{
	if (ft_strchr(token, '>') && ft_strlen(token) == 1)
		return (OUT);
	else if (ft_strchr(token, '<') && ft_strlen(token) == 1)
		return (IN);
	else if (token[0] == '>' && token[1] == '>' && ft_strlen(token) == 2)
		return (APPOUT);
	else if (token[0] == '<' && token[1] == '<' && ft_strlen(token) == 2)
		return (HEREDOC);
	return (NONE);
}

int	io_files_alloc(char **tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) == 1)
			j++;
		if (isredir(tokens[i]) == IN || isredir(tokens[i]) == HEREDOC)
			shell->cmds[j].infile_count++;
		else if (isredir(tokens[i]) == OUT || isredir(tokens[i]) == APPOUT)
			shell->cmds[j].outfile_count++;
		i++;
	}
	j = 0;
	while (j < shell->n_cmds)
	{
		shell->cmds[j].infile = (t_io_files *)malloc(sizeof(t_io_files) * shell->cmds[j].infile_count + 1); 
		if (!shell->cmds[j].infile)
			return (1);
		shell->cmds[j].outfile = (t_io_files *)malloc(sizeof(t_io_files) * shell->cmds[j].outfile_count + 1);
		if (!shell->cmds[j].outfile)
			return (1);
		j++;
	}
	return (0);
}

int	arg_alloc(char **tokens, t_shell *shell)
{
	int	i;
	int	j;
	int	arg_count;
	
	i = 0;
	j = 0;
	arg_count = 0;
	while (tokens[i])
	{
		if ((ft_strchr(tokens[i], '|') && ft_strlen(tokens[i]) == 1))
		{
			shell->cmds[j].args = (char **)malloc(sizeof(char *) * arg_count + 1);
			if (!shell->cmds[j].args)
				return (1);
			shell->cmds[j].args[arg_count] = NULL;
			arg_count = 0;
			j++;
			i++;
		}
		else if (isredir(tokens[i]) != NONE)
			i++;
		else if (i != 0)
			arg_count++;
		i++;
	}
	shell->cmds[j].args = (char **)malloc(sizeof(char *) * arg_count + 1);
	if (!shell->cmds[j].args)
		return (1);
	shell->cmds[j].args[arg_count] = NULL;
	return (0);
}

int	store_tokens(char **tokens, t_shell *shell)
{
	shell->cmds = (t_command *)malloc(sizeof(t_command) * count_cmd(tokens, shell)); // ACORDARSE LIBERAR COMANDOS + TODO SU CONTENIDO
	int	i = 0;
	int	j = 0;
	int	in_count = 0;
	int	out_count = 0;
	int	arg_count = 0;
	
	if (rmquotes(tokens) == 1)
		return (1);
	if (io_files_alloc(tokens, shell) == 1)
		return (1);
	if (arg_alloc(tokens, shell) == 1)
		return (1);
	while (tokens[i])
	{
		if (tokens[i][0] == '|' && ft_strlen(tokens[i]) == 1)
		{
			j++;
			i++;
			shell->cmds[j].exe = ft_strdup(tokens[i]);
			if (!shell->cmds[j].exe)
				return (1);
			in_count = 0;
			out_count = 0;
			arg_count = 0;
		}
		else if (i == 0)
		{
			shell->cmds[j].exe = ft_strdup(tokens[i]);
			if (!shell->cmds[j].exe)
				return (1);
		}
		else if (isredir(tokens[i]) == IN || isredir(tokens[i]) == HEREDOC)
		{
			shell->cmds[j].infile[in_count].redir = isredir(tokens[i]);
			i++;
			shell->cmds[j].infile[in_count].filename = ft_strdup(tokens[i]);
			if (!shell->cmds[j].infile[in_count].filename)
				return (1);
			in_count++;
		}
		else if (isredir(tokens[i]) == OUT || isredir(tokens[i]) == APPOUT)
		{
			shell->cmds[j].outfile[out_count].redir = isredir(tokens[i]);
			i++;
			shell->cmds[j].outfile[out_count].filename = ft_strdup(tokens[i]);
			if (!shell->cmds[j].outfile[out_count].filename)
				return (1);
			out_count++;
		}
		else
		{
			shell->cmds[j].args[arg_count] = ft_strdup(tokens[i]);
			if (!shell->cmds[j].args[arg_count])
				return (1);
			arg_count++;
		}
		i++;
	}
	return (0);
}

void printall(t_shell *shell)
{
	for (int i = 0; i < shell->n_cmds; i++)
	{
		printf("-------------------------\n\n");
		printf("EXE COMANDO: \n%s\n\n", shell->cmds[i].exe);
		printf("ARGUMENTOS: \n");
		for (int j = 0; shell->cmds[i].args[j]; j++)
			printf("%s\n", shell->cmds[i].args[j]);
		printf("\nINFILES: \n");
		for (int j = 0; j < shell->cmds[i].infile_count; j++)
		{
			printf("Tipo redir -> %u\n", shell->cmds[i].infile[j].redir);
			printf("Filename -> %s\n\n", shell->cmds[i].infile[j].filename);
		}
		printf("OUTFILES: \n");
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
	tokens = get_tokens(shell->line_read); // debo devolver con comillas los que tengan comillas y quitarlas luego en "store tokens".
	if (!tokens)
		return (1);
	store_tokens(tokens, shell);
	printall(shell);
	ft_free_matrix((void *)tokens);
	return (0);
}

int	init_line(t_shell *shell)
{
	if (check_quotes(shell) == 1)
		return (1);
	if (expand_line(shell) == 1) // GESTIONAR SI NO EXISTE ENV, CAMBIAR GETENV POR FT_GETENV, GESTIONAR $?, HEREDOC GESTIONAR EXPANSION DELIMITADOR
		return (1);
	if (create_cmd_array(shell) == 1)
		return (1);
	return (0);
}