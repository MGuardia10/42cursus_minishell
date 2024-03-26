/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:34:39 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/26 18:03:24 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * expands a word by retrieving its value from the environment list.
 * 
 * @param envi a pointer to a structure `t_env_list` that holds environment
 * variables.
 * @param line a string with the input text that needs to be processed.
 * @param j a integer that represents the starting index of the word that needs
 * to be expanded in the `line` string.
 * @param i a pointer to an integer that is used to keep track of the current
 * index position in the string.
 * 
 * @return a string that represents the expansion of the word obtained from the
 * input line. NULL if returned if there is no match.
 */
static char	*expand_word(t_shell *shell, char *line, int j, int *i)
{
	char	*word_to_expand;
	char	*expansion;
	int		flag;

	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '$')
		(*i)++;
	word_to_expand = ft_substr(line, j, *i - j);
	if (!word_to_expand)
		(perror("malloc"), clean_exit(shell, EXIT_FAILURE));
	expansion = ft_getenv(shell->envi, word_to_expand, &flag);
	free(word_to_expand);
	return (expansion);
}

/**
 * The function `heredoc_exp` in C language expands variables and special
 * characters in a given input line and writes the result to a file descriptor.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param fd an integer that represents the fd where the output will be written.
 * @param line a string that contains the input text to be processed.
 * @param i a pointer to an integer that is used as an index to iterate over
 * `line`.
 * 
 * @return an integer value. 0 if line is finished or recursion if there is more
 * string to be parsed.
 */
static int	heredoc_exp(t_shell *shell, int fd, char *line, int *i)
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
		exp_word = expand_word(shell, line, j, i);
		if (exp_word)
			ft_putstr_fd(exp_word, fd);
	}
	return (heredoc_exp(shell, fd, line, i));
}

/**
 * reads input from the standard input until a keyword is encountered, with an
 * option to expand certain content before writing to a file descriptor.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param fd File descriptor for writing output.
 * @param key_word is a string that works as a delimiter like in the original
 * heredoc.
 * @param expand a boolean flag that determines whether to expand the input line
 * before writing it to the file descriptor.
 * 
 * @return an integer value. If the function successfully reads the input until
 * the `key_word` is encountered, it returns 0. Otherwise, it returns 1.
 */
static int	read_stdin(t_shell *shell, int fd, char *key_word, bool expand)
{
	char	*line;
	int		i;

	while (1)
	{
		line = readline("> ");
		if (g_signal_status == SIGINT_HD)
			return (free(line), 1);
		if (!line || ft_strcmp(line, key_word) == 0)
			break ;
		if (expand == false)
			ft_putstr_fd(line, fd);
		else
		{
			i = 0;
			heredoc_exp(shell, fd, line, &i);
		}
		ft_putchar_fd('\n', fd);
		free(line);
	}
	if (line)
		free(line);
	return (0);
}

/**
 * creates a temporary file, opens it for writing, and reads input from stdin
 * into the file.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param infile a pointer to a structure of type `t_io_files`.
 * @param error a pointer to a boolean variable that is used to indicate whether
 * an error occurred during the `heredoc` function execution.
 */
static void	heredoc(t_shell *shell, t_io_files *infile, bool *error)
{
	int		fd;

	infile->path = create_temp_file(shell);
	if (!infile->path)
	{
		*error = true;
		return ;
	}
	fd = open(infile->path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		*error = true;
		perror("open");
		return ;
	}
	if (read_stdin(shell, fd, infile->filename, infile->expheredoc))
	{
		*error = true;
		close(fd);
		return ;
	}
}

/**
 * The function `resolve_heredoc` iterates through input files and processes
 * heredoc redirections, returning an error if encountered.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param infiles a pointer to a structure of type `t_io_files`.
 * @param i an integer representing the current index in the array of infiles.
 * @param in_count an integer representing the total number of infiles.
 * 
 * @return an integer value. If there is an error during the execution of the
 * function (error == true), it will return 1. Otherwise, it will return 0.
 */
int	resolve_heredocs(t_shell *shell, t_command *cmds, int n_cmds)
{
	bool	error;
	int		i;
	int		j;

	error = false;
	i = 0;
	while (i < n_cmds)
	{
		j = 0;
		while (j < cmds[i].infile_count)
		{
			if (cmds[i].infiles[j].redir == HEREDOC)
			{
				signal_handler(ft_sigint_heredoc, SIG_IGN);
				heredoc(shell, &cmds[i].infiles[j], &error);
				signal_handler(ft_sigint, SIG_IGN);
			}
			if (error == true)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
