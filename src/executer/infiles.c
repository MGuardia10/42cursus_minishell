/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguardia <mguardia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:12:47 by mguardia          #+#    #+#             */
/*   Updated: 2024/03/26 17:19:20 by mguardia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function `open_infiles` opens input files for reading and handles errors.
 * 
 * @param infiles pointer to a structure `t_io_files` which contains info 
 * about input files for the command.
 * @param i an integer representing the index of the file in the `infiles` array
 * that needs to be opened.
 * @param error a pointer to a boolean variable that is used to indicate whether
 * an error occurred during the file opening process.
 * 
 * @return an integer value, which is the file descriptor `fd` if the file was
 * successfully opened. If there was an error opening the file, it returns -1.
 */
static int	open_infiles(t_io_files *infiles, int i, bool *error)
{
	int	fd;

	fd = -1;
	if (infiles[i].redir == IN)
		fd = open(infiles[i].filename, O_RDONLY);
	else
		fd = open(infiles[i].path, O_RDONLY);
	if (fd < 0)
	{
		*error = true;
		if (infiles[i].redir == IN)
			ft_fprintf(STDERR_FILENO, "minishell: %s: ", infiles[i].filename);
		else
			ft_fprintf(STDERR_FILENO, "minishell: %s: ", infiles[i].path);
		return (perror(""), -1);
	}
	return (fd);
}

/**
 * handles input file redirection and returns the file descriptor for the last
 * input file or a pipe file descriptor if needed.
 * 
 * @param shell a pointer to a structure of type `t_shell`.
 * @param infiles pointer to a structure `t_io_files` which contains info 
 * about input files for the command.
 * @param in_count an integer that represent the number of infiles.
 * @param pipe is an integer that represents the file descriptor of a pipe. 
 * If `pipe` is -1, there is no pipe.
 * 
 * @return an integer that represents the file descriptor of the input.
 */
int	manage_infiles(t_io_files *infiles, int in_count, int pipe)
{
	int		i;
	int		fd;
	bool	error;

	i = 0;
	error = false;
	fd = STDIN_FILENO;
	while (i < in_count)
	{
		fd = open_infiles(infiles, i, &error);
		if (error == true)
			return (-1);
		if (i != in_count - 1)
			close(fd);
		i++;
	}
	if (fd == STDIN_FILENO && pipe > 0)
		return (pipe);
	if (pipe > 0)
		close(pipe);
	return (fd);
}
