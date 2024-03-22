/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:34:39 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/22 17:35:41 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_word(t_env_list *envi, char *line, int j, int *i)
{
	char	*word_to_expand;
	char	*expansion;
	int		flag;

	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '$')
		(*i)++;
	word_to_expand = ft_substr(line, j, *i - j);
	if (!word_to_expand)
		return (NULL);
	expansion = ft_getenv(envi, word_to_expand, &flag);
	free(word_to_expand);
	return (expansion);
}

int	heredoc_exp(t_shell *shell, int fd, char *line, int *i)
{
	char	*exp_word;
	int		j;

	while (line[*i] && line[*i] != '$')
		ft_putchar_fd(line[(*i)++], fd);
	if (!line[*i])
		return (0);
	if (line[(*i)++] == '$')
	{
		j = *i;
		if (!line[j])
			return (ft_putchar_fd('$', fd), 0);
		if (line[j] == '?')
			return (ft_putnbr_fd(shell->exit_status, fd), (*i)++, \
											heredoc_exp(shell, fd, line, i));
		if (ft_isspace(line[j]))
			return (ft_putchar_fd('$', fd), heredoc_exp(shell, fd, line, i));
		if (!ft_isalpha(line[j]))
			return ((*i)++, heredoc_exp(shell, fd, line, i));
		exp_word = expand_word(shell->envi, line, j, i);
		if (exp_word)
			ft_putstr_fd(exp_word, fd);
	}
	return (heredoc_exp(shell, fd, line, i));
}

int	read_stdin(t_shell *shell, int fd, char *key_word, bool expand)
{
	char	*line;
	int		i;

	line = readline("> ");
	if (!line)
		return (1);
	while (ft_strcmp(line, key_word) != 0)
	{
		if (expand == false)
			ft_putstr_fd(line, fd);
		else
		{
			i = 0;
			if (heredoc_exp(shell, fd, line, &i))
				return (1);
		}
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
		if (!line)
			return (1);
	}
	return (0);
}

void	heredoc(t_shell *shell, t_io_files *infile, bool *error)
{
	int		fd;

	infile->path = create_temp_file();
	if (!infile->path)
	{
		*error = true;
		return ;
	}
	fd = open(infile->path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		*error = true;
		return ;
	}
	if (read_stdin(shell, fd, infile->filename, infile->expheredoc))
	{
		*error = true;
		return ;
	}
}

int	resolve_heredoc(t_shell *shell, t_io_files *infiles, int i, int in_count)
{
	bool	error;

	while (i < in_count)
	{
		if (infiles[i].redir == HEREDOC)
			heredoc(shell, &infiles[i], &error);
		if (error == true)
			return (1);
		i++;
	}
	return (0);
}

/*
	expansiones
	-	un $ solo	--> imprime el dolar.
	-	$$ 			--> numero pid, no gestionar
	-	$CACA 		--> salvo existencia de caca, no imprime nada
	-	$HOME		--> expande a $HOME
	-	$1    		--> si el primer valor depsues del dolar no es digito, 
						no imprime nada y empieza a imprimir lo siguiente
	-	$?			--> expande a ultimo status code.
*/